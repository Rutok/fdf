#include "obj_parser.h"

t_bool	init_array_2dp(t_array_2dp *array, const size_t initial_size)
{
	if (!(array->p = (t_2dpair *)malloc(sizeof(t_2dpair) * initial_size)))
		return (0);
	array->used = 0;
	array->size = initial_size;
	return (1);
}

t_bool	insert_array_2dp(t_array_2dp *array, const t_2dpair pair)
{
	if (array->used == array->size)
	{
		array->size *= 2;
		if (!(array->p =
			(t_2dpair *)realloc(array->p, sizeof(t_2dpair) * array->size)))
			return (0);
	}
	array->p[array->used++] = (t_2dpair){pair.x, pair.y};
	return (1);
}

void	free_array_2dp(t_array_2dp *array)
{
	free(array->p);
	array->p = NULL;
	array->used = 0;
	array->size = 0;
}
