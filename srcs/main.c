/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:50:04 by nboste            #+#    #+#             */
/*   Updated: 2016/12/10 03:15:33 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include "libft.h"

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2 || !fdf_init(&env, 1000, 700))
		return (1);
	env.path = argv[1];
	fdf_loop(&env);
	return (0);
}
