cmake_minimum_required(VERSION 3.5)

project(m3u8 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".LIB" ".dll" ".DLL" ".dylib")
set(FFMPEG_DIR "/opt/homebrew/Cellar/ffmpeg/7.0.1")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIRS})
include_directories(/Users/hua/file/project/源码/cpp-httplib-0.16.0)
#include_directories(${FFMPEG_DIR}/include)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        component/customlineedit.cpp
        component/customlineedit.h
        component/customtextedit.cpp
        component/customtextedit.h
        component/progresscard.cpp
        component/progresscard.h
        tools/threadpool.h
        framelesswindow/framelesswindow.h
        framelesswindow/framelesswindow.cpp
        framelesswindow/framelesswindow.mm
        resource/res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(m3u8
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
            tools/utils.h tools/utils.cpp
            tools/m3u8.h tools/m3u8.cpp
        component/pathselectedit.h component/pathselectedit.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET m3u8 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(m3u8 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(m3u8
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(m3u8 PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(m3u8 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#file(GLOB_RECURSE FFMPEG_LIBRARIES "${FFMPEG_DIR}/lib/*.dylib")
## 遍历找到的所有库文件
#foreach(FFMPEG_LIB ${FFMPEG_LIBRARIES})
#    message(${FFMPEG_LIBRARIES})
#    # 添加库到目标
#    target_link_libraries(m3u8 PRIVATE ${FFMPEG_LIB})
#endforeach()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.m3u8)
endif()
set_target_properties(m3u8 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS m3u8
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(m3u8)
endif()
