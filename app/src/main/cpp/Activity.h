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

#ifndef NDK_ACTIVITY_H
#define NDK_ACTIVITY_H

#include <android_native_app_glue.h>

typedef int32_t Abool;
typedef int32_t ACMD;
typedef int AlooperId;
typedef void *Bundle;
#define ATRUE 1
#define AFALSE 0

class Activity {
protected:
    struct android_app *context;
    AlooperId ID;
    Bundle bundle;

    friend void android_main(struct android_app *state);

public:
    Activity() : context(NULL), bundle(NULL) { }

    ~Activity() { }

    void onCreate(Bundle savedInstanceState);

    void onStart();

    void onResume();

    void onPause();

    void onStop();

    void onDestroy();

    Bundle onSaveInstanceState();

    Abool onTouchEvent(AInputEvent *event);
};

void dispatch(struct android_app *app, ACMD cmd);

Abool onTouchEvent(struct android_app *app, AInputEvent *event);

#endif //NDK_ACTIVITY_H
