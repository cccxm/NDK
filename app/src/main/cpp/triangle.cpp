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

#include "triangle.h"

GLboolean
triangleCreateWindow(TriangleContext *context) {
    context->width = ANativeWindow_getWidth(context->nativeWindow);
    context->height = ANativeWindow_getHeight(context->nativeWindow);

    context->eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (context->eglDisplay == EGL_NO_DISPLAY) {
        return GL_FALSE;
    }
    GLint majorVersion;
    GLint minorVersion;
    EGLConfig config;
    if (!eglInitialize(context->eglDisplay, &majorVersion, &minorVersion)) {
        return GL_FALSE;
    }

    EGLint numConfigs = 0;
    EGLint attribList[] =
            {
                    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,
                    EGL_DEPTH_SIZE, 16,
                    EGL_NONE
            };

    if (!eglChooseConfig(context->eglDisplay, attribList, &config, 1, &numConfigs)) {
        return GL_FALSE;
    }

    if (numConfigs < 1) {
        return GL_FALSE;
    }

    EGLint format = 0;
    eglGetConfigAttrib(context->eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(context->nativeWindow, 0, 0, format);


    context->eglSurface = eglCreateWindowSurface(context->eglDisplay, config, context->nativeWindow,
                                                 NULL);

    if (context->eglSurface == EGL_NO_SURFACE) {
        return GL_FALSE;
    }

    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

    context->eglContext = eglCreateContext(context->eglDisplay, config, EGL_NO_CONTEXT,
                                           contextAttribs);

    if (context->eglContext == EGL_NO_CONTEXT) {
        return GL_FALSE;
    }

    if (!eglMakeCurrent(context->eglDisplay, context->eglSurface, context->eglSurface,
                        context->eglContext)) {
        return GL_FALSE;
    }
    return GL_TRUE;
}

//

static const char VERTEX_SHADER[] =
        "#version 300 es\n"
                "layout(location = 0) in vec4 vPosition;\n"
                "void main(){\n"
                "   gl_Position = vPosition;\n"
                "}\n";

static const char FRAGMENT_SHADER[] =
        "#version 300 es\n"
                "precision mediump float;\n"
                "out vec4 fragColor;\n"
                "void main(){\n"
                "   fragColor = vec4(1.0,0.0,0.0,1.0);\n"
                "}\n";

static const GLfloat VERTEX[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
};

GLuint program;

GLboolean
triangleInit(TriangleContext *context) {
    program = createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!program) {
        ALOGE("程序创建失败");
        return GL_FALSE;
    }
    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, context->width, context->height);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    return GL_TRUE;
}

void
triangleStep(TriangleContext *context) {
    glClear(GL_COLOR_BUFFER_BIT);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, VERTEX);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void
triangleDestroy(TriangleContext *context) {
    glDeleteProgram(program);
}