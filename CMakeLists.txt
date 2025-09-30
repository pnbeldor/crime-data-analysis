cmake_minimum_required(VERSION 3.31)
project(openDataAnalysis VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_TESTING "Build unit tests" ON)

include(CTest)
enable_testing()

#include(GnuInstallDirs)

include(FetchContent)
#[[
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)
]]
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror -Ofast -g -lpthread)
endif()

if(NOT WIN32)
    if(CMAKE_GENERATOR STREQUAL "Ninja" OR
        CMAKE_GENERATOR STREQUAL "Unix Makefiles")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_}-fdiagnostics-color=always")
        
    endif()
endif()

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(CrimeIncidents)
target_link_libraries(${PROJECT_NAME} PUBLIC crimeAnalysis)
add_subdirectory(DataCenter)
target_link_libraries(${PROJECT_NAME} PUBLIC data)
add_subdirectory(DataSource)
target_link_libraries(${PROJECT_NAME} PUBLIC dataSource)
add_subdirectory(DataParser)
target_link_libraries(${PROJECT_NAME} PUBLIC dataParser)

target_link_libraries(${PROJECT_NAME} PUBLIC gtest)

set(CMAKE_BUILD_TYPE, "Debug")
target_compile_options(${PROJECT_NAME} PRIVATE -coverage)
target_link_options(${PROJECT_NAME} PRIVATE -coverage)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
