#include <windows.h>
#include <gl/GL.h>

#include "scene.hpp"

GLvoid init () {
  spin = 0.0;

  glViewport (0, 0, (GLsizei) 800, (GLsizei) 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 0.0);
}

GLvoid update (LONGLONG diff) {
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);
    spin = spin + 360.0f * diff / 1000000;
    glRectf(-1.0, 0.0, 1.0, 25.0);
    glPopMatrix();
    // glFinish();
    glFlush();
}
