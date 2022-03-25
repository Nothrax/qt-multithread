CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(QTMultithread)

SET(CMAKE_CXX_STANDARD 17)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOUIC ON)

if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

FIND_PACKAGE(Qt5 COMPONENTS Widgets REQUIRED)
SET(QT5_MODULES Widgets)
FIND_PACKAGE(Qt5 REQUIRED COMPONENTS ${QT5_MODULES})

#[[FILE(GLOB_RECURSE source_files "source/*")
ADD_LIBRARY(qt_multithread_lib STATIC ${source_files})
TARGET_INCLUDE_DIRECTORIES(qt_multithread_lib PUBLIC "include/")
TARGET_LINK_LIBRARIES(qt_multithread_lib PUBLIC Qt5::Widgets)]]

ADD_EXECUTABLE(QTMultithread main.cpp mainwindow.cpp mainwindow.h Controller.cpp Controller.hpp Worker.cpp Worker.hpp)
TARGET_LINK_LIBRARIES(QTMultithread PUBLIC Qt5::Widgets)