set(VCPKG_ROOT_DIR "$ENV{VCPKG_ROOT}" CACHE PATH "VCPKG_ROOT_DIR")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

cmake_minimum_required(VERSION 3.0.0)
project(battle_city)

add_compile_options(-Wall -Wextra -pedantic)

if (WIN32)
    set(VCPKG_SYSARCH "x64-windows")
elseif(APPLE)
    set(VCPKG_SYSARCH "x64-osx")
else()
    set(VCPKG_SYSARCH "x64-linux")
endif()

set(VCPKG_PREFIX_PATH "${VCPKG_ROOT_DIR}/installed/${VCPKG_SYSARCH}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(VCPKG_PREFIX_CONF_PATH "${VCPKG_PREFIX_PATH}/debug")
else()
    set(VCPKG_PREFIX_CONF_PATH "${VCPKG_PREFIX_PATH}")
endif()

set(SOURCE_FILES 
    main.c
    keys.c
    graphics.c
    settings.c
    tank.c
    texture.c
    entity.c
    framerate.c
    game_map.c
    bullet.c
    physics.c
    vector.c
    animation.c
    scene.c
    main_scene.c
	command.c
	menu_scene.c
	editor_scene.c
	fonts.c
)

set(HEADER_FILES 
    keys.h
    graphics.h
    settings.h
    tank.h
    texture.h
    entity.h
    framerate.h
    game_map.h
    bullet.h
    physics.h
    vector.h
    animation.h
    game.h
    scene.h
    main_scene.h
	command.h
	menu_scene.h
	editor_scene.h
	fonts.h
)

add_executable(${PROJECT_NAME} 
    ${SOURCE_FILES}
    ${HEADER_FILES}
)


find_library(APPKIT Appkit)
if (NOT APPKIT)
    message(FATAL_ERROR "Appkit not found")
endif()

find_library(OPENGL OpenGL)
if (NOT OPENGL)
    message(FATAL_ERROR "OpenGL not found")
endif()

add_subdirectory(utils)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    utils
    "-framework Appkit"
    "-framework OpenGL"
	SDL2::SDL2
	SDL2::SDL2main
	SDL2::SDL2-static
	SDL2::SDL2_image
	SDL2_ttf::SDL2_ttf-static
	SDL2_mixer::SDL2_mixer-static
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/utils"
	${SDL2_INCLUDE_DIRS}
	${SDL2IMAGE_INCLUDE_DIRS}
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${VCPKG_PREFIX_PATH}/include
)
