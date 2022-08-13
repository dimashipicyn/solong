project(utils)

add_library(${PROJECT_NAME} STATIC
	utils.h
	time.c
	strrev.c get_next_line.c itoa_base.c
	toupper_str.c isdigit_str.c
	swap.c bubblesort.c
	create_elem.c list_at.c list_clear.c list_find.c
	list_foreach.c list_foreach_if.c list_last.c list_merge.c
	list_push_back.c list_push_front.c list_push_params.c
	list_remove_if.c list_reverse.c list_size.c list_sort.c
)
