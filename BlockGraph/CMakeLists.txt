set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

add_library(BlockGraph BlockGraph.cpp)

target_link_libraries(BlockGraph PUBLIC XPSHelper)
target_include_directories(BlockGraph PUBLIC XPSHelper)

target_link_libraries(BlockGraph PUBLIC Block)
target_include_directories(BlockGraph PUBLIC Block)