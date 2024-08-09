/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/09 13:19:57 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "hooks.h"
#include "img.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"
#include "data.h"
#include "render.h"

#include "entity.h"

static void	start_game(t_data *data)
{//XXX mat=ybe remove entmap
	data->map.entmap = malloc(data->map.hei * data->map.wid * sizeof(*data->map.entmap));
	data->map.entities = malloc(2 * sizeof(*data->map.entities));
	data->map.entmap[0] = data->map.entities + 0;
	data->map.entities[0].x = 3.5;
	data->map.entities[0].y = 2.5;
	data->map.map[3 + 2 * data->map.wid] = ENTITY;
	data->map.entities[0].type = DOOR;
	data->map.entities[0].wid = 1.;
	data->map.entities[0].hei = 1.;

	data->play.az = 0.;
	data->play.sina = sin(data->play.a);
	data->play.cosa = cos(data->play.a);
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, &unkey_hook, data);
	mlx_hook(data->mlx.win, DestroyNotify, 0, &win_hook, data);
	mlx_hook(data->mlx.win, FocusOut, FocusChangeMask, &out_hook, data);
	mlx_hook(data->mlx.win, FocusIn, FocusChangeMask, &in_hook, data);
	mlx_loop_hook(data->mlx.mlx, &loop, data);
	mlx_loop(data->mlx.mlx);
}

static int	init_data2(t_data *data)
{
	if (init_mlx(&data->mlx, data->set.wid, data->set.hei))
	{
		free_map(&data->map);
		free_settings(&data->set);
		ft_perror(ERR_MLX);
		return (1);
	}
	if (init_mini(&data->mini, &data->set))
	{
		ft_perror(ERR_MALLOC);
		free_map(&data->map);
		free_mlx(&data->mlx);
		free_settings(&data->set);
		return (1);
	}
	return (0);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	if (init_settings(&data->set))
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		return (1);
	}
	if (parse_map(data->mlx.mlx, data, argc, argv))
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		free_settings(&data->set);
		return (1);
	}
	return (init_data2(data));
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.mlx.mlx = mlx_init();
	if (data.mlx.mlx == NULL)
	{
		ft_perror(ERR_MLX);
		return (1);
	}
	if (init_data(&data, argc, argv))
		return (1);
	start_game(&data);
	free_map(&data.map);
	free_mlx(&data.mlx);
	free_mini(&data.mini);
	free_settings(&data.set);
	return (0);
}
