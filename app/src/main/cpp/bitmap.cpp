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
#define LOG_TAG "bitmap"

#define ARGB_4444

#include "Bitmap.h"

extern "C"
JNIEXPORT void JNICALL Java_com_github_cccxm_ndk_lib_NBitmapLib_renderGray(JNIEnv *env,
                                                                           jobject obj,
                                                                           jobject bitmap) {
    Bitmap bm(env, bitmap);
    ABsize height = bm.getHeight();
    ABsize width = bm.getWidth();

    const APixel MODEL = 0xF;
    APixel color;
    APixel av;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            av = 0;
            color = bm[y][x];
            av += (color >>= 4) & MODEL;
            av += (color >>= 4) & MODEL;
            av += (color >> 4) & MODEL;
            av /= 3;
            color = av;
            color = (color << 4) + av;
            color = (color << 4) + av;
            bm[y][x] = color << 4;
        }
    }
}
