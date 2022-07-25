cmake_minimum_required(VERSION 3.10)

project(LidaPath)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

add_library(LidaPath LidaPath.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./)

IF(MSVC)
    ADD_DEFINITIONS("/EHsc")
ENDIF(MSVC)

cmake_policy(SET CMP0074 NEW)
find_package(Boost)
if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS}) 
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})
endif()

#add_dependencies(LidaPath XPSTest)

add_subdirectory(XPSHelper)
target_link_libraries(LidaPath PUBLIC XPSHelper)
target_include_directories(LidaPath PUBLIC XPSHelper)

add_subdirectory(RArea)
target_link_libraries(LidaPath PUBLIC RArea)
target_include_directories(LidaPath PUBLIC RArea)

add_subdirectory(Block)
target_link_libraries(LidaPath PUBLIC Block)
target_include_directories(LidaPath PUBLIC Block)

add_subdirectory(Snake)
target_link_libraries(LidaPath PUBLIC Snake)
target_include_directories(LidaPath PUBLIC Snake)

add_subdirectory(BlockGraph)
target_link_libraries(LidaPath PUBLIC BlockGraph)
target_include_directories(LidaPath PUBLIC BlockGraph)

add_subdirectory(Board)
target_link_libraries(LidaPath PUBLIC Board)
target_include_directories(LidaPath PUBLIC Board)

add_subdirectory(PathHelper)
target_link_libraries(LidaPath PUBLIC PathHelper)
target_include_directories(LidaPath PUBLIC PathHelper)