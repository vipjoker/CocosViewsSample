#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 3.1)

set(APP_NAME MyGame)
project(${APP_NAME})
set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

SET( USE_BOX2D ON CACHE BOOL "Turn on Box2D for 2D physics" )


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)


if (MACOSX OR APPLE)
    ADD_DEFINITIONS(-DCC_TARGET_OS_MAC)
    ADD_DEFINITIONS(-DUSE_FILE32API)
    set(PLATFORM_FOLDER mac)
elseif (LINUX)
    ADD_DEFINITIONS(-DLINUX)
    set(PLATFORM_FOLDER linux)
elseif (ANDROID)
    ADD_DEFINITIONS(-DUSE_FILE32API)
    set(PLATFORM_FOLDER android)
else ()
    message(FATAL_ERROR "Unsupported platform, CMake will exit")
endif ()


# Compiler options
if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt /NODEFAULTLIB:libcmt")
    else ()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt")
    endif ()
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
            -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
            -wd4514 -wd4056 -wd4996 -wd4099)
else ()
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        ADD_DEFINITIONS(-DCOCOS2D_DEBUG=1)
    endif ()
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
    if (CLANG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif ()
endif (MSVC)

set(PLATFORM_SPECIFIC_SRC)
set(PLATFORM_SPECIFIC_HEADERS)

if (MACOSX OR APPLE)
    set(PLATFORM_SPECIFIC_SRC
            proj.ios_mac/mac/main.cpp)
elseif (LINUX)
    set(PLATFORM_SPECIFIC_SRC
            proj.linux/main.cpp)

elseif (ANDROID)
    set(PLATFORM_SPECIFIC_SRC
            proj.android-studio/app/jni/hellocpp/main.cpp)
endif ()

include_directories(
        /usr/local/include/GLFW
        /usr/include/GLFW
        ${COCOS2D_ROOT}
        ${COCOS2D_ROOT}/cocos
        ${COCOS2D_ROOT}/external
        ${COCOS2D_ROOT}/cocos/platform
        ${COCOS2D_ROOT}/cocos/audio/include/
        Classes
)

set(GAME_SRC
        Classes/AppDelegate.cpp
        Classes/CustomNodes/Ball.cpp
        Classes/CustomNodes/UiNode.cpp
#        Classes/loader/b2DebugDraw.cpp
#        Classes/loader/b2DebugLayer.cpp
#        Classes/loader/Box2dWorldLoader.cpp
        Classes/PhysicsDemo/PhysicsTest.cpp
        Classes/PhysicsDemo/VisibleRect.cpp
        Classes/Scenes/MenuScene.cpp
        Classes/Scenes/PhysicsScene.cpp
        Classes/Scenes/StartScene.cpp
        Classes/Box2dScene.cpp
        Classes/GLES-Render.cpp
        Classes/LetterNode.cpp
        ${PLATFORM_SPECIFIC_SRC}
        )

set(GAME_HEADERS
        Classes/AppDelegate.h
        Classes/CustomNodes/Ball.h
        Classes/CustomNodes/UiNode.h
#        Classes/loader/b2DebugDraw.h
#        Classes/loader/b2DebugLayer.h
#        Classes/loader/Box2dWorldLoader.h
        Classes/PhysicsDemo/PhysicsTest.h
        Classes/PhysicsDemo/VisibleRect.h
        Classes/Scenes/MenuScene.h
        Classes/Scenes/PhysicsScene.h
        Classes/Scenes/StartScene.h
        Classes/Box2dScene.h
        Classes/GLES-Render.h
        Classes/LetterNode.h
        ${PLATFORM_SPECIFIC_HEADERS}
        Classes/Scenes/EditorScene.cpp Classes/Scenes/EditorScene.h Classes/CustomNodes/Shape.cpp Classes/CustomNodes/Shape.h Classes/CustomNodes/Editable.cpp Classes/CustomNodes/Editable.h Classes/CustomNodes/FileChooserDialog.cpp Classes/CustomNodes/FileChooserDialog.h)


# Configure libcocos2d
set(BUILD_CPP_EMPTY_TEST OFF CACHE BOOL "turn off build cpp-empty-test")
set(BUILD_CPP_TESTS OFF CACHE BOOL "turn off build cpp-tests")
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua related targets")
set(BUILD_JS_LIBS OFF CACHE BOOL "turn off build js related targets")
add_subdirectory(${COCOS2D_ROOT})
add_subdirectory(../CocosViewsSample/cocos2d/external/Box2D)

# MyGame
if (ANDROID)
    add_library(${APP_NAME} SHARED ${GAME_SRC} ${GAME_HEADERS})
    IF (CMAKE_BUILD_TYPE MATCHES RELEASE)
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF ()
else ()
    add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})
endif ()

target_link_libraries(${APP_NAME} cocos2d box2d sqlite3)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")

if (WIN32)
    #also copying dlls to binary directory for the executable to run
    pre_build(${APP_NAME}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
            COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
            COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
            )
elseif (ANDROID)

else ()
    pre_build(${APP_NAME}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
            )

endif ()
