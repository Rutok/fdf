/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:20:26 by nboste            #+#    #+#             */
/*   Updated: 2017/05/28 13:32:53 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_reader.h"

static int	fdf_get_width(char **split)
{
	int i;

	i = 0;
	while (*split++)
		i++;
	return (i);
}

static t_color	fdf_getcolorz(int z)
{
	t_color	c;

	if (z <= 0)
	{
		c.r = 0;
		c.g = 0;
		if (z >= -255)
			c.b = z + 255;
		else
			c.b = 0;
	}
	else if (z < 50)
	{
		c.r = 0;
		c.g = z + 45;
		c.b = 0;
	}
	else
	{
		c.r = (z % 200) + 55;
		c.g = (z % 128);
		c.b = (z % 64);
	}
	return (c);
}

static t_color	fdf_getcolor(char *str, int z)
{
	char	*c;
	int		val;
	int		i;
	t_color	color;

	val = 0;
	i = 0;
	if ((c = ft_strchr(str, 'x')))
	{
		c++;
		while (c[i] != '\0' && i < 6)
		{
			c[i] = ft_toupper(c[i]);
			val = val << 4;
			if (c[i] >= '0' && c[i] <= '9')
				val += c[i] - '0';
			else if (c[i] >= 'A' && c[i] <= 'F')
				val += 10 + c[i] - 'A';
			else
				ft_exit("Bad map colors !!!");
			i++;
		}
		color.r = val >> 16;
		color.g = (val & 0xFF00) >> 8;
		color.b = (val & 0xFF);
	}
	else
		color = fdf_getcolorz(z);
	return (color);
}

static void	fdf_fill_obj(t_3dobject *obj, t_list *list, int width)
{
	int		x;
	int		y;
	char	*str;
	t_list	*tmp;
	t_face	f;

	y = 0;
	obj->faces = NULL;
	while (list)
	{
		x = 0;
		while (x < width)
		{
			str = ((*(char ***)list->content)[x]);
			if (!(ft_isdigit(str[0]) || (str[0] == '-' && ft_isdigit(str[1]))))
				ft_exit("Bad map :')");
			if (x < width - 1 && list->next != NULL)
			{
				f.v1.x = x * 10;
				f.v1.y = y * 10;
				f.v1.z = ft_atoi(str);
				f.c1 = fdf_getcolor(str, f.v1.z);
				f.v2.x = (x + 1) * 10;
				f.v2.y = y * 10;
				f.v2.z = ft_atoi((*(char ***)list->content)[x + 1]);
				f.c2 = fdf_getcolor((*(char ***)list->content)[x + 1], f.v2.z);
				f.v3.x = x * 10;
				f.v3.y = (y + 1) * 10;
				f.v3.z = ft_atoi((*(char ***)list->next->content)[x]);
				f.c3 = fdf_getcolor((*(char ***)list->next->content)[x], f.v3.z);
				ft_lstadd(&obj->faces, ft_lstnew(&f, sizeof(t_face)));
				f.v1.x = (x + 1) * 10;
				f.v1.y = y * 10;
				f.v1.z = ft_atoi((*(char ***)list->content)[x + 1]);
				f.c1 = fdf_getcolor((*(char ***)list->content)[x + 1], f.v1.z);
				f.v2.x = (x + 1) * 10;
				f.v2.y = (y + 1) * 10;
				f.v2.z = ft_atoi((*(char ***)list->next->content)[x + 1]);
				f.c2 = fdf_getcolor((*(char ***)list->next->content)[x + 1], f.v2.z);
				f.v3.x = x * 10;
				f.v3.y = (y + 1) * 10;
				f.v3.z = ft_atoi((*(char ***)list->next->content)[x]);
				f.c3 = fdf_getcolor((*(char ***)list->next->content)[x], f.v3.z);
				ft_lstadd(&obj->faces, ft_lstnew(&f, sizeof(t_face)));
			}
			free(str);
			x++;
		}
		y++;
		tmp = list;
		list = list->next;
		free(*(char ***)tmp->content);
		free((char ***)tmp->content);
		free(tmp);
	}
}

static void	fdf_build_obj(int fd, t_3dobject *obj)
{
	char	*line;
	char	**split_line;
	t_list	*list;
	int		width;

	list = NULL;
	width = -1;
	while (get_next_line(fd, &line) > 0)
	{
		split_line = ft_strsplit(line, ' ');
		free(line);
		if (width == -1)
			width = fdf_get_width(split_line);
		if (fdf_get_width(split_line) != width)
			ft_exit("Bad map :'(");
		ft_lstadd(&list, ft_lstnew(&split_line, sizeof(char ***)));
	}
	if (width == -1 || list->next == 0)
		ft_exit("Bad map :'(");
	fdf_fill_obj(obj, list, width);
}

t_3dobject	*fdf_get_obj(char *path)
{
	int			fd;
	t_3dobject	*obj;

	if ((fd = open(path, O_RDONLY)) < 0)
		ft_exit("The file can't be opened.");
	if (!(obj = (t_3dobject *)malloc(sizeof(t_3dobject))))
		ft_exit("Could not allocate memory");
	fdf_build_obj(fd, obj);
	close(fd);
	obj->pos.x = 0;
	obj->pos.y = 0;
	obj->pos.z = 0;
	obj->uvn.n.x = 1;
	obj->uvn.n.y = 0;
	obj->uvn.n.z = 0;
	obj->uvn.v.x = 0;
	obj->uvn.v.y = 0;
	obj->uvn.v.z = 1;
	obj->uvn.u.x = 0;
	obj->uvn.u.y = 1;
	obj->uvn.u.z = 0;
	obj->scale.x = 1;
	obj->scale.y = 1;
	obj->scale.z = 1;
	return (obj);

}
