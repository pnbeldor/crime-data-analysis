#include "CSVDataLoader.h"


add_library(crimeAnalysis)

file(GLOB SOURCES CONFIG_DEPENDS "src/*.cpp")
target_sources(crimeAnalysis PRIVATE ${SOURCES})

target_include_directories(crimeAnalysis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(crimeAnalysis PUBLIC data dataSource dataParser)

add_subdirectory(test)
