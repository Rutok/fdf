/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 23:50:04 by nboste            #+#    #+#             */
/*   Updated: 2017/05/28 11:16:01 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "fdf.h"

int		main(int argc, char **argv)
{
	t_env	env;

	env.app.argc = argc;
	env.app.argv = argv;
	env.win.name = "fdf";
	env.win.size.x = 2560;
	env.win.size.y = 1440;
	engine_init(&env, &init_app, &process_app, &destroy_app);
	return (engine_run(&env));
}
