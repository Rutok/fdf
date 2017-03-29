#include "obj_parser.h"

t_bool	init_array_3dv(t_array_3dv *array, const size_t initial_size)
{
	if (!(array->v = (t_3dvertex *)malloc(sizeof(t_3dvertex) * initial_size)))
		return (0);
	array->used = 0;
	array->size = initial_size;
	return (1);
}

t_bool	insert_array_3dv(t_array_3dv *array, const t_3dvertex vertex)
{
	if (array->used == array->size)
	{
		array->size *= 2;
		if (!(array->v =
			(t_3dvertex *)realloc(array->v, sizeof(t_3dvertex) * array->size)))
			return (0);
	}
	array->v[array->used++] = (t_3dvertex){vertex.x, vertex.y, vertex.z};
	return (1);
}

void	free_array_3dv(t_array_3dv *array)
{
	free(array->v);
	array->v = NULL;
	array->used = 0;
	array->size = 0;
}
