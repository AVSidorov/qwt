cmake_minimum_required(VERSION 3.25)
project(qwt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5
        COMPONENTS
        Core
        Gui
        Widgets
        Svg
        OpenGL
        Concurrent
        PrintSupport
        REQUIRED
)

#set(CMAKE_VERBOSE_MAKEFILE ON) # for output in CLion

cmake_path(SET qwt_dir NORMALIZE ${PROJECT_SOURCE_DIR})
cmake_path(SET qwt_src NORMALIZE ${PROJECT_SOURCE_DIR}/src)
cmake_path(SET qwt_classincludes NORMALIZE ${PROJECT_SOURCE_DIR}/classincludes)

message("qwt dir: ${qwt_dir}")
message("qwt sources dir: ${qwt_src}")
message("qwt classincludes dir: ${qwt_classincludes}")

file(GLOB QWT_SOURCES
    LIST_DIRECTORIES true
    RELATIVE ${PROJECT_SOURCE_DIR}
        ${qwt_src}/*.cpp
)

file(GLOB QWT_HEADERS
        LIST_DIRECTORIES true
        RELATIVE ${PROJECT_SOURCE_DIR}
        ${qwt_src}/*.h
)

file(GLOB QWT_CLASSINCLUDES
        LIST_DIRECTORIES true
        RELATIVE ${PROJECT_SOURCE_DIR}
        ${qwt_classincludes}/*
)

list(REMOVE_ITEM QWT_CLASSINCLUDES classincludes/classincludes.pro)


add_library(qwt SHARED)

target_sources(qwt
        PRIVATE
            ${QWT_SOURCES}
        PUBLIC FILE_SET qwt_header_set  TYPE HEADERS  BASE_DIRS ${qwt_src} FILES ${QWT_HEADERS}
        INTERFACE FILE_SET qwt_classincludes_set TYPE HEADERS BASE_DIRS ${qwt_classincludes} FILES ${QWT_CLASSINCLUDES}
)

target_include_directories(qwt
        PUBLIC
        $<BUILD_INTERFACE:${qwt_src}>
        $<INSTALL_INTERFACE:${INCLUDEDIR}>
        $<INSTALL_INTERFACE:${LIBDIR}>
)

target_compile_definitions(qwt PUBLIC QWT_MOC_INCLUDE=1 QT_NO_DEBUG QT_NO_KEYWORDS)

target_link_libraries(qwt
        PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        Qt::OpenGL
        Qt::Concurrent
        Qt::PrintSupport
)

include(GNUInstallDirs)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install/ CACHE PATH "install prefix" FORCE)

install(TARGETS qwt
        EXPORT Qwt
        FILE_SET qwt_header_set
        FILE_SET qwt_classincludes_set
)

install(EXPORT Qwt
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        NAMESPACE Qwt::
)

install(FILES qwt-config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR})

