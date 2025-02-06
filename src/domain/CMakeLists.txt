set(TARGET_SUFFIX domain)
set(TARGET_NAME ${PROJECT_NAME}-${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC
    ${SRCROOT}/entity/Uuid.hpp
    ${SRCROOT}/entity/User.hpp
    
    ${SRCROOT}/model/Room.hpp
    ${SRCROOT}/model/Room.cpp
    
    ${SRCROOT}/model/round_pipe/ForceNominatePlayerCardPipe.hpp
    ${SRCROOT}/model/round_pipe/ForceNominatePlayerCardPipe.cpp
    ${SRCROOT}/model/round_pipe/RaisePlayerCardPipe.hpp
    ${SRCROOT}/model/round_pipe/RaisePlayerCardPipe.cpp
    ${SRCROOT}/model/round_pipe/ComputePlayerWinnerPipe.hpp
    ${SRCROOT}/model/round_pipe/ComputePlayerWinnerPipe.cpp

    ${SRCROOT}/interface/UserStorage.hpp
    ${SRCROOT}/interface/RoomStorage.hpp
    ${SRCROOT}/interface/UuidGenerator.hpp
    ${SRCROOT}/interface/Timer.hpp

    ${SRCROOT}/handler/RegisterCommandHandler.hpp
    ${SRCROOT}/handler/RegisterCommandHandler.cpp
    ${SRCROOT}/handler/CreateRoomCommandHandler.hpp
    ${SRCROOT}/handler/CreateRoomCommandHandler.cpp
    ${SRCROOT}/handler/ConnectToRoomCommandHandler.hpp
    ${SRCROOT}/handler/ConnectToRoomCommandHandler.cpp
    ${SRCROOT}/handler/StartGameCommandHandler.hpp
    ${SRCROOT}/handler/StartGameCommandHandler.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} PUBLIC RockPaperScissorsProtocol::RockPaperScissorsProtocol)