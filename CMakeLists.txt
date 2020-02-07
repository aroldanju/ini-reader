project(ini-reader C)

add_definitions(-D__INI_DEBUG__)

file(GLOB SOURCES_INI src/*.h src/*.c)

add_library(${PROJECT_NAME} ${SOURCES_INI})
add_library(dependencies::ini-reader ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

project(ini-reader-sample C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../sample)
add_executable(ini-reader-sample sample/sample.c)
target_link_libraries(ini-reader-sample dependencies::ini-reader)