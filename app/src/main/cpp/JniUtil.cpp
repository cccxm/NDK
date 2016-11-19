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
#include "JniUtil.h"
#include <fstream>

void
toString(int value, char *buffer, int radix) {
    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned uNum;
    int i = 0, j, k;
    if (radix == 10 && value < 0) {
        uNum = unsigned(-value);
        buffer[i++] = '-';
    } else uNum = unsigned(value);
    do {
        buffer[i++] = index[uNum % (unsigned) radix];
        uNum /= radix;
    } while (uNum);
    buffer[i] = '\0';
    if (buffer[0] == '-') k = 1;
    else k = 0;
    char temp;
    for (j = k; j <= (i - k - 1) / 2.0; j++) {
        temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

String::String() : _size(0) {
    _str = (char *) malloc(sizeof(char));
    _str[0] = '\0';
}

String::String(String &str) {
    _size = str._size;
    _str = (char *) malloc(sizeof(char) * _size);
    strcpy(_str, str._str);
}

String::String(char *str) {
    _size = int(strlen(str));
    _str = (char *) malloc(sizeof(char) * _size);
    strcpy(_str, str);
}

String::~String() { free(_str); }

String &
String::operator=(char *str) {
    _size = int(strlen(str));
    _str = (char *) malloc(sizeof(char) * _size);
    strcpy(_str, str);
    return *this;
}

StringBuilder::StringBuilder(String &str) {
    _size = str._size;
    _max = _size + 1;
    _buffer = (char *) malloc(sizeof(char) * _max);
    strcpy(_buffer, str);
}

StringBuilder::StringBuilder(unsigned capacity) {
    _size = capacity;
    _max = _size + 1;
    _buffer = (char *) malloc(sizeof(char) * _max);
    _buffer[0] = '\0';
}

StringBuilder::~StringBuilder() { free(_buffer); }

StringBuilder &
StringBuilder::append(char *str) {
    int nMax = _max;
    auto size = strlen(str);
    while (_size + size >= nMax)nMax *= 2;
    if (nMax != _max) {
        _max = nMax;
        char *nStr = (char *) malloc(sizeof(char) * _max);
        strcpy(nStr, _buffer);
        free(_buffer);
        _buffer = nStr;
    }
    for (int i = 0; _buffer[_size++] = str[i]; i++);
    *(_buffer + _size) = '\0';
    return *this;
}

StringBuilder &
StringBuilder::append(char *arr, unsigned off, unsigned len) {
    char *str = new char[len + 1];
    auto size = strlen(arr);
    if (size < off + len) return *this;
    arr = arr + off;
    memcpy(str, arr, len);
    StringBuilder &temp = append(str);
    delete[] str;
    return temp;
}

StringBuilder &
StringBuilder::append(char c) {
    if (_size == _max - 1) {
        _max *= 2;
        realloc(_buffer, _max);
    }
    _buffer[_size++] = c;
    _buffer[_size] = '\0';
    return *this;
}

StringBuilder &
StringBuilder::append(int value, int radix) {
    char buffer[22];
    ::toString(value, buffer, radix);
    return append(buffer);
}

StringBuilder
&StringBuilder::append(float value) {
    char buffer[32];
    sprintf(buffer, "%f", value);
    return append(buffer);
}

String &
StringBuilder::toString() {
    return *(new String(_buffer));
}

ByteArray::ByteArray(int length, byte def) : _length(length) {
    _array = (byte *) malloc(sizeof(byte) * length);
    for (int i = 0; i < length; _array[i++] = def);
}

ByteArray::ByteArray(int length, byte *arr) {
    _length = length;
    _array = (byte *) malloc(sizeof(byte) * length);
    for (int i = 0; i < length; _array[i] = arr[i], i++);
}

ByteArray::~ByteArray() { free(_array); }

UByteArray::UByteArray(int length, ubyte def) : _length(length) {
    _array = (ubyte *) malloc(sizeof(ubyte) * length);
    for (int i = 0; i < length; _array[i++] = def);
}

UByteArray::~UByteArray() { free(_array); }

FileInputStream::FileInputStream(File &file) : _s(new ifstream) {
    _s->open(file.getAbsolutePath(), std::ios::in | std::ios::app);
}

FileInputStream::FileInputStream(char *dir, char *name) {
    File file(dir, name);
    _s->open(file.getAbsolutePath(), std::ios::in | std::ios::app);
}

FileInputStream::~FileInputStream() {
    delete (_s);
}

int
FileInputStream::read(ByteArray &b) {
    streamsize len = -1;
    if (_s->eof() == 0) {//到达结尾返回非零
        _s->read(b, b.size());
        len = _s->gcount();
    }
    return int(len);
}

void
FileInputStream::close() {
    _s->close();
}

FileOutputStream::FileOutputStream(File &file) : _s(new ofstream) {
    _s->open(file.getAbsolutePath(), std::ios::out | std::ios::app);
}

FileOutputStream::FileOutputStream(char *dir, char *name) {
    File file(dir, name);
    _s->open(file.getAbsolutePath(), std::ios::out | std::ios::app);
}

FileOutputStream::~FileOutputStream() {
    delete (_s);
}

void
FileOutputStream::close() {
    _s->close();
}

TextFile::TextFile(File &file) {
    _is = new FileInputStream(file);
    _os = new FileOutputStream(file);
}

TextFile::TextFile(char *dir, char *name) {
    _is = new FileInputStream(dir, name);
    _os = new FileOutputStream(dir, name);
}

TextFile::TextFile(char *path) {
    File file(path);
    _is = new FileInputStream(file);
    _os = new FileOutputStream(file);
}

String &
TextFile::getText() {
    StringBuilder builder;
    ByteArray bytes(64 * 1024);
    int len;
    while ((len = _is->read(bytes)) != -1) {
        builder.append(bytes, 0, len);
    }
    return builder.toString();
}

TextFile::~TextFile() {
    delete _is;
    delete _os;
}

void
TextFile::close() {
    _is->close();
    _os->close();
}

File::File(char *path) {
    _path = new String(path);
}

File::File(char *dir, char *name) {
    StringBuilder builder;
    _path = &(builder.append(dir).append(name).toString());
}

String &
File::getAbsolutePath() {
    return *_path;
}

File::~File() {
    delete _path;
}

bool
File::exists() {
    fstream file;
    file.open(*_path, ios_base::in);
    bool result = file.is_open();
    file.close();
    return result;
}

float
GetCurrentTime() {
    struct timespec clockRealTime;
    clock_gettime(CLOCK_MONOTONIC, &clockRealTime);
    double curTimeInSeconds = clockRealTime.tv_sec + (double) clockRealTime.tv_nsec / 1e9;
    return (float) curTimeInSeconds;
}

bool checkGlError(const char *funcName) {
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        ALOGE("GL error after %s(): 0x%08x\n", funcName, err);
        return true;
    }
    return false;
}

GLuint createShader(GLenum shaderType, const char *src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        checkGlError("glCreateShader");
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);

    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
                ALOGE("Could not compile %s shader:\n%s\n",
                      shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
                      infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint createProgram(const char *vtxSrc, const char *fragSrc) {
    GLuint vtxShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
    GLint linked = GL_FALSE;

    vtxShader = createShader(GL_VERTEX_SHADER, vtxSrc);
    if (!vtxShader)
        goto exit;

    fragShader = createShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragShader)
        goto exit;

    program = glCreateProgram();
    if (!program) {
        checkGlError("glCreateProgram");
        goto exit;
    }
    glAttachShader(program, vtxShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        ALOGE("Could not link program");
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen) {
            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
                ALOGE("Could not link program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }

    exit:
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);
    return program;
}

void
matrixMultiply(Matrix *result, Matrix *srcA, Matrix *srcB) {
    Matrix tmp;
    int i;

    for (i = 0; i < 4; i++) {
        tmp.m[i][0] = (srcA->m[i][0] * srcB->m[0][0]) +
                      (srcA->m[i][1] * srcB->m[1][0]) +
                      (srcA->m[i][2] * srcB->m[2][0]) +
                      (srcA->m[i][3] * srcB->m[3][0]);

        tmp.m[i][1] = (srcA->m[i][0] * srcB->m[0][1]) +
                      (srcA->m[i][1] * srcB->m[1][1]) +
                      (srcA->m[i][2] * srcB->m[2][1]) +
                      (srcA->m[i][3] * srcB->m[3][1]);

        tmp.m[i][2] = (srcA->m[i][0] * srcB->m[0][2]) +
                      (srcA->m[i][1] * srcB->m[1][2]) +
                      (srcA->m[i][2] * srcB->m[2][2]) +
                      (srcA->m[i][3] * srcB->m[3][2]);

        tmp.m[i][3] = (srcA->m[i][0] * srcB->m[0][3]) +
                      (srcA->m[i][1] * srcB->m[1][3]) +
                      (srcA->m[i][2] * srcB->m[2][3]) +
                      (srcA->m[i][3] * srcB->m[3][3]);
    }

    memcpy(result, &tmp, sizeof(Matrix));
}

int createSquareGrid(int size, GLfloat **vertices, GLuint **indices) {
    GLuint i, j;
    int numIndices = (size - 1) * (size - 1) * 2 * 3;

    // Allocate memory for buffers
    if (vertices != NULL) {
        int numVertices = size * size;
        float stepSize = (float) size - 1;
        *vertices = (GLfloat *) malloc(sizeof(GLfloat) * 3 * numVertices);

        for (i = 0; i < size; ++i) // row
        {
            for (j = 0; j < size; ++j) // column
            {
                (*vertices)[3 * (j + i * size)] = i / stepSize;
                (*vertices)[3 * (j + i * size) + 1] = j / stepSize;
                (*vertices)[3 * (j + i * size) + 2] = 0.0f;
            }
        }
    }

    // Generate the indices
    if (indices != NULL) {
        *indices = (GLuint *) malloc(sizeof(GLuint) * numIndices);

        for (i = 0; i < size - 1; ++i) {
            for (j = 0; j < size - 1; ++j) {
                // two triangles per quad
                (*indices)[6 * (j + i * (size - 1))] = j + (i) * (size);
                (*indices)[6 * (j + i * (size - 1)) + 1] = j + (i) * (size) + 1;
                (*indices)[6 * (j + i * (size - 1)) + 2] = j + (i + 1) * (size) + 1;

                (*indices)[6 * (j + i * (size - 1)) + 3] = j + (i) * (size);
                (*indices)[6 * (j + i * (size - 1)) + 4] = j + (i + 1) * (size) + 1;
                (*indices)[6 * (j + i * (size - 1)) + 5] = j + (i + 1) * (size);
            }
        }
    }

    return numIndices;
}

void
frustum(Matrix *result, float w, float h, float nearZ,
        float farZ) {
    float left = -w;
    float right = w;
    float bottom = -h;
    float top = h;
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    Matrix frust;

    if ((nearZ <= 0.0f) || (farZ <= 0.0f) ||
        (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f)) {
        return;
    }

    frust.m[0][0] = 2.0f * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

    frust.m[1][1] = 2.0f * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

    frust.m[2][0] = (right + left) / deltaX;
    frust.m[2][1] = (top + bottom) / deltaY;
    frust.m[2][2] = -(nearZ + farZ) / deltaZ;
    frust.m[2][3] = -1.0f;

    frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

    matrixMultiply(result, &frust, result);
}

void
rotate(Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    GLfloat sinAngle, cosAngle;
    GLfloat mag = sqrtf(x * x + y * y + z * z);

    sinAngle = sinf(float(angle * PI / 180.0f));
    cosAngle = cosf(float(angle * PI / 180.0f));

    if (mag > 0.0f) {
        GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
        GLfloat oneMinusCos;
        Matrix rotMat;

        x /= mag;
        y /= mag;
        z /= mag;

        xx = x * x;
        yy = y * y;
        zz = z * z;
        xy = x * y;
        yz = y * z;
        zx = z * x;
        xs = x * sinAngle;
        ys = y * sinAngle;
        zs = z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;

        rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
        rotMat.m[0][1] = (oneMinusCos * xy) - zs;
        rotMat.m[0][2] = (oneMinusCos * zx) + ys;
        rotMat.m[0][3] = 0.0F;

        rotMat.m[1][0] = (oneMinusCos * xy) + zs;
        rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
        rotMat.m[1][2] = (oneMinusCos * yz) - xs;
        rotMat.m[1][3] = 0.0F;

        rotMat.m[2][0] = (oneMinusCos * zx) - ys;
        rotMat.m[2][1] = (oneMinusCos * yz) + xs;
        rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
        rotMat.m[2][3] = 0.0F;

        rotMat.m[3][0] = 0.0F;
        rotMat.m[3][1] = 0.0F;
        rotMat.m[3][2] = 0.0F;
        rotMat.m[3][3] = 1.0F;

        matrixMultiply(result, &rotMat, result);
    }
}

void
translate(Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz) {
    result->m[3][0] += (result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz);
    result->m[3][1] += (result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz);
    result->m[3][2] += (result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz);
    result->m[3][3] += (result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz);
}

void
matrixLoadIdentity(Matrix *result) {
    memset(result, 0, sizeof(Matrix));
    result->m[0][0] = 1.0f;
    result->m[1][1] = 1.0f;
    result->m[2][2] = 1.0f;
    result->m[3][3] = 1.0f;
}

int
createCube(float scale, GLfloat **vertices, GLfloat **normals,
           GLfloat **texCoords, GLuint **indices) {
    int i;
    int numVertices = 24;
    int numIndices = 36;

    GLfloat cubeVerts[] =
            {
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, 0.5f,
                    0.5f, -0.5f, 0.5f,
                    0.5f, -0.5f, -0.5f,
                    -0.5f, 0.5f, -0.5f,
                    -0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, 0.5f, -0.5f,
                    0.5f, 0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, 0.5f,
                    -0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, 0.5f,
                    0.5f, -0.5f, 0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, 0.5f,
                    -0.5f, 0.5f, 0.5f,
                    -0.5f, 0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, 0.5f,
                    0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, -0.5f,
            };

    GLfloat cubeNormals[] =
            {
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
            };

    GLfloat cubeTex[] =
            {
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
            };
    if (vertices != NULL) {
        *vertices = (GLfloat *) malloc(sizeof(GLfloat) * 3 * numVertices);
        memcpy(*vertices, cubeVerts, sizeof(cubeVerts));

        for (i = 0; i < numVertices * 3; i++) {
            (*vertices)[i] *= scale;
        }
    }
    if (normals != NULL) {
        *normals = (GLfloat *) malloc(sizeof(GLfloat) * 3 * numVertices);
        memcpy(*normals, cubeNormals, sizeof(cubeNormals));
    }
    if (texCoords != NULL) {
        *texCoords = (GLfloat *) malloc(sizeof(GLfloat) * 2 * numVertices);
        memcpy(*texCoords, cubeTex, sizeof(cubeTex));
    }
    if (indices != NULL) {
        GLuint cubeIndices[] =
                {
                        0, 2, 1,
                        0, 3, 2,
                        4, 5, 6,
                        4, 6, 7,
                        8, 9, 10,
                        8, 10, 11,
                        12, 15, 14,
                        12, 14, 13,
                        16, 17, 18,
                        16, 18, 19,
                        20, 23, 22,
                        20, 22, 21
                };

        *indices = (GLuint *) malloc(sizeof(GLuint) * numIndices);
        memcpy(*indices, cubeIndices, sizeof(cubeIndices));
    }
    return numIndices;
}

void
perspective(Matrix *result, float fovy, float aspect, float nearZ, float farZ) {
    GLfloat frustumW, frustumH;

    frustumH = tanf(float(fovy / 360.0f * PI)) * nearZ;
    frustumW = frustumH * aspect;

    frustum(result, frustumW, frustumH, nearZ, farZ);
}

void
scale(Matrix *result, GLfloat sx, GLfloat sy, GLfloat sz) {
    result->m[0][0] *= sx;
    result->m[0][1] *= sx;
    result->m[0][2] *= sx;
    result->m[0][3] *= sx;

    result->m[1][0] *= sy;
    result->m[1][1] *= sy;
    result->m[1][2] *= sy;
    result->m[1][3] *= sy;

    result->m[2][0] *= sz;
    result->m[2][1] *= sz;
    result->m[2][2] *= sz;
    result->m[2][3] *= sz;
}

void
matrixLookAt(Matrix *result,
             float posX, float posY, float posZ,
             float lookAtX, float lookAtY, float lookAtZ,
             float upX, float upY, float upZ) {
    float axisX[3], axisY[3], axisZ[3];
    float length;

// axisZ = lookAt - pos
    axisZ[0] = lookAtX - posX;
    axisZ[1] = lookAtY - posY;
    axisZ[2] = lookAtZ - posZ;

// normalize axisZ
    length = sqrtf(axisZ[0] * axisZ[0] + axisZ[1] * axisZ[1] + axisZ[2] * axisZ[2]);

    if (length != 0.0f) {
        axisZ[0] /= length;
        axisZ[1] /= length;
        axisZ[2] /= length;
    }

// axisX = up X axisZ
    axisX[0] = upY * axisZ[2] - upZ * axisZ[1];
    axisX[1] = upZ * axisZ[0] - upX * axisZ[2];
    axisX[2] = upX * axisZ[1] - upY * axisZ[0];

// normalize axisX
    length = sqrtf(axisX[0] * axisX[0] + axisX[1] * axisX[1] + axisX[2] * axisX[2]);

    if (length != 0.0f) {
        axisX[0] /= length;
        axisX[1] /= length;
        axisX[2] /= length;
    }

// axisY = axisZ x axisX
    axisY[0] = axisZ[1] * axisX[2] - axisZ[2] * axisX[1];
    axisY[1] = axisZ[2] * axisX[0] - axisZ[0] * axisX[2];
    axisY[2] = axisZ[0] * axisX[1] - axisZ[1] * axisX[0];

// normalize axisY
    length = sqrtf(axisY[0] * axisY[0] + axisY[1] * axisY[1] + axisY[2] * axisY[2]);

    if (length != 0.0f) {
        axisY[0] /= length;
        axisY[1] /= length;
        axisY[2] /= length;
    }

    memset(result, 0x0, sizeof(Matrix));

    result->m[0][0] = -axisX[0];
    result->m[0][1] = axisY[0];
    result->m[0][2] = -axisZ[0];

    result->m[1][0] = -axisX[1];
    result->m[1][1] = axisY[1];
    result->m[1][2] = -axisZ[1];

    result->m[2][0] = -axisX[2];
    result->m[2][1] = axisY[2];
    result->m[2][2] = -axisZ[2];

// translate (-posX, -posY, -posZ)
    result->m[3][0] = axisX[0] * posX + axisX[1] * posY + axisX[2] * posZ;
    result->m[3][1] = -axisY[0] * posX - axisY[1] * posY - axisY[2] * posZ;
    result->m[3][2] = axisZ[0] * posX + axisZ[1] * posY + axisZ[2] * posZ;
    result->m[3][3] = 1.0f;
}


void
ortho(Matrix *result, float left, float right, float bottom, float top, float nearZ,
      float farZ) {
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;
    Matrix ortho;

    if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f)) {
        return;
    }

    matrixLoadIdentity(&ortho);
    ortho.m[0][0] = 2.0f / deltaX;
    ortho.m[3][0] = -(right + left) / deltaX;
    ortho.m[1][1] = 2.0f / deltaY;
    ortho.m[3][1] = -(top + bottom) / deltaY;
    ortho.m[2][2] = -2.0f / deltaZ;
    ortho.m[3][2] = -(nearZ + farZ) / deltaZ;

    matrixMultiply(result, &ortho, result);
}

int
createSphere(int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
             GLfloat **texCoords, GLuint **indices) {
    int i;
    int j;
    int numParallels = numSlices / 2;
    int numVertices = (numParallels + 1) * (numSlices + 1);
    int numIndices = numParallels * numSlices * 6;
    float angleStep = (float) (2.0f * PI) / numSlices;

    // Allocate memory for buffers
    if (vertices != NULL) {
        *vertices = (GLfloat *) malloc(sizeof(GLfloat) * 3 * numVertices);
    }

    if (normals != NULL) {
        *normals = (GLfloat *) malloc(sizeof(GLfloat) * 3 * numVertices);
    }

    if (texCoords != NULL) {
        *texCoords = (GLfloat *) malloc(sizeof(GLfloat) * 2 * numVertices);
    }

    if (indices != NULL) {
        *indices = (GLuint *) malloc(sizeof(GLuint) * numIndices);
    }

    for (i = 0; i < numParallels + 1; i++) {
        for (j = 0; j < numSlices + 1; j++) {
            int vertex = (i * (numSlices + 1) + j) * 3;

            if (vertices) {
                (*vertices)[vertex + 0] = radius * sinf(angleStep * (float) i) *
                                          sinf(angleStep * (float) j);
                (*vertices)[vertex + 1] = radius * cosf(angleStep * (float) i);
                (*vertices)[vertex + 2] = radius * sinf(angleStep * (float) i) *
                                          cosf(angleStep * (float) j);
            }

            if (normals) {
                (*normals)[vertex + 0] = (*vertices)[vertex + 0] / radius;
                (*normals)[vertex + 1] = (*vertices)[vertex + 1] / radius;
                (*normals)[vertex + 2] = (*vertices)[vertex + 2] / radius;
            }

            if (texCoords) {
                int texIndex = (i * (numSlices + 1) + j) * 2;
                (*texCoords)[texIndex + 0] = (float) j / (float) numSlices;
                (*texCoords)[texIndex + 1] = (1.0f - (float) i) / (float) (numParallels - 1);
            }
        }
    }
    // Generate the indices
    if (indices != NULL) {
        GLuint *indexBuf = (*indices);

        for (i = 0; i < numParallels; i++) {
            for (j = 0; j < numSlices; j++) {
                *indexBuf++ = (GLuint) (i * (numSlices + 1) + j);
                *indexBuf++ = (GLuint) (i + 1) * (numSlices + 1) + j;
                *indexBuf++ = (GLuint) (i + 1) * (numSlices + 1) + (j + 1);

                *indexBuf++ = (GLuint) i * (numSlices + 1) + j;
                *indexBuf++ = (GLuint) (i + 1) * (numSlices + 1) + (j + 1);
                *indexBuf++ = (GLuint) i * (numSlices + 1) + (j + 1);
            }
        }
    }
    return numIndices;
}
