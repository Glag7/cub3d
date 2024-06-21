/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:22:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 19:19:36 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "mlx.h"
#include "img.h"
#include "utils.h"

static int	init_minimap(t_mlx *mlx)
{
	if (mlx->mini.d == 0)
		mlx->mini.d = DEF_D;
	if (mlx->mini.offset == 0)
		mlx->mini.offset = DEF_OFFSET;
	mlx->mini.map = malloc(mlx->minimap.d * mlx->minimap.d);
	if (mlx->mini.map == NULL)
	{
		free_mlx(mlx);
		return (1);
	}
	return (0);
}

int	init_mlx(t_mlx *mlx)
{
	int	foo;

	if (mlx->mlx == NULL)
		return (1);
	if (mlx->wid == 0)
		mlx->wid = DEF_WID;
	if (mlx->hei == 0)
		mlx->hei = DEF_HEI;
	mlx->win = mlx_new_window(mlx->mlx, mlx->wid, mlx->hei,
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
	return (init_minimap(mlx));
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
	free(mlx->mini.map);
	ft_bzero(mlx, sizeof(*mlx));
}
