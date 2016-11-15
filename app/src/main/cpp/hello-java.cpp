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
#include <jni.h>

static int count;

extern "C"
JNIEXPORT void JNICALL
Java_com_github_cccxm_ndk_view_HelloJavaActivity_callback(JNIEnv *env,
                                                          jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID method = env->GetMethodID(activityClass, "setText", "(I)V");
    env->CallVoidMethod(activity, method, count += 1);
}