// #define _2d_H
#ifndef _2d_H
#define _2d_H

#include <windows.h>
#include <GL/GL.h>

static LPCTSTR windowClassName = L"_2d";
static HINSTANCE instance = NULL;

static HWND wnd = NULL;
static HDC deviceContext = NULL;
static HGLRC glContext = NULL;

static PIXELFORMATDESCRIPTOR pixelFormat = {
  sizeof(PIXELFORMATDESCRIPTOR),
  1,
  PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,// | PFD_DOUBLEBUFFER,
  PFD_TYPE_RGBA,
  32,
  0, 0, 0, 0, 0, 0,
  0,
  0,
  0,
  0, 0, 0, 0,
  24,
  8,
  0,
  PFD_MAIN_PLANE,
  0,
  0, 0, 0
};


static void WINAPI spinner (void* arg);
LRESULT WndProc (HWND wnd, UINT msg, WPARAM p1, LPARAM p2);

#endif
