set(TARGET_NAME ${PROJECT_NAME}-unit-tests)

find_package(GTest CONFIG REQUIRED)

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC 
    ${SRCROOT}/mock/storage/UserStorageMock.hpp
    ${SRCROOT}/mock/storage/RoomStorageMock.hpp

    ${SRCROOT}/mock/client/ConnectionMock.hpp

    ${SRCROOT}/mock/model/RoomMock.hpp

    ${SRCROOT}/mock/util/TimerMock.hpp

    ${SRCROOT}/fixture/handler/request/RegisterTest.hpp
    ${SRCROOT}/fixture/handler/request/CreateRoomTest.hpp
    ${SRCROOT}/fixture/handler/request/ConnectToRoomTest.hpp
    ${SRCROOT}/fixture/handler/request/StartGameTest.hpp
    ${SRCROOT}/fixture/handler/request/NominateCardTest.hpp

    ${SRCROOT}/fixture/model/RoomTest.hpp

    ${SRCROOT}/fixture/model/round_pipe/ComputePlayerWinnerTest.hpp
    ${SRCROOT}/fixture/model/round_pipe/ForceNominatePlayerCardTest.hpp
    ${SRCROOT}/fixture/model/round_pipe/RaisePlayerCardTest.hpp
    ${SRCROOT}/fixture/model/round_pipe/DealMissingCardsTest.hpp

    ${SRCROOT}/src/model/RoomTest.cpp
    
    ${SRCROOT}/src/model/round_pipe/ComputePlayerWinnerTest.cpp
    ${SRCROOT}/src/model/round_pipe/ForceNominatePlayerCardTest.cpp
    ${SRCROOT}/src/model/round_pipe/RaisePlayerCardTest.cpp
    ${SRCROOT}/src/model/round_pipe/DealMissingCardsTest.cpp

    ${SRCROOT}/src/handler/request/ConnectToRoomTest.cpp
    ${SRCROOT}/src/handler/request/RegisterTest.cpp
    ${SRCROOT}/src/handler/request/CreateRoomTest.cpp
    ${SRCROOT}/src/handler/request/StartGameTest.cpp
    ${SRCROOT}/src/handler/request/NominateCardTest.cpp
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
