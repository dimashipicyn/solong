cmake_minimum_required(VERSION 3.0.0)
project(solong VERSION 0.1.0)

add_compile_options(-Wall -Wextra -pedantic)

set(SOURCE_FILES 
    main.c
    keys.c
    graphics.c
    settings.c
    tank.c
    texture.c
    utils.c
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
)

set(HEADER_FILES 
    keys.h
    graphics.h
    settings.h
    tank.h
    texture.h
    utils.h
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
)

add_executable(solong 
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

#MLX
#set(MLX_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/lmlx/libmlx.a)
#add_custom_target(build_mlx ALL 
#                   COMMAND ${CMAKE_MAKE_PROGRAM}
#                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lmlx
#                   COMMENT "Original mlx makefile target")
#
#add_library(mlx STATIC IMPORTED)
#set_property(TARGET mlx APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
#set_target_properties(mlx PROPERTIES
#  IMPORTED_LOCATION_NOCONFIG "${MLX_LIBRARY}")
#
#add_dependencies(mlx build_mlx)

#LIBFT
#set(FT_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/lft/libft.a)
#add_custom_target(build_ft ALL 
#                   COMMAND ${CMAKE_MAKE_PROGRAM}
#                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lft
#                   COMMENT "Original ft makefile target")
#
#add_library(ft STATIC IMPORTED)
#set_property(TARGET ft APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
#set_target_properties(ft PROPERTIES
#  IMPORTED_LOCATION_NOCONFIG "${FT_LIBRARY}")

#add_dependencies(ft build_ft)


find_library(APPKIT Appkit)
if (NOT APPKIT)
    message(FATAL_ERROR "Appkit not found")
endif()

find_library(OPENGL OpenGL)
if (NOT OPENGL)
    message(FATAL_ERROR "OpenGL not found")
endif()

target_link_libraries(solong
    mlx
    ft
    "-framework Appkit"
    "-framework OpenGL"
)

target_include_directories(solong PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/mlx"
    "${PROJECT_SOURCE_DIR}/ft"
)

add_subdirectory(ft)
add_subdirectory(mlx)
