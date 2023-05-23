cmake_minimum_required(VERSION 3.10)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

project(game C)
include_directories(game ${SDL2_INCLUDE_DIRS})
include_directories(game ${SDL2TTF_INCLUDE_DIRS})
add_executable(game src/main.c src/update.c src/render.c src/event.c src/gamepad.c src/init.c
    src/alert.c src/quit.c)
target_compile_options(game PRIVATE -Wall -Werror -pedantic)
target_link_libraries(game ${SDL2_LIBRARIES})
target_link_libraries(game ${SDL2TTF_LIBRARIES})

project(gamepad C)
include_directories(gamepad ${SDL2_INCLUDE_DIRS})
add_executable(gamepad src/gamepad/main.c src/gamepad/update.c src/gamepad/render.c
    src/gamepad/event.c src/gamepad/gamepad.c src/gamepad/init.c)
target_compile_options(gamepad PRIVATE -Wall -Werror -pedantic)
target_link_libraries(gamepad ${SDL2_LIBRARIES})

project(render C)
include_directories(render ${SDL2_INCLUDE_DIRS})
add_executable(render src/render/event.c src/render/gamepad.c 
	src/render/init.c src/render/main.c src/render/render.c src/render/update.c)
target_compile_options(render PRIVATE -Wall -Werror -pedantic)
target_link_libraries(render ${SDL2_LIBRARIES})
