/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:50:04 by nboste            #+#    #+#             */
/*   Updated: 2016/12/09 00:14:33 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libft.h"

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc < 3 || !fdf_init(&env, ft_atoi(argv[1]), ft_atoi(argv[2])))
		return (1);
	fdf_loop(&env);
	return (0);
}
