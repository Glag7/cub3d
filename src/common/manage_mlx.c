/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:22:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/19 15:01:14 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "mlx.h"
#include "img.h"
#include "utils.h"

int	init_mlx(t_mlx *mlx)
{
	int	foo;

	if (mlx->mlx == NULL)
		return (1);
	mlx->wid = DEF_WID;
	mlx->hei = DEF_HEI;
	mlx->win = mlx_new_window(mlx->mlx, DEF_WID, DEF_HEI,
			"polyedre a six faces planes carrees de dimension trois");
	if (mlx->win == NULL)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		ft_bzero(mlx, sizeof(*mlx));
		return (1);
	}
	mlx->img = mlx_new_image(mlx->mlx, DEF_WID, DEF_HEI);
	if (mlx->img == NULL)
	{
		free_mlx(mlx);
		return (1);
	}
	mlx->px = (uint32_t *)mlx_get_data_addr(mlx->img, &foo, &foo, &foo);
	return (0);
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	ft_bzero(mlx, sizeof(*mlx));
}
