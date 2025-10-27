
if(BUILD_TESTING)
    project(dataSourceTests LANGUAGES CXX)
    find_package(GTest REQUIRED)

    file(GLOB SOURCES CONFIG_DEPENDS "*Tests.cpp")

    add_executable(dataSourceTests ${SOURCES})

    target_link_libraries(dataSourceTests data gmock gtest gtest_main)

    target_include_directories(dataSourceTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    add_test(NAME DataSource_tests COMMAND dataSourceTests)
    set_tests_properties(DataSource_tests PROPERTIES TIMEOUT 30)
    include(GoogleTest)

    gtest_discover_tests(dataSourceTests
        EXTRA_ARGS --gtest_output=json:${CMAKE_BINARY_DIR}/test_results/DataSource/)
endif()
