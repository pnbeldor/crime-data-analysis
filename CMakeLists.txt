cmake_minimum_required(VERSION 3.31)
project(openDataAnalysis VERSION 0.1.0)

set(CMAKE_C_COMPILEER "/usr/bin/clang")
set(CMAKE_CXX_COMPILEER "/usr/bin/clang++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_TESTING "Build unit tests" ON)

include(CTest)
enable_testing()

configure_file(DataConfig.h.in DataFetchConfig.h)
set(RESOURCES_DIR "${PROJECT_SOURCE_DIR}/resources")

add_definitions(-DRESOURCES_PATH="${RESOURCES_DIR}")

#include(GnuInstallDirs)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG        1.9.6
)
FetchContent_MakeAvailable(jsoncpp)
#[[
FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG        curl-8_16_0
)
FetchContent_MakeAvailable(curl)
]]
FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG        v4.2.1
    GIT_SHALLOW TRUE)

#set(SIMDJSON_JUST_LIBRARY ON CACHE INTERNAL "")
#set(SIMDJSON_BUILD_SHARED_LIB ON CACHE INTERNAL "")

FetchContent_MakeAvailable(simdjson)

# FetchContent_Declare(
#     curlcpp
#     GIT_REPOSITORY https://github.com/JosephP91/curlcpp.git
#     GIT_TAG        3.1
# )
# FetchContent_MakeAvailable(curlcpp)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror -g -pg)
endif()

if(NOT WIN32)
    if(CMAKE_GENERATOR STREQUAL "Ninja" OR
        CMAKE_GENERATOR STREQUAL "Unix Makefiles")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fdiagnostics-color=always")
        
    endif()
endif()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

add_subdirectory(CrimeIncidents)
target_link_libraries(${PROJECT_NAME} PUBLIC crimeAnalysis)
add_subdirectory(DataCenter)
target_link_libraries(${PROJECT_NAME} PUBLIC data)
add_subdirectory(DataSource)
target_link_libraries(${PROJECT_NAME} PUBLIC data)
add_subdirectory(utils)
target_link_libraries(${PROJECT_NAME} PUBLIC utils)
add_subdirectory(DataParser)
target_link_libraries(${PROJECT_NAME} PUBLIC dataParser)

target_link_libraries(${PROJECT_NAME} PUBLIC gtest)

set(CMAKE_BUILD_TYPE, "Release")
target_compile_options(${PROJECT_NAME} PRIVATE -coverage)
target_link_options(${PROJECT_NAME} PRIVATE -coverage)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
