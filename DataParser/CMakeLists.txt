
add_library(dataParser)

file(GLOB SOURCES CONFIG_DEPENDS "src/*.cpp")
target_sources(dataParser PRIVATE ${SOURCES})

target_include_directories(dataParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(dataParser dataSource data -lcurl -ljsoncpp)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
