
if(BUILD_TESTING)
    file(GLOB SOURCES CONFIG_DEPENDS "*Tests.cpp")

    add_executable(CrimeIncidentsTest ${SOURCES})

    target_link_libraries(CrimeIncidentsTest PUBLIC gmock gtest gtest_main)
    target_link_libraries(CrimeIncidentsTest PUBLIC crimeAnalysis)

    target_include_directories(CrimeIncidentsTest PUBLIC "${PROJECT_BINARY_DIR}")

    add_test(NAME crimeDataTest COMMAND CrimeIncidentsTest)
    include(GoogleTest)

    gtest_discover_tests(CrimeIncidentsTest)
endif()