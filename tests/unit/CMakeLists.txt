set(TARGET_NAME ${PROJECT_NAME}-unit-tests)

find_package(GTest CONFIG REQUIRED)

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC 
    ${SRCROOT}/mock/storage/UserStorageMock.hpp
    ${SRCROOT}/mock/storage/RoomStorageMock.hpp

    ${SRCROOT}/mock/client/ConnectionMock.hpp

    ${SRCROOT}/mock/model/RoomMock.hpp

    ${SRCROOT}/mock/util/TimerMock.hpp

    ${SRCROOT}/fixture/handler/RegisterCommandFixture.hpp
    ${SRCROOT}/fixture/handler/CreateRoomCommandFixture.hpp
    ${SRCROOT}/fixture/handler/ConnectToRoomCommandFixture.hpp
    ${SRCROOT}/fixture/handler/StartGameCommandFixture.hpp

    ${SRCROOT}/fixture/model/RoomFixture.hpp

    ${SRCROOT}/fixture/model/round_pipe/ComputePlayerWinnerPipeFixture.hpp

    ${SRCROOT}/src/model/RoomTest.cpp
    
    ${SRCROOT}/src/model/round_pipe/ComputePlayerWinnerPipeTest.cpp

    ${SRCROOT}/src/handler/ConnectToRoomCommandHandlerTest.cpp
    ${SRCROOT}/src/handler/RegisterCommandHandlerTest.cpp
    ${SRCROOT}/src/handler/CreateRoomCommandHandlerTest.cpp
    ${SRCROOT}/src/handler/StartGameCommandHandlerTest.cpp
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
