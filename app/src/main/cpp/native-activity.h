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
// Created by 陈小默 on 16/11/17.
//

#ifndef NDK_NATIVE_ACTIVITY_H
#define NDK_NATIVE_ACTIVITY_H

#include <android/native_activity.h>

/*
 * 绑定声明周期函数到activity
 */
void bindLifeCycle(ANativeActivity *activity);

/*
 * NativeActivity的入口函数
 */
void ANativeActivity_onCreate(ANativeActivity *activity, void *savedState, size_t savedStateSize);

/*
 * 处理事件队列的线程函数。
 */
void *looper(void *args);

void onStart(ANativeActivity *activity);

void onResume(ANativeActivity *activity);

void *onSaveInstanceState(ANativeActivity *activity, size_t *outSize);

void onPause(ANativeActivity *activity);

void onStop(ANativeActivity *activity);

void onDestroy(ANativeActivity *activity);

void onWindowFocusChanged(ANativeActivity *activity, int hasFocus);

void onNativeWindowCreated(ANativeActivity *activity, ANativeWindow *window);

//void onNativeWindowResized(ANativeActivity *activity, ANativeWindow *window);

//void onNativeWindowRedrawNeeded(ANativeActivity *activity, ANativeWindow *window);

void onNativeWindowDestroyed(ANativeActivity *activity, ANativeWindow *window);

void onInputQueueCreated(ANativeActivity *activity, AInputQueue *queue);

void onInputQueueDestroyed(ANativeActivity *activity, AInputQueue *queue);

//void onConfigurationChanged(ANativeActivity *activity);

void onLowMemory(ANativeActivity *activity);

#endif //NDK_NATIVE_ACTIVITY_H
