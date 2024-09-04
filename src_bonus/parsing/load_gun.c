/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:55:16 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/04 17:09:05 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tex.h"
#include "map.h"
#include "parsing.h"

int	load_gun(t_data *data)
{
	if (load_img(data->mlx.mlx, TEX_GUN1, data->map.gun.frames + 0,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	if (load_img(data->mlx.mlx, TEX_GUN2, data->map.gun.frames + 1,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	if (load_img(data->mlx.mlx, TEX_GUN3, data->map.gun.frames + 2,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	if (load_img(data->mlx.mlx, TEX_GUN4, data->map.gun.frames + 3,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	if (load_img(data->mlx.mlx, TEX_GUN5, data->map.gun.frames + 4,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	if (load_img(data->mlx.mlx, TEX_GUN6, data->map.gun.frames + 5,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	if (load_img(data->mlx.mlx, TEX_GUN7, data->map.gun.frames + 6,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	if (load_img(data->mlx.mlx, TEX_GUN8, data->map.gun.frames + 7,
				(t_dim){data->set.texsiz, data->set.texsiz}))
		return (1);
	return (0);
}
