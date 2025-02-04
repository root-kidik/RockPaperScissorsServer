set(TARGET_NAME ${PROJECT_NAME}-unit-tests)

find_package(GTest CONFIG REQUIRED)

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC 
    ${SRCROOT}/mock/storage/UserStorageMock.hpp
    ${SRCROOT}/mock/storage/RoomStorageMock.hpp

    ${SRCROOT}/mock/client/UserClientMock.hpp

    ${SRCROOT}/mock/utils/TimerMock.hpp

    ${SRCROOT}/fixture/command/RegisterCommandFixture.hpp
    ${SRCROOT}/fixture/command/CreateRoomCommandFixture.hpp
    ${SRCROOT}/fixture/command/ConnectToRoomCommandFixture.hpp
    ${SRCROOT}/fixture/command/StartGameCommandFixture.hpp

    ${SRCROOT}/src/command/ConnectToRoomCommandHandlerTest.cpp
    ${SRCROOT}/src/command/RegisterCommandHandlerTest.cpp
    ${SRCROOT}/src/command/CreateRoomCommandHandlerTest.cpp
    ${SRCROOT}/src/command/StartGameCommandHandlerTest.cpp
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
