
add_library(dataSource)

file(GLOB SOURCES CONFIG_DEPENDS "src/*.cpp")
target_sources(dataSource PRIVATE ${SOURCES})

target_include_directories(dataSource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(dataSource -lcurl simdjson jsoncpp_lib)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
