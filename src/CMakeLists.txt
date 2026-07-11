file(GLOB_RECURSE GAME_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE GAME_HEADER_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${GAME_SOURCE_FILES}
        ${GAME_HEADER_FILES}
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
if (EMSCRIPTEN OR "${PLATFORM}" STREQUAL "Web")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            PLATFORM_WEB
            ASSETS_PATH=\"assets/\"
    )
else()
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            ASSETS_PATH=\"assets/\"
    )
endif()