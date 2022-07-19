add_library(Snake Snake.cpp)

target_link_libraries(Snake PUBLIC XPSHelper)
target_include_directories(Snake PUBLIC XPSHelper)

target_link_libraries(Snake PUBLIC Block)
target_include_directories(Snake PUBLIC Block)