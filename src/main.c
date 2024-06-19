/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/19 15:03:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "img.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"

static void	start_game(t_mlx *mlx, t_map *map)
{
	//init hooks
	//
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	if (mlx.mlx == NULL)
	{
		ft_perror(ERR_MLX);
		return (1);
	}
	if (parse_map(mlx.mlx, &map, argc, argv))
	{
		mlx_destroy_display(mlx.mlx);
		free(mlx.mlx);
		return (1);
	}
	if (init_mlx(&mlx))
	{
		free_map(&map);
		ft_perror(ERR_MLX);
		return (1);
	}
	start_game(&mlx, &map);
	free_map(&map);
	free_mlx(&mlx);
	return (0);
}
