/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/19 16:55:37 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "hooks.h"
#include "img.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"
#include "data.h"

#include <X11/Xutil.h>
static void	start_game(t_data *data)
{
	mlx_hook(data->mlx.win, KeyPress, 1L, &key_hook, data);
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
