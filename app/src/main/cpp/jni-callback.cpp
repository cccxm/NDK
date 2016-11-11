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

extern "C"
JNIEXPORT void JNICALL
Java_com_github_cccxm_ndk_lib_JniCallbackLib_callback(JNIEnv *env, jclass type, jobject activity) {
    jclass cla_activity = env->FindClass("com/github/cccxm/ndk/view/JniCallbackActivity");
    jmethodID m_getCount = env->GetMethodID(cla_activity, "getCount", "()I");
    int count = env->CallIntMethod(activity, m_getCount);
    jmethodID m_setText = env->GetMethodID(cla_activity, "setText", "(I)V");
    env->CallVoidMethod(activity, m_setText, count + 1);
}