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
#define LOG_TAG "native-activity"

#include "JniUtil.h"
#include "native-activity.h"
#include "triangle.h"

void
ANativeActivity_onCreate(ANativeActivity *activity, void *savedState, size_t savedStateSize) {
    ALOGE("onCreate");
    bindLifeCycle(activity);
}

void
onStart(ANativeActivity *activity) {
    ALOGE("onStart");
}

void
onResume(ANativeActivity *activity) {
    ALOGE("onResume");
}

void *
onSaveInstanceState(ANativeActivity *activity, size_t *outSize) {
    ALOGE("onSaveInstanceState");
    return NULL;
}

void
onPause(ANativeActivity *activity) {
    ALOGE("onPause");
}

void
onStop(ANativeActivity *activity) {
    ALOGE("onStop");
}

void
onDestroy(ANativeActivity *activity) {
    ALOGE("onDestroy");
}

void
onWindowFocusChanged(ANativeActivity *activity, int hasFocus) {
    ALOGE("onWindowFocusChanged");
}

static bool triangleShowing;
static pthread_t triangleID;

void *
triangleView(void *args) {
    TriangleContext *context = (TriangleContext *) args;
    if (triangleCreateWindow(context) && triangleInit(context)) {
        while (triangleShowing) {
            triangleStep(context);
            eglSwapBuffers(context->eglDisplay, context->eglSurface);
        }
        triangleDestroy(context);
    }
    else
        ALOGE("EGL window create error");
    return args;
}

void
onNativeWindowCreated(ANativeActivity *activity, ANativeWindow *window) {
    ALOGE("onNativeWindowCreated");
    triangleShowing = true;
    TriangleContext *context = new TriangleContext;
    memset(context, 0, sizeof(context));
    context->nativeActivity = activity;
    context->nativeWindow = window;
    if (0 != pthread_create(&triangleID, NULL, triangleView, context)) {
        ALOGE("Thread create error");
        delete context;
    }
}

void
onNativeWindowDestroyed(ANativeActivity *activity, ANativeWindow *window) {
    ALOGE("onNativeWindowDestroyed");
    triangleShowing = false;
}


static bool isLoop = false;
static pthread_t loopID;

void *
looper(void *args) {
    ANativeActivity *activity = (ANativeActivity *) args;
    AInputQueue *queue = (AInputQueue *) activity->instance;
    AInputEvent *event = NULL;
    while (isLoop) {
        if (!AInputQueue_hasEvents(queue))
            continue;
        AInputQueue_getEvent(queue, &event);
        switch (AInputEvent_getType(event)) {
            case AINPUT_EVENT_TYPE_MOTION: {
                switch (AMotionEvent_getAction(event)) {
                    case AMOTION_EVENT_ACTION_DOWN: {
                        float x = AMotionEvent_getX(event, 0);
                        float y = AMotionEvent_getY(event, 0);
                        ALOGE("X:%f,Y:%f", x, y);
                        break;
                    }
                    case AMOTION_EVENT_ACTION_UP: {
                        break;
                    }
                }
                break;
            }
            case AINPUT_EVENT_TYPE_KEY: {
                switch (AKeyEvent_getAction(event)) {
                    case AKEY_EVENT_ACTION_DOWN: {
                        switch (AKeyEvent_getKeyCode(event)) {
                            case AKEYCODE_BACK: {
                                ANativeActivity_finish(activity);
                                break;
                            }
                        }
                        break;
                    }
                    case AKEY_EVENT_ACTION_UP: {
                        break;
                    }
                }
            }
        }
        AInputQueue_finishEvent(queue, event, 1);
    }
    return args;
}

void
onInputQueueCreated(ANativeActivity *activity, AInputQueue *queue) {
    ALOGE("onInputQueueCreated");
    isLoop = true;
    activity->instance = (void *) queue;
    pthread_create(&loopID, NULL, looper, activity);
}

void
onInputQueueDestroyed(ANativeActivity *activity, AInputQueue *queue) {
    ALOGE("onInputQueueDestroyed");
    isLoop = false;
}

void
onLowMemory(ANativeActivity *activity) {
    ALOGE("onLowMemory");
}

void
bindLifeCycle(ANativeActivity *activity) {
    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onStop = onStop;
    activity->callbacks->onDestroy = onDestroy;
    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
    activity->callbacks->onLowMemory = onLowMemory;
}