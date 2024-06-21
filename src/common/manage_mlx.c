/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:22:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 19:38:06 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include "mlx.h"
#include "img.h"
#include "utils.h"

static void	fill_circle(uint8_t *mask, unsigned int d)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	r;
	int			x;
	int			y;

	i = 0;
	r = d / 2;
	while (i < d)
	{
		j = 0;
		while (j < d)
		{
			x = i - r;
			y = j - r;
			if ((unsigned int)sqrt((float)(x * x + y * y)) > r)
				mask[i + j * d] = 0;
			else
				mask[i + j * d] = 1;
			j++;
		}
		i++;
	}
}

static int	init_minimask(t_mlx *mlx)
{
	if (mlx->mini.d == 0)
		mlx->mini.d = DEF_D;
	if (mlx->mini.offset == 0)
		mlx->mini.offset = DEF_OFFSET;
	mlx->mini.mask = malloc(mlx->mini.d * mlx->mini.d);
	if (mlx->mini.mask == NULL)
	{
		free_mlx(mlx);
		return (1);
	}
	fill_circle(mlx->mini.mask, mlx->mini.d);
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
	return (init_minimask(mlx));
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
	free(mlx->mini.mask);
	ft_bzero(mlx, sizeof(*mlx));
}
