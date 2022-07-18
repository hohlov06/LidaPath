set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

add_library(Block Block.cpp)
target_link_libraries(Block PUBLIC XPSHelper)
target_include_directories(Block PUBLIC XPSHelper)