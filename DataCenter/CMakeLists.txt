
add_library(data)

file(GLOB SOURCES CONFIG_DEPENDS "src/*.cpp")
target_sources(data PRIVATE ${SOURCES})

target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(data -lcurl -ljsoncpp)

add_subdirectory(test)