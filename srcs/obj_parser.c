#include "obj_parser.h"

size_t				ft_strsplit_size(char **parts)
{
	size_t	i;

	i = 0;
	while (parts[i])
		++i;
	return (i);
}

void				ft_strsplit_free(char **parts)
{
	size_t	i;

	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

static t_face		*parse_obj_line(const char *line,
					t_array_3dv *v, t_array_2dp *vt, t_array_3dv *vn)
{
	char	**parts;
	char	**parts1;
	char	**parts2;
	char	**parts3;
	t_face	*f;

	f = NULL;
	if (line[0] == 'v')
	{
		parts = ft_strsplit(line, ' ');
		if (line[1] == ' ' && ft_strsplit_size(parts) >= 4)
			insert_array_3dv(v, (t_3dvertex)
			{ft_atod(parts[1]), ft_atod(parts[2]), ft_atod(parts[3])});
		else if (line[1] == 't' && ft_strsplit_size(parts) >= 3)
			insert_array_2dp(vt, (t_2dpair)
			{ft_atod(parts[1]), ft_atod(parts[2])});
		else if (line[1] == 'n' && ft_strsplit_size(parts) >= 4)
			insert_array_3dv(vn, (t_3dvertex)
			{ft_atod(parts[1]), ft_atod(parts[2]), ft_atod(parts[3])});
		ft_strsplit_free(parts);
	}
	else if (line[0] == 'f')
	{
		parts = ft_strsplit(line, ' ');
		if (ft_strsplit_size(parts) >= 4)
		{
			if ((f = (t_face *)malloc(sizeof(t_face))))
			{
				parts1 = ft_strsplit(parts[1], '/');
				parts2 = ft_strsplit(parts[2], '/');
				parts3 = ft_strsplit(parts[3], '/');
				f->v1 = v->v[ft_atoi(parts1[0]) - 1];
//				f->vt1 = vt->p[ft_atoi(parts1[1]) - 1];
//				f->vn1 = vn->v[ft_atoi(parts1[2]) - 1];
				f->v2 = v->v[ft_atoi(parts2[0]) - 1];
//				f->vt2 = vt->p[ft_atoi(parts2[1]) - 1];
//				f->vn2 = vn->v[ft_atoi(parts2[2]) - 1];
				f->v3 = v->v[ft_atoi(parts3[0]) - 1];
//				f->vt3 = vt->p[ft_atoi(parts3[1]) - 1];
//				f->vn3 = vn->v[ft_atoi(parts3[2]) - 1];
				ft_strsplit_free(parts1);
				ft_strsplit_free(parts2);
				ft_strsplit_free(parts3);
			}
		}
		ft_strsplit_free(parts);
	}
	return (f);
}

t_list			*parse_obj(const char *path)
{
	t_list		*obj;
	t_face		*f;
	t_array_3dv	v;
	t_array_2dp	vt;
	t_array_3dv	vn;
	int			fd;
	char		*line;

	obj = NULL;
	if (init_array_3dv(&v, 100) && init_array_2dp(&vt, 100) && init_array_3dv(&vn, 100))
		if ((fd = open(path, O_RDONLY)) != -1)
			while (get_next_line(fd, &line) > 0)
			{
				if (ft_strlen(line) >= 2)
					if ((f = parse_obj_line(line, &v, &vt, &vn)))
						ft_lstadd(&obj, ft_lstnew(f, sizeof(t_face)));
				free(line);
			}
	free_array_3dv(&v);
	free_array_2dp(&vt);
	free_array_3dv(&vn);
	return (obj);
}
