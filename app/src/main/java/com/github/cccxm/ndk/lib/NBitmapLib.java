package com.github.cccxm.ndk.lib;

import android.graphics.Bitmap;

/**
 * project:NDK
 * Copyright (C) <2016>  <陈小默>
 * <p>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * <p>
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * <p>
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * <p>
 * Created by 陈小默 on 16/11/9.
 */
public class NBitmapLib {
    public static native void renderGray(Bitmap bitmap);

    public static void javaRenderGray(Bitmap bitmap) {
        int height = bitmap.getHeight();
        int width = bitmap.getWidth();

        int MODEL = 0xFF;
        int color;
        int av;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                av = 0;
                color = bitmap.getPixel(x, y);
                av += color & MODEL;
                av += (color >> 8) & MODEL;
                av += (color >> 16) & MODEL;
                av /= 3;
                color = 0xFF00 + av;
                color = (color << 8) + av;
                color = (color << 8) + av;
                bitmap.setPixel(x, y, color);
            }
        }
    }
}
