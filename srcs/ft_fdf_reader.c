/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:20:26 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 00:45:00 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_reader.h"

static int	fdf_get_width(char **split)
{
	int i;

	i = 0;
	while (*split++)
		i++;
	return (i);
}

static void	fdf_fill_map(t_map *map, t_list *list)
{
	int		x;
	int		y;

	if (!(map->points = (t_point **)malloc(sizeof(t_point *) * map->height)))
		fdf_exit("Cant allocate memory.");
	y = map->height - 1;
	while (list)
	{
		if (!(map->points[y] = (t_point *)malloc(sizeof(t_point) * map->width)))
			fdf_exit("Cant allocate memory.");
		x = 0;
		while (x < map->width)
		{
			map->points[y][x].x = x;
			map->points[y][x].y = y;
			map->points[y][x].z = ft_atoi(((char **)list->content)[x]);
			x++;
		}
		y--;
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
		fdf_exit("The file can't be opened.");
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		fdf_exit("Could not allocate memory");
	fdf_build_map(fd, map);
	close(fd);
	return (map);
}
