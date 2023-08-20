cmake_minimum_required(VERSION 3.25)
project(polarspectrogram)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)

find_package(Qt5
        COMPONENTS
        Widgets
        REQUIRED
)



find_package(Qwt
        PATHS
            ${PROJECT_SOURCE_DIR}/../../install/lib/
        REQUIRED
        NO_DEFAULT_PATH
)

add_executable(${PROJECT_NAME}
        main.cpp
        Plot.cpp
        PlotWindow.cpp
        Plot.h
        PlotWindow.h
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt::Widgets
        Qwt::qwt
)