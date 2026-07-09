cmake_minimum_required(VERSION 3.24...3.30)

project(raylib-game-template LANGUAGES C CXX)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
set(RAYLIB_VERSION 6.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_Declare(
    entt
    GIT_REPOSITORY "https://github.com/skypjack/entt.git"
    GIT_TAG v3.15.0
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY "https://github.com/nlohmann/json.git"
    GIT_TAG v3.11.3
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    box2d
    GIT_REPOSITORY "https://github.com/erincatto/box2d.git"
    GIT_TAG v3.1.1
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(
    raylib
    entt
    nlohmann_json
    box2d
)

# Our Project
add_executable(${PROJECT_NAME})

add_subdirectory(engine)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        engine
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Desktop assets
if (NOT "${PLATFORM}" STREQUAL "Web")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    )
endif()

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        SUFFIX ".html"
    )

    target_link_options(${PROJECT_NAME}
        PRIVATE
            -sUSE_GLFW=3
            "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/src/assets@assets"
    )
endif()

# macOS frameworks
if (APPLE)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            "-framework IOKit"
            "-framework Cocoa"
            "-framework OpenGL"
    )
endif()