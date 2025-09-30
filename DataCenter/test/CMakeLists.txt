
if(BUILD_TESTING)
    project(data_tests LANGUAGES CXX)
    find_package(GTest REQUIRED)

    file(GLOB SOURCES CONFIG_DEPENDS "*Tests.cpp")

    add_executable(data_tests ${SOURCES})

    target_link_libraries(data_tests data gmock gtest gtest_main)

    target_include_directories(data_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    add_test(NAME Data_tests COMMAND data_tests)
    include(GoogleTest)

    gtest_discover_tests(data_tests
        EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results/DataCenter/)
endif()
