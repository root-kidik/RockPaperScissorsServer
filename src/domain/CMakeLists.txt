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
    ${SRCROOT}/model/round_pipe/DealMissingCardsPipe.hpp
    ${SRCROOT}/model/round_pipe/DealMissingCardsPipe.cpp

    ${SRCROOT}/interface/UserStorage.hpp
    ${SRCROOT}/interface/RoomStorage.hpp
    ${SRCROOT}/interface/UuidGenerator.hpp
    ${SRCROOT}/interface/Timer.hpp

    ${SRCROOT}/handler/Register.hpp
    ${SRCROOT}/handler/Register.cpp
    ${SRCROOT}/handler/CreateRoom.hpp
    ${SRCROOT}/handler/CreateRoom.cpp
    ${SRCROOT}/handler/ConnectToRoom.hpp
    ${SRCROOT}/handler/ConnectToRoom.cpp
    ${SRCROOT}/handler/StartGame.hpp
    ${SRCROOT}/handler/StartGame.cpp
    ${SRCROOT}/handler/NominateCard.hpp
    ${SRCROOT}/handler/NominateCard.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} PUBLIC RockPaperScissorsProtocol::RockPaperScissorsProtocol)