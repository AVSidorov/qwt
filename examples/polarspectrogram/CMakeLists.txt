cmake_minimum_required(VERSION 3.25)
project(polarspectrogram)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5
        COMPONENTS
        Widgets
        Svg
        REQUIRED
)



find_library(libqwt
        NAMES
            libqwt.so.6.3.0
            libqwt.so
        PATHS
#            ${PROJECT_SOURCE_DIR}/../../lib/
            ${PROJECT_SOURCE_DIR}/
        REQUIRED
        NO_DEFAULT_PATH
)

message("libqwt ${libqwt}")

add_library(qwt INTERFACE)

target_link_libraries(qwt INTERFACE ${libqwt})

add_executable(${PROJECT_NAME}
        main.cpp
        Plot.cpp
        PlotWindow.cpp
        Plot.h
        PlotWindow.h
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/../../src
        ${PROJECT_SOURCE_DIR}/../../classincludes
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt::Widgets
        Qt::Svg
        qwt
)