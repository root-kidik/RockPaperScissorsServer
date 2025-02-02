set(TARGET_SUFFIX infrastructure)
set(TARGET_NAME ${PROJECT_NAME}_${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC 
    ${SRCROOT}/generator/UUIDGenerator.hpp
    ${SRCROOT}/generator/UUIDGenerator.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

if(UNIX AND NOT APPLE)
    set(INTEGRATION_PLUGIN QXcbIntegrationPlugin)
elseif(WIN32)
    set(INTEGRATION_PLUGIN QWindowsIntegrationPlugin)
else()
    message(FATAL_ERROR "Not supported OS")
endif()

find_package(Qt6 COMPONENTS ${INTEGRATION_PLUGIN} Core Widgets Network Protobuf Grpc REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC Qt6::${INTEGRATION_PLUGIN} Qt6::Core Qt6::Widgets Qt6::Network Qt6::Protobuf Qt6::Grpc ${PROJECT_NAME}::domain)
