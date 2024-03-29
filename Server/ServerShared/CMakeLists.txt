CMAKE_MINIMUM_REQUIRED (VERSION 3.4)

SET(PROJECT_NAME ${SS_PROJECT_NAME})
PROJECT(${PROJECT_NAME})

SET(PROJECT_ROOT_DIR ${SS_ROOT_DIR})
SET(HEADER_FILES "")
SET(SRC_FILES "")

FILE(GLOB HEADER_FILES
${PROJECT_ROOT_DIR}/${HEADER_DIR}/*.h
${PROJECT_ROOT_DIR}/${PCH_HEADER}
)

FILE(GLOB SRC_FILES
${PROJECT_ROOT_DIR}/${SRC_DIR}/*.cpp
${PROJECT_ROOT_DIR}/${PCH_SRC}
)

ADD_LIBRARY(${PROJECT_NAME}
${HEADER_FILES}
${SRC_FILES}
)

MSVC_SET_PCH(${PROJECT_NAME}
${PCH_HEADER}
${PCH_SRC}
)

INCLUDE_DIRECTORIES(${PCH_DIR})
INCLUDE_DIRECTORIES(${HEADER_DIR})

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${DB_ROOT_DIR}/${HEADER_DIR})
INCLUDE_DIRECTORIES(${PACKET_ROOT_DIR}/${HEADER_DIR})

INCLUDE_DIRECTORIES(${FGNET_SHARED_ROOT_DIR}/${HEADER_DIR})
INCLUDE_DIRECTORIES(${FGNET_SERVER_ROOT_DIR}/${HEADER_DIR})

INCLUDE_DIRECTORIES(${PROTOBUF_ROOT_DIR}/${HEADER_DIR})
INCLUDE_DIRECTORIES(${PROTOBUF_AUTOGEN_DIR})
INCLUDE_DIRECTORIES(${PROTOBUF_PROTO_DIR})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
${FGNET_SERVER_PROJECT_NAME}
${PACKET_PROJECT_NAME}
${DB_PROJECT_NAME}
)