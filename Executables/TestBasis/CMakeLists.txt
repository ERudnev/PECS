file (GLOB_RECURSE SOURCES_HERE CONFIGURE_DEPENDS "*.cpp")

project(TestBasis)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${SOURCES_HERE}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Basis
    PRIVATE Database
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
)