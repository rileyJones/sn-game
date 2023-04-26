cmake_minimum_required(VERSION 3.10)

project(game C)
find_package(SDL2 REQUIRED)
include_directories(game ${SDL2_INCLUDE_DIRS})
add_executable(game src/main.c src/update.c src/render.c src/event.c src/gamepad.c src/init.c)
target_compile_options(game PRIVATE -Wall -Werror -pedantic)
target_link_libraries(game ${SDL2_LIBRARIES})

project(gamepad C)
include_directories(gamepad ${SDL2_INCLUDE_DIRS})
add_executable(gamepad src/gamepad/main.c src/gamepad/update.c src/gamepad/render.c src/gamepad/event.c src/gamepad.c src/gamepad/init.c)
target_compile_options(gamepad PRIVATE -Wall -Werror -pedantic)
target_link_libraries(gamepad ${SDL2_LIBRARIES})
