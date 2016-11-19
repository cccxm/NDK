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
// Created by 陈小默 on 16/11/8.
//

#ifndef NDK_JNIUTIL_H
#define NDK_JNIUTIL_H

#include <jni.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <ctime>
#include <iostream>
#include <GLES3/gl3.h>
#include <EGL/egl.h>

using namespace std;

#include "Lang.h"
#include "String.h"
#include "File.h"

#ifndef LOG_TAG
#define LOG_TAG "NDK-LIB"
#endif

#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)

#define PI 3.1415926

float GetCurrentTime();

//检查当前程序错误
bool checkGlError(const char *funcName);

//获取并编译着色器对象
GLuint createShader(GLenum shaderType, const char *src);

//使用着色器生成着色器程序对象
GLuint createProgram(const char *vtxSrc, const char *fragSrc);


//产生一个立方体
int createCube(float scale, GLfloat **vertices, GLfloat **normals,
               GLfloat **texCoords, GLuint **indices);

int createSquareGrid(int size, GLfloat **vertices, GLuint **indices);

//生成一个球
int createSphere(int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
                 GLfloat **texCoords, GLuint **indices);


typedef struct {
    GLfloat m[4][4];
} Matrix;

//初始化一个矩阵
void matrixLoadIdentity(Matrix *result);

//矩阵变换
void translate(Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz);

//矩阵旋转
void rotate(Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

//矩阵相乘
void matrixMultiply(Matrix *result, Matrix *srcA, Matrix *srcB);

//矩阵截取
void frustum(Matrix *result, float w, float h, float nearZ, float farZ);

//矩阵透视变换
void perspective(Matrix *result, float fovy, float aspect, float nearZ, float farZ);

void ortho(Matrix *result, float left, float right, float bottom, float top, float nearZ,
           float farZ);

void scale(Matrix *result, GLfloat sx, GLfloat sy, GLfloat sz);

void matrixLookAt(Matrix *result, float posX, float posY, float posZ, float lookAtX, float lookAtY,
                  float lookAtZ, float upX, float upY, float upZ);


#endif //NDK_JNIUTIL_H
