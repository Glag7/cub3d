/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 19:40:19 by glaguyon         ###   ########.fr       */
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

static void	start_game(t_data *data)
{
	data->mlx.keys = 0;
	data->map.player.x += 0.5;
	data->map.player.y += 0.5;
	data->map.player.fov = DEF_FOV * M_PI / 180.;
	data->map.player.lwid = DEF_LWID;
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, &unkey_hook, data);
	mlx_hook(data->mlx.win, DestroyNotify, 0, &win_hook, data);
	mlx_loop_hook(data->mlx.mlx, draw, data);
	mlx_loop(data->mlx.mlx);
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
	if (parse_map(data.mlx.mlx, &data.map, argc, argv))
	{
		mlx_destroy_display(data.mlx.mlx);
		free(data.mlx.mlx);
		return (1);
	}
	if (init_mlx(&data.mlx))
	{
		free_map(&data.map);
		ft_perror(ERR_MLX);
		return (1);
	}
	start_game(&data);
	free_map(&data.map);
	free_mlx(&data.mlx);
	return (0);
}
