cmake_minimum_required(VERSION 3.4.1)
#设置编译指令
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -std=c++11 -fno-rtti -fno-exceptions -Wall")
#如果当前系统版本过低设置拒绝编译
if (${ANDROID_PLATFORM_LEVEL} LESS 11)
  message(FATAL_ERROR "OpenGL 2 is not supported before API level 11 (currently using ${ANDROID_PLATFORM_LEVEL}).")
  return()
elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
  add_definitions("-DDYNAMIC_ES3")
  set(OPENGL_LIB GLESv2)
else ()
  set(OPENGL_LIB GLESv3)
endif (${ANDROID_PLATFORM_LEVEL} LESS 11)

add_library(app-glue STATIC
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

add_library(ndk-lib SHARED
            src/main/cpp/JniUtil.cpp
            src/main/cpp/hello-jni.cpp
            src/main/cpp/hello-java.cpp
            src/main/cpp/native-activity.cpp
            src/main/cpp/bitmap.cpp)

target_include_directories(ndk-lib PRIVATE
                           ${ANDROID_NDK}/sources/android/native_app_glue)

target_link_libraries(ndk-lib
                      android
                      jnigraphics
                      app-glue
                      EGL
                      log
                      m)
