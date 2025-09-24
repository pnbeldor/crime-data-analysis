
if(BUILD_TESTING)
    file(GLOB SOURCES CONFIG_DEPENDS "*Tests.cpp")

    add_executable(dataTest ${SOURCES})

    target_link_libraries(dataTest PRIVATE gmock gtest gtest_main)
    target_link_libraries(dataTest PRIVATE data)

    target_include_directories(dataTest PUBLIC "${PROJECT_BINARY_DIR}")

    add_test(NAME DataTests COMMAND dataTest)
    include(GoogleTest)

    gtest_discover_tests(dataTest)
endif()
