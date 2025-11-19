
add_library(utils)

file(GLOB SOURCES CONFIG_DEPENDS "src/*.cpp")
target_sources(utils PRIVATE ${SOURCES})

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(utils simdjson)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
