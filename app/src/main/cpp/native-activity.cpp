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

typedef struct {
    int number;
} Saved, *_Saved;

void Activity::onCreate(Bundle savedInstanceState) {
    //ALOGE("onCreate");
    if (savedInstanceState != NULL)
        bundle = savedInstanceState;
    else {
        bundle = new Saved;
        memset(bundle, 0, sizeof(Saved));
    }
}

void Activity::onStart() {
    //ALOGE("onStart");
}

void Activity::onResume() {
    //ALOGE("onResume");
    _Saved saved = (_Saved) bundle;
    ALOGE("current num is %d", saved->number);
}

void Activity::onPause() {
    //ALOGE("onPause");
}

void Activity::onStop() {
    //ALOGE("onStop");
}

void Activity::onDestroy() {
    //ALOGE("onDestroy");
}

Bundle Activity::onSaveInstanceState() {
    //ALOGE("onSaveInstanceState");
    return bundle;
}

Abool Activity::onTouchEvent(AInputEvent *event) {
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
//        float x = AMotionEvent_getX(event, 0);
//        float y = AMotionEvent_getY(event, 0);
//        ALOGE("X:%f,Y:%f", x, y);
        _Saved saved = (_Saved) bundle;
        saved->number += 1;
        ALOGE("current num is %d", saved->number);
        return ATRUE;
    }
    return AFALSE;
}