
if(BUILD_TESTING)
    project(dataParserTests LANGUAGES CXX)
    find_package(GTest REQUIRED)

    file(GLOB SOURCES CONFIG_DEPENDS "*Tests.cpp")

    add_executable(dataParserTests ${SOURCES})

    target_link_libraries(dataParserTests dataParser data gmock gtest gtest_main)

    target_include_directories(dataParserTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    add_test(NAME DataParser_tests COMMAND dataParserTests)
    include(GoogleTest)

    gtest_discover_tests(dataParserTests
        EXTRA_ARGS --gtest_output=json:${CMAKE_BINARY_DIR}/test_results/DataParser/)
endif()
