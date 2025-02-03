set(TARGET_SUFFIX domain)
set(TARGET_NAME ${PROJECT_NAME}-${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC
    ${SRCROOT}/entity/Uuid.hpp
    ${SRCROOT}/entity/User.hpp
    ${SRCROOT}/entity/Room.hpp
    
    ${SRCROOT}/interface/CommandHandler.hpp
    ${SRCROOT}/interface/UserConnection.hpp
    ${SRCROOT}/interface/UserStorage.hpp
    ${SRCROOT}/interface/RoomStorage.hpp
    ${SRCROOT}/interface/UuidGenerator.hpp

    ${SRCROOT}/command/RegisterCommandHandler.hpp
    ${SRCROOT}/command/RegisterCommandHandler.cpp
    ${SRCROOT}/command/CreateRoomCommandHandler.hpp
    ${SRCROOT}/command/CreateRoomCommandHandler.cpp
    ${SRCROOT}/command/ConnectToRoomCommandHandler.hpp
    ${SRCROOT}/command/ConnectToRoomCommandHandler.cpp

    ${SRCROOT}/CommandExecutor.hpp
    ${SRCROOT}/CommandExecutor.cpp

    ${SRCROOT}/Server.hpp
    ${SRCROOT}/Server.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TARGET_NAME} PUBLIC RockPaperScissorsProtocol::RockPaperScissorsProtocol)