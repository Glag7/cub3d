/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/06 11:51:27 by glaguyon         ###   ########.fr       */
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
	char	tmp[] = "./assets/ycontre.xpm\0";
	load_img(data->mlx.mlx, tmp, &data->tmp, ((t_dim){64, 64}));//
	char	tmp2[] = "./assets/edbernar.xpm\0";
	load_img(data->mlx.mlx, tmp2, &data->tmp2 , ((t_dim){256, 128}));//

	mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
	mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->set.wid / 2,
		data->set.hei / 2);
	data->oldmouse.x = data->set.wid / 2;
	data->oldmouse.y = data->set.hei / 2;

	data->play.az = 0.;
	data->play.sina = sin(data->play.a);
	data->play.cosa = cos(data->play.a);
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, &key_hook, data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, &unkey_hook, data);
	mlx_hook(data->mlx.win, DestroyNotify, 0, &win_hook, data);
	mlx_loop_hook(data->mlx.mlx, &loop, data);
	mlx_loop(data->mlx.mlx);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	init_settings(&data->set);
	if (parse_map(data->mlx.mlx, data, argc, argv))
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		return (1);
	}
	if (init_mlx(&data->mlx, data->set.wid, data->set.hei))
	{
		free_map(&data->map);
		ft_perror(ERR_MLX);
		return (1);
	}
	if (init_mini(&data->mini, &data->set))
	{
		ft_perror(ERR_MALLOC);
		free_map(&data->map);
		free_mlx(&data->mlx);
		return (1);
	}
	return (0);
}

/*
<<<<<<< HEAD
=======
static int	init_menu(t_data *data)
{
	t_img		img;
	char	path[24] = "assets/main_menu.xpm";

	data->menu.active_popup = MAIN;
	data->menu.button_state = 0;
	load_img(data->mlx.mlx, path, &img, (t_dim){.w = data->set.wid, .h = data->set.hei});
	data->menu.bg_img = img.px;
	if (data->menu.bg_img == NULL)
	{
		ft_perror("img menu tout pete\n");
		free_map(&data->map);
		free_mlx(&data->mlx);
		free_mini(&data->mini);
		return (1);
	}
	return (0);
}

>>>>>>> 06b878c (refactored load_img, added t_dim)*/
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
	return (0);
}
