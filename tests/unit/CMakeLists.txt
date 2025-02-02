set(TARGET_NAME ${PROJECT_NAME}-unit-tests)

find_package(GTest CONFIG REQUIRED)

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC 
    ${SRCROOT}/mock/storage/UserStorageMock.hpp
    ${SRCROOT}/mock/storage/RoomStorageMock.hpp

    ${SRCROOT}/mock/client/UserClientMock.hpp

    ${SRCROOT}/fixture/command/RegisterCommandFixture.hpp
    ${SRCROOT}/fixture/command/CreateRoomCommandFixture.hpp
    ${SRCROOT}/fixture/command/ConnectToRoomCommandFixture.hpp

    ${SRCROOT}/src/command/ConnectToRoomCommandTest.cpp
    ${SRCROOT}/src/command/RegisterCommandTest.cpp
    ${SRCROOT}/src/command/CreateRoomCommandTest.cpp
)

add_executable(${TARGET_NAME} ${SRC})

target_link_libraries(${TARGET_NAME} 
    ${PROJECT_NAME}::domain
    GTest::gtest_main 
    GTest::gmock_main 
)

target_include_directories(${TARGET_NAME} PRIVATE ${SRCROOT})

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
