cmake_minimum_required(VERSION 3.0)

project(config)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/json/include
    ${CMAKE_CURRENT_SOURCE_DIR}/trace/include)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Config.cpp)

add_subdirectory(trace)

include_directories(${INCLUDES})

add_library(configlib STATIC ${SOURCES})
link_libraries(configlib tracelib)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/config.cpp)