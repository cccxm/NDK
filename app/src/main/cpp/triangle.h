/**
 *  project:NDK
 *  Copyright (C) <2016>  <陈小默>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
//
// Created by 陈小默 on 16/11/18.
//

#ifndef NDK_TRIANGLE_H
#define NDK_TRIANGLE_H

#define LOG_TAG "TRIANGLE"

#include "JniUtil.h"

typedef struct {
    void *UserData;
    int32_t width;
    int32_t height;
    ANativeActivity *nativeActivity;
    ANativeWindow *nativeWindow;
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLContext eglContext;
} TriangleContext;

GLboolean triangleCreateWindow(TriangleContext *context);

GLboolean triangleInit(TriangleContext *context);

void triangleStep(TriangleContext *context);

void triangleDestroy(TriangleContext *context);

#endif //NDK_TRIANGLE_H
