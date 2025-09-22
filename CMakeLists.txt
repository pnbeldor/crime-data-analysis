cmake_minimum_required(VERSION 4.1.0)
project(crime-analysis VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Whether to build unit tests" ON)

#include(GnuInstallDirs)

# Enable all compiler warnings and treat as errors

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

if(NOT WIN32)
    if(CMAKE_GENERATOR STREQUAL "Ninja" OR
        CMAKE_GENERATOR STREQUAL "Unix Makefiles")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_}-fdiagnostics-color=always")
        
    endif()
endif()


add_library(crime-analysis)

file(GLOB SOURCES CONFIG_DEPENDS "src/*.cpp")
target_sources(crime-analysis PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/jsoncpp)
target_link_libraries(crime-analysis -lcurl -ljsoncpp)

if(BUILD_TESTS)
    include(CTest)
    enable_testing()

    #find_package(GTests 1.17.0 REQUIRED NO_MODULE)
    add_subdirectory(test)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
