/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/16 16:23:53 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"
#include "err.h"

int	main(int argc, char **argv)
{
	t_map	map;
	void	*mlx;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		ft_perror(ERR_MLX);
		return (1);
	}
	if (parse_map(mlx, &map, argc, argv))
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	//TODO DRAW
	free_map(&map);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
