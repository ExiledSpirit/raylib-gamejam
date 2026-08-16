cmake_minimum_required(VERSION 3.24...3.30)

project(raylib-game-template LANGUAGES C CXX)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
set(RAYLIB_VERSION 6.0)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(RAYLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
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

#target_link_options(${PROJECT_NAME} PRIVATE
#    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:GNU>>:-mwindows>
#)

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
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        PLATFORM_WEB
        ASSETS_PATH=\"assets/\"
    )

    target_link_options(${PROJECT_NAME} PRIVATE
        -sUSE_GLFW=3
        -sASYNCIFY
        -sALLOW_MEMORY_GROWTH=1
        -sINITIAL_MEMORY=134217728
        -sSTACK_SIZE=1048576
        --shell-file=${CMAKE_SOURCE_DIR}/platform/web/shell.html
        --preload-file ${CMAKE_SOURCE_DIR}/src/assets@assets
    )
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        ASSETS_PATH=\"assets/\"
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