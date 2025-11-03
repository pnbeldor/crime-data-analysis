
if(BUILD_TESTING)
    project(utilsTests LANGUAGES CXX)
    find_package(GTest REQUIRED)

    file(GLOB SOURCES CONFIG_DEPENDS "*Tests.cpp")

    add_executable(utilsTests ${SOURCES})

    target_link_libraries(utilsTests data gmock gtest gtest_main)

    target_include_directories(utilsTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    add_test(NAME utils_tests COMMAND utilsTests)
    include(GoogleTest)

    gtest_discover_tests(utilsTests
        EXTRA_ARGS --gtest_output=json:${CMAKE_BINARY_DIR}/test_results/utils/)
endif()
