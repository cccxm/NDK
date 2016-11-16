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
// Created by 陈小默 on 16/11/9.
//

#ifndef NDK_BITMAP_H
#define NDK_BITMAP_H

#include <android/bitmap.h>
#include "JniUtil.h"

typedef uint32_t ABsize;//Android Bitmap size

typedef int32_t ABformat;//Android Bitmap format

#ifdef ARGB_8888
typedef uint32_t  APixel;
ABformat checkFormat = ANDROID_BITMAP_FORMAT_RGBA_8888;
#elif defined(ARGB_4444)
typedef uint16_t APixel;
ABformat checkFormat = ANDROID_BITMAP_FORMAT_RGBA_4444;
#elif defined(RGB_565)
typedef uint16_t APixel;
ABformat checkFormat = ANDROID_BITMAP_FORMAT_RGB_565;
#elif defined(ALPHA_8)
typedef uint8_t APixel;
ABformat checkFormat = ANDROID_BITMAP_FORMAT_A_8;
#else
typedef uint32_t  APixel;
ABformat checkFormat = ANDROID_BITMAP_FORMAT_RGBA_8888;
#endif


class Bitmap {
private:
    APixel *pixels;
    JNIEnv *jenv;
    _jobject *jbitmap;
    AndroidBitmapInfo info;
    int result;
    ABsize width;
    ABsize height;
public:
    Bitmap(int width, int height) : jenv(NULL), jbitmap(NULL) {
        pixels = (APixel *) malloc(sizeof(APixel) * width * height);
        memset(pixels, 0, width * height);
    }

    Bitmap(JNIEnv *env, jobject bitmap) : pixels(NULL), jenv(env), jbitmap(bitmap) {
        if ((result = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
            ALOGE("bitmap init failed ! error=%d", result);
            return;
        }
        if (info.format != checkFormat) {
            ALOGE("Bitmap format is not your selection !");
            return;
        }
        if ((result = AndroidBitmap_lockPixels(env, bitmap, (void **) &pixels)) < 0) {
            ALOGE("bitmap get pixels failed ! error=%d", result);
        }
    }

    ~Bitmap() {
        if (jenv)
            AndroidBitmap_unlockPixels(jenv, jbitmap);
        else
            free(pixels);
    }

    ABsize getHeight() {
        return jenv ? info.height : height;
    }

    ABsize getWidth() {
        return jenv ? info.width : width;
    }

    ABformat getType() {
        return checkFormat;
    }

    int getErrorCode() {
        return result;
    }

    operator APixel *() {
        return pixels;
    }

    APixel *operator[](int y) {
        if (y >= getHeight()) return NULL;
        return pixels + y * getWidth();
    }

};

#endif //NDK_BITMAP_H
