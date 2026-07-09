file(GLOB_RECURSE ENGINE_SOURCE_FILES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE ENGINE_HEADER_FILES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(engine STATIC
  ${ENGINE_SOURCE_FILES}
  ${ENGINE_HEADER_FILES}
)

target_include_directories(engine
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(
  engine
  PUBLIC
    raylib
    nlohmann_json::nlohmann_json
    EnTT::EnTT
    box2d
)
