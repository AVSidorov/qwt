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
        ${qwt_src}/*.h
)

add_library(qwt SHARED ${QWT_SOURCES})

target_compile_definitions(qwt PUBLIC QWT_MOC_INCLUDE=1 QT_NO_DEBUG QT_NO_KEYWORDS)
target_link_libraries(qwt
        PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        Qt::OpenGL
        Qt::Concurrent
        Qt::PrintSupport
)
