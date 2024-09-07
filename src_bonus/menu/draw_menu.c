/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/07 16:31:00 by ttrave           ###   ########.fr       */
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
	darker_pixel |= (uint32_t)part((pixel & 0x00FF0000) >> 16, 0.5) << 16;
	darker_pixel |= (uint32_t)part((pixel & 0x0000FF00) >> 8, 0.5) << 8;
	darker_pixel |= (uint32_t)part((pixel & 0x000000FF), 0.5);
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
	size_t	x;
	size_t	y;
	size_t	margin;

	if (fmin(dim.x, dim.y) < 100)
		margin = part(fmin(dim.x, dim.y), 0.1);
	else
		margin = 10;
	y = pos.y - dim.y / 2;
	while (y < pos.y + dim.y / 2)
	{
		x = pos.x - dim.x / 2;
		while (x < pos.x + dim.x / 2)
		{
			if (x < pos.x - dim.x / 2 + margin || x > pos.x + dim.x / 2 - margin
				|| y < pos.y - dim.y / 2 + margin || y > pos.y + dim.y / 2 - margin)
				mlx->px[y * set->wid + x] = colors[0];
			else
				mlx->px[y * set->wid + x] = colors[1];
			x++;
		}
		y++;
	}
}

void	draw_string(t_mlx *mlx, t_set *set, t_ulpoint pos, t_img string)
{
	size_t	x_img;
	size_t	y_img;
	size_t	x_px;
	size_t	y_px;

	y_img = 0;
	y_px = pos.y - string.h / 2;
	while (y_img < string.h)
	{
		x_img = 0;
		x_px = pos.x - string.w / 2;
		while (x_img < string.w)
		{
			if ((string.px[y_img * string.w + x_img] & 0xFF000000) != 0)
				mlx->px[y_px * set->wid + x_px] = string.px[y_img * string.w + x_img];
			x_img++;
			x_px++;
		}
		y_img++;
		y_px++;
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
