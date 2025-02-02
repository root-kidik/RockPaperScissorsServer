set(TARGET_SUFFIX domain)
set(TARGET_NAME ${PROJECT_NAME}_${TARGET_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(SRC
    ${SRCROOT}/entity/User.hpp
    ${SRCROOT}/entity/User.cpp
)

add_library(${TARGET_NAME} ${SRC})
add_library(${PROJECT_NAME}::${TARGET_SUFFIX} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
