/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/19 17:39:28 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <stdlib.h>
#include "mlx.h"
#include "hooks.h"
#include "img.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"
#include "data.h"

static int draw(void *data_)
{
	t_data *data;

	data = data_;
	ft_bzero(data->mlx.px, DEF_WID * DEF_HEI * 4);
	data->mlx.px[(int)data->map.player.y * DEF_WID + (int)data->map.player.x] = 0x0000FF00;
	data->mlx.px[(int)data->map.player.y * DEF_WID + (int)data->map.player.x + 1] = 0x0000FF00;
	data->mlx.px[(int)data->map.player.y * DEF_WID + (int)data->map.player.x + 2] = 0x0000FF00;
	data->mlx.px[(int)data->map.player.y * DEF_WID + (int)data->map.player.x + 3] = 0x0000FF00;
	data->mlx.px[(int)data->map.player.y * DEF_WID + (int)data->map.player.x + 1 + DEF_WID] = 0x0000FF00;
	data->mlx.px[(int)data->map.player.y * DEF_WID + (int)data->map.player.x + 1 - DEF_WID] = 0x0000FF00;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}

static void	start_game(t_data *data)
{
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_hook(data->mlx.win, DestroyNotify, 0, &win_hook, data);
	mlx_loop_hook(data->mlx.mlx, draw, data);
	mlx_loop(data->mlx.mlx);
	//init hooks
	//
}

int	main(int argc, char **argv)
{
	t_data	data;

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
