set (CMAKE_CXX_FLAGS "-DSTRINGPUTX11 -O2")

add_library(mlx STATIC 
    mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c mlx_get_screen_size.m
    mlx_png.c mlx_mouse.m
)
