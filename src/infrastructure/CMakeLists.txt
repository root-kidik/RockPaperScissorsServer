set(TARGET_SUFFIX infrastructure)
set(TARGET_NAME ${PROJECT_NAME}-${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC 
    ${SRCROOT}/client/TcpSocketUserConnection.hpp
    ${SRCROOT}/client/TcpSocketUserConnection.cpp

    ${SRCROOT}/generator/UuidGenerator.hpp
    ${SRCROOT}/generator/UuidGenerator.cpp

    ${SRCROOT}/storage/MemoryUserStorage.hpp
    ${SRCROOT}/storage/MemoryUserStorage.cpp
    ${SRCROOT}/storage/MemoryRoomStorage.hpp
    ${SRCROOT}/storage/MemoryRoomStorage.cpp

    ${SRCROOT}/util/QtTimer.hpp
    ${SRCROOT}/util/QtTimer.cpp

    ${SRCROOT}/Server.hpp
    ${SRCROOT}/Server.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

find_package(Qt6 COMPONENTS Core Network REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC Qt6::Core Qt6::Network ${PROJECT_NAME}::domain)
