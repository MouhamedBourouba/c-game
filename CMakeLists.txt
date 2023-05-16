cmake_minimum_required (VERSION 3.22.1)

project (game_engine)

include_directories(include)
include_directories(include/ECS)
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMAND ON)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)
