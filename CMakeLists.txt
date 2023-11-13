cmake_minimum_required(VERSION 3.10)

project(InteractiveChart)

find_package(Qt5 COMPONENTS Core Gui Widgets Charts REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(chart_sample main.cpp chart.cpp widget.cpp)
target_link_libraries(chart_sample Qt5::Core Qt5::Gui Qt5::Charts)
