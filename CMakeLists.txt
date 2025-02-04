cmake_minimum_required(VERSION 3.25)

set(CMAKE_AUTOMOC ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(TRUE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
endif()

project(RockPaperScissorsServer)

add_subdirectory(libs/RockPaperScissorsProtocol)

add_subdirectory(src)

if(TRUE)
    add_subdirectory(tests/unit)
endif()
