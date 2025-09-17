

add_executable(crimeDataAnalysisTest CrimeDataAnalysis_tests.cpp)

target_link_libraries(crimeDataAnalysisTest PUBLIC gmock gtest gtest_main)
target_link_libraries(crimeDataAnalysisTest PUBLIC crime-analysis)

target_include_directories(crimeDataAnalysisTest PUBLIC "${PROJECT_BINARY_DIR}")

ADD_TEST(NAME crimeDataTest COMMAND crimeDataAnalysisTest)
include(GoogleTest)

gtest_discover_tests(crimeDataAnalysisTest)
