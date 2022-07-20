#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <GL/GL.h>

#include <stdio.h>


#include "scene.hpp"

#include "2d.hpp"

LRESULT WndProc (HWND wnd, UINT msg, WPARAM p1, LPARAM p2) {
  RECT rect;

  if (msg == WM_CREATE) {
    deviceContext = GetDC(wnd);
    int choosenFormat = ChoosePixelFormat(deviceContext, &pixelFormat);
    if (choosenFormat == 0) PostQuitMessage(0);
    if (SetPixelFormat(deviceContext, choosenFormat, &pixelFormat) == FALSE) PostQuitMessage(0);

    glContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, glContext);

    GetClientRect(wnd, &rect);

    // To check some values:
    // WCHAR a[50];
    // GLfloat pointSizeRange[2];
    // glGetFloatv(GL_POINT_SIZE_RANGE, pointSizeRange);
    // swprintf(a, L"%f-%f", pointSizeRange[0], pointSizeRange[1]);
    // MessageBox(wnd, (LPWSTR)a, L"max point", NULL);

    init();
    return 0;
  } else if (msg == WM_KEYDOWN) {
    if ((HIWORD(p2) & KF_REPEAT) == KF_REPEAT) return 0;
    WORD vkCode = LOWORD(p1);
    onKeydown(vkCode);
    return 0;
  } else if (msg == WM_KEYUP) {
    WORD vkCode = LOWORD(p1);
    onKeyup(vkCode);
    return 0;
  } else if (msg == WM_PAINT) {
    PAINTSTRUCT paint;
    BeginPaint(wnd, &paint);
    EndPaint(wnd, &paint);
    return 0;
  } else if (msg == WM_SIZE) {
    GetClientRect(wnd, &rect);
    return 0;
  } else if (msg == WM_GETMINMAXINFO) {
    // GetClientRect(wnd, &rect);
    MINMAXINFO *mm;
    mm = (MINMAXINFO*)p2;
    mm->ptMinTrackSize.x = 850;
    mm->ptMinTrackSize.y = 600;
    mm->ptMaxTrackSize.x = 850;
    mm->ptMaxTrackSize.y = 600;
    return 0;
  // } else if (msg == WM_WINDOWPOSCHANGING) {
  //   return 0;
  // } else if (msg == WM_NCLBUTTONDOWN) {
  //   SetWindowPos(wnd, HWND_TOP, 500, 500, 1000, 1000, SWP_NOSIZE);
  //   return 0;
  }  else if (msg == WM_MOUSEMOVE) {
    WORD x = LOWORD(p2);
    WORD y = HIWORD(p2);
    InvalidateRgn(wnd, NULL, FALSE);
    return 0;
  } else if (msg == WM_DESTROY) {
    wglDeleteContext(glContext);
    PostQuitMessage(0);
    return 0;
  } else {
    return DefWindowProc(wnd, msg, p1, p2);
  }
}

int wWinMain (HINSTANCE _instance, HINSTANCE prev, PWSTR args, int flag) {
  instance = _instance;
  // wsprintfW((LPWSTR)&str, L"test");


  WNDCLASSEX windowClass = {
    sizeof(WNDCLASSEX),
    CS_OWNDC,
    WndProc,
    0, 0,
    instance,
    NULL,
    LoadCursor(NULL, IDC_ARROW),
    NULL,
    NULL,
    windowClassName,
    NULL
  };
  if (!RegisterClassEx(&windowClass)) return FALSE;

  wnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, windowClassName, L"minimal", WS_OVERLAPPEDWINDOW, 0, 0, 850, 600, NULL, NULL, instance, NULL);
  if (!wnd) return FALSE;
  ShowWindow(wnd, flag);
  UpdateWindow(wnd);

  LARGE_INTEGER start, stop, freq;
  LONGLONG diff;
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&start);
  while (1) {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE) {
      if (GetMessage(&msg, NULL, 0, 0)) {
        // TranslateMessage(&msg);
        // if (msg.message == WM_SIZING) break;
        // if (msg.message == WM_NCLBUTTONDOWN) break;
        DispatchMessage(&msg);
      } else {
        return TRUE;
      }
    }

    // TODO: add delta as arg
    QueryPerformanceCounter(&stop);
    diff = stop.QuadPart - start.QuadPart;
    diff *= 1000000;
    diff /= freq.QuadPart;
    update(diff);
    start.QuadPart = stop.QuadPart;
    // QueryPerformanceCounter(&start);
    // SwapBuffers(deviceContext);
  }

  return 0;
}
