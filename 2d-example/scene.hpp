#ifndef _2d_scene_H
#define _2d_scene_H

#include <windows.h>
#include <gl/GL.h>

static GLfloat spin;


GLvoid init (void);

GLvoid update (LONGLONG diff);

void onKeydown (WORD vkCode);
void onKeyup (WORD vkCode);

#endif
