
if(BUILD_TESTING)
    project(dataTests LANGUAGES CXX)
    find_package(GTest REQUIRED)

    file(GLOB SOURCES CONFIG_DEPENDS "*Tests.cpp")

    add_executable(dataTests ${SOURCES})

    target_link_libraries(dataTests data gmock gtest gtest_main)

    target_include_directories(dataTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    add_test(NAME Data_tests COMMAND dataTests)
    include(GoogleTest)

    gtest_discover_tests(dataTests
        EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results/DataCenter/)
endif()
