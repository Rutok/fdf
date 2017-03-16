/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:20:26 by nboste            #+#    #+#             */
/*   Updated: 2017/03/16 17:52:19 by nboste           ###   ########.fr       */
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

static void	fdf_fill_map(t_map *map, t_list *list)
{
	int		x;
	int		y;
	char	*str;
	t_list	*tmp;

	if (!(map->points = (t_fdfpoint **)malloc(sizeof(t_fdfpoint *) * map->height)))
		ft_exit("Cant allocate memory.");
	y = 0;
	while (list)
	{
		if (!(map->points[y] = (t_fdfpoint *)malloc(sizeof(t_fdfpoint) * map->width)))
			ft_exit("Cant allocate memory.");
		x = 0;
		while (x < map->width)
		{
			str = ((*(char ***)list->content)[x]);
			if (!(ft_isdigit(str[0]) || (str[0] == '-' && ft_isdigit(str[1]))))
				ft_exit("Bad map :')");
			map->points[y][x].pos.x = x * 10;
			map->points[y][x].pos.y = y * 10;
			map->points[y][x].pos.z = ft_atoi(str) / 23.0;
			map->points[y][x].color = fdf_getcolor(str, map->points[y][x].pos.z);
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

static void	fdf_build_map(int fd, t_map *map)
{
	char	*line;
	char	**split_line;
	t_list	*list;

	map->width = 0;
	map->height = 0;
	list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		split_line = ft_strsplit(line, ' ');
		free(line);
		if (!map->height++)
			map->width = fdf_get_width(split_line);
		if (fdf_get_width(split_line) != map->width)
			ft_exit("Bad map :'(");
		ft_lstadd(&list, ft_lstnew(&split_line, sizeof(char ***)));
	}
	fdf_fill_map(map, list);
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
