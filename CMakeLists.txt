cmake_minimum_required(VERSION 3.0.0)

set( cmake_verbose_makefile TRUE )
set( cmake_automoc ON )
set( cmake_include_current_dir ON )

PROJECT(qtjsbsim)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)
FIND_PACKAGE(Qt5Svg REQUIRED)
FIND_PACKAGE(Qt5WebKitWidgets REQUIRED)

INCLUDE_DIRECTORIES( ${Qt5Widgets_INCLUDES} )
INCLUDE_DIRECTORIES( ${Qt5Network_INCLUDES} )
INCLUDE_DIRECTORIES( ${Qt5Svg_INCLUDES} )
INCLUDE_DIRECTORIES( ${Qt5WebKitWidgets_INCLUDES} )

ADD_DEFINITIONS( ${Qt5Widgets_DEFINITIONS} )

set( CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}" )

if(WIN32)
  set (QT_USE_QTMAIN TRUE)
endif(WIN32)

set(ENABLE_PLIB_JOYSTICK 1)
find_package(PLIB REQUIRED js)

ADD_SUBDIRECTORY(src)

