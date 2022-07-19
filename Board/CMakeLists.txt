set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

add_library(Board Board.cpp)

target_link_libraries(Board PUBLIC XPSHelper)
target_include_directories(Board PUBLIC XPSHelper)

target_link_libraries(Board PUBLIC Block)
target_include_directories(Board PUBLIC Block)

target_link_libraries(Board PUBLIC BlockGraph)
target_include_directories(Board PUBLIC BlockGraph)

target_link_libraries(Board PUBLIC Snake)
target_include_directories(Board PUBLIC Snake)