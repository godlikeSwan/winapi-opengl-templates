#include <windows.h>
#include <gl/GL.h>

#include "scene.hpp"

GLfloat ps = 15;

BOOL isAPressed = FALSE;
BOOL isDPressed = FALSE;
BOOL isWPressed = FALSE;
GLfloat x = 0.0f;
const GLfloat g = 10;
GLfloat vy = 0;
GLfloat y = 0;
GLboolean onGround = TRUE;

GLvoid init () {
  spin = 0.0;

  glViewport (0, 0, (GLsizei) 800, (GLsizei) 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 800, 0, 600, -1, 1);

  // glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 0.0, 0.5);

  // glLineWidth(15);
  glPointSize(ps);
}

GLvoid update (LONGLONG diff) {
  GLfloat d = (GLfloat) diff / 100000;
  if (isAPressed) x -= 50 * d;
  if (isDPressed) x += 50 * d;
  if (x < 0 + ps) x = 0 + ps;
  if (x > 800 - ps) x = 800 - ps;
  vy -= g * d;
  y += vy * d;
  if (y < 0 + ps) {
    vy = 0;
    y = 0 + ps;
    onGround = TRUE;
  }
  if (isWPressed && onGround) {
    onGround = FALSE;
    vy += 50;
  }
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_POINTS);
    glVertex2f(x, y);
  glEnd();
  // glRecti(0, 0, 50, 50);
  glFlush();
}

void onKeydown (WORD vkCode) {
  if (vkCode == 'A') isAPressed = TRUE;
  if (vkCode == 'D') isDPressed = TRUE;
  if (vkCode == 'W') isWPressed = TRUE;
}

void onKeyup (WORD vkCode) {
  if (vkCode == 'A') isAPressed = FALSE;
  if (vkCode == 'D') isDPressed = FALSE;
  if (vkCode == 'W') isWPressed = FALSE;
}

    // glPushMatrix();
    // glRotatef(spin, 0.0, 0.0, 1.0);
    // spin = spin + 360.0f * diff / 1000000;
    // glRectf(-1.0, 0.0, 1.0, 25.0);
    // glPopMatrix();
    // glFinish();
