/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/14 15:58:42 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//pas d'espaces ou de bords autour des 0 ou du player

#include <stdlib.h>
#include "mlx.h"
#include "map.h"
#include "utils.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_map	map;
	void	*mlx;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		ft_perror("MLX failure\n");
		return (1);
	}
	if (parse_map(mlx, &map, argc, argv))
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
