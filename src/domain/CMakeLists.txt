set(TARGET_SUFFIX domain)
set(TARGET_NAME ${PROJECT_NAME}-${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC
    ${SRCROOT}/entity/Uuid.hpp
    ${SRCROOT}/entity/User.hpp
    
    ${SRCROOT}/model/Room.hpp
    ${SRCROOT}/model/Room.cpp
    
    ${SRCROOT}/model/round_pipe/ForceNominatePlayerCard.hpp
    ${SRCROOT}/model/round_pipe/ForceNominatePlayerCard.cpp
    ${SRCROOT}/model/round_pipe/RaisePlayerCard.hpp
    ${SRCROOT}/model/round_pipe/RaisePlayerCard.cpp
    ${SRCROOT}/model/round_pipe/ComputePlayerWinner.hpp
    ${SRCROOT}/model/round_pipe/ComputePlayerWinner.cpp
    ${SRCROOT}/model/round_pipe/DealMissingCards.hpp
    ${SRCROOT}/model/round_pipe/DealMissingCards.cpp

    ${SRCROOT}/interface/UserStorage.hpp
    ${SRCROOT}/interface/RoomStorage.hpp
    ${SRCROOT}/interface/UuidGenerator.hpp
    ${SRCROOT}/interface/Timer.hpp

    ${SRCROOT}/handler/request/Register.hpp
    ${SRCROOT}/handler/request/Register.cpp
    ${SRCROOT}/handler/request/CreateRoom.hpp
    ${SRCROOT}/handler/request/CreateRoom.cpp
    ${SRCROOT}/handler/request/ConnectToRoom.hpp
    ${SRCROOT}/handler/request/ConnectToRoom.cpp
    ${SRCROOT}/handler/request/StartGame.hpp
    ${SRCROOT}/handler/request/StartGame.cpp
    ${SRCROOT}/handler/request/NominateCard.hpp
    ${SRCROOT}/handler/request/NominateCard.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} PUBLIC RockPaperScissorsProtocol::RockPaperScissorsProtocol)