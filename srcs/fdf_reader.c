/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:20:26 by nboste            #+#    #+#             */
/*   Updated: 2017/02/17 05:38:20 by nboste           ###   ########.fr       */
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

static t_color	fdf_getcolor(char *str)
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
			else
				val += 10 + c[i] - 'A';
			i++;
		}
	}
	else
		val = 0x00FFFFFF;
	color.r = val >> 16;
	color.g = (val & 0xFF00) >> 8;
	color.b = (val & 0xFF);
	return (color);
}

static void	fdf_fill_map(t_map *map, t_list *list)
{
	int		x;
	int		y;

	if (!(map->points = (t_point **)malloc(sizeof(t_point *) * map->height)))
		ft_exit("Cant allocate memory.");
	y = 0;
	while (list)
	{
		if (!(map->points[y] = (t_point *)malloc(sizeof(t_point) * map->width)))
			ft_exit("Cant allocate memory.");
		x = 0;
		while (x < map->width)
		{
			map->points[y][x].pos.x = x * 10;
			map->points[y][x].pos.y = y * 10;
			map->points[y][x].pos.z = ft_atoi(((char **)list->content)[x]);
			map->points[y][x].color = fdf_getcolor(((char **)list->content)[x]);
			x++;
		}
		y++;
		list = list->next;
	}
}

static void	fdf_build_map(int fd, t_map *map)
{
	char	*line;
	char	**split_line;
	t_list	*list;

	map->width = 0;
	map->height = 0;
	list = 0;
	while (get_next_line(fd, &line) > 0)
	{
		split_line = ft_strsplit(line, ' ');
		free(line);
		if (!map->height)
		{
			map->width = fdf_get_width(split_line);
			list = ft_lstnew(&split_line, sizeof(char **));
			list->content = (void *)split_line;
		}
		else
		{
			// TODO: check errors in file
			ft_lstadd(&list, ft_lstnew(&split_line, sizeof(char **)));
			list->content = (void *)split_line;
		}
		map->height++;
	}
	fdf_fill_map(map, list);
	// TODO: free list
}
t_map	*fdf_get_map(char *path)
{
	int		fd;
	t_map	*map;

	if ((fd = open(path, O_RDONLY)) < 0)
		ft_exit("The file can't be opened.");
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		ft_exit("Could not allocate memory");
	fdf_build_map(fd, map);
	close(fd);
	return (map);
}
