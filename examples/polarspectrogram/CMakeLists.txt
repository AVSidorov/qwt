cmake_minimum_required(VERSION 3.25)
project(polarspectrogram)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME}
        main.cpp
        Plot.cpp
        PlotWindow.cpp
)

target_compile_definitions(${PROJECT_NAME} PUBLIC QT_DLL QWT_DLL)

find_package(Qt5
        COMPONENTS
        Widgets
        REQUIRED
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Qt::Widgets
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("use debug lib")
    set(subfolder debug)
else()
    set(subfolder "")
endif()

find_package(Qwt
        PATHS
            ${PROJECT_SOURCE_DIR}/../../instal/${subfolder}/lib/cmake/
        REQUIRED
        NO_DEFAULT_PATH
)

message("Qwt_DIR ${Qwt_DIR}")
message("Qwt_INCLUDE_DIR ${Qwt_INCLUDE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE Qwt::qwt)