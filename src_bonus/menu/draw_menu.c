/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/27 17:27:35 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "set.h"
#include "menu.h"
#include "img.h"
#include "popup.h"

inline static uint32_t	darken(uint32_t pixel)
{
	uint32_t	darker_pixel;

	darker_pixel = pixel & 0xFF000000;
	darker_pixel |= (uint32_t)((double)((pixel & 0x00FF0000) >> 16) * 0.7) << 16;
	darker_pixel |= (uint32_t)((double)((pixel & 0x0000FF00) >> 8) * 0.7) << 8;
	darker_pixel |= (uint32_t)((double)(pixel & 0x000000FF) * 0.7);
	return (darker_pixel);
}

void	save_background(t_mlx *mlx, t_menu *menu, t_set *set)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < set->hei)
	{
		x = 0;
		while (x < set->wid)
		{
			menu->background[y * set->wid + x] =
				darken(mlx->px[y * set->wid + x]);
			x++;
		}
		y++;
	}
}

void	draw_background(t_mlx *mlx, t_menu *menu, t_set *set)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < set->hei)
	{
		x = 0;
		while (x < set->wid)
		{
			mlx->px[y * set->wid + x] =
				menu->background[y * set->wid + x];
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_mlx *mlx, t_set *set, t_ulpoint pos, t_ulpoint dim, uint32_t *colors)
{
	size_t		x;
	size_t		y;
	t_ulpoint	in_dim;

	if (part(dim.x, 0.1) > 10)
		in_dim.x = dim.x - 10;
	else
		in_dim.x = part(dim.x, 0.1);
	if (part(dim.y, 0.1) > 10)
		in_dim.y = dim.y - 10;
	else
		in_dim.y = part(dim.y, 0.1);
	y = pos.y - dim.y / 2;
	while (pos.y + dim.y / 2)
	{
		x = pos.x - dim.x / 2;
		while (pos.x + dim.x / 2)
		{
			mlx->px[y * set->wid + x] = colors[x > pos.x - in_dim.x / 2
				&& x < pos.x + in_dim.x / 2 && y > pos.y - in_dim.y / 2
				&& y > pos.y + in_dim.y / 2];
			x++;
		}
		y++;
	}
}

void	draw_string(t_mlx *mlx, t_set *set, t_ulpoint pos, t_img string)
{
	size_t	x;
	size_t	y;

	y = pos.y - string.h / 2;
	while (y < pos.y + string.h / 2)
	{
		x = pos.x - string.w / 2;
		while (x < pos.x + string.w / 2)
		{
			if ((string.px[y * string.w + x] & 0xFF000000) != 0)//a verifier
				mlx->px[y * set->wid + x] = string.px[y * string.w + x];
			x++;
		}
		y++;
	}
}

void	draw_button(t_mlx *mlx, t_set *set, t_button button, bool state)
{
	uint32_t	*colors;

	if (state == IDLE)
		colors = button.color_idle;
	else
		colors = button.color_hover;
	draw_rectangle(mlx, set, button.pos, button.dim, colors);
	draw_string(mlx, set, button.pos, button.string);
}
