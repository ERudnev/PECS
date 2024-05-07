file (GLOB_RECURSE SOURCES_HERE CONFIGURE_DEPENDS "*.cpp")

project("Database"
    DESCRIPTION "Persistent ECS database engine"
    VERSION 0.1
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${SOURCES_HERE}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/interface
    INTERFACE
        ${PROJECT_SOURCE_DIR}/interface
)
