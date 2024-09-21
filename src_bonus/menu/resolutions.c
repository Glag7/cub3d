/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolutions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:05:32 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/21 19:18:53 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "mlx.h"
#include "data.h"
#include "menu.h"
#include "popup.h"

void	save_resolution(t_data *data, size_t x, size_t y)
{
	size_t		i;
	t_ulpoint	pos;
	t_ulpoint	dim;

	dim = (t_ulpoint){.x = data->menu.res.dim.x / NB_RESOLUTIONS,
		.y = data->menu.res.dim.y};
	pos = (t_ulpoint){.x = data->menu.res.pos.x - data->menu.res.dim.x / 2
		+ dim.x / 2, .y = data->menu.res.pos.y};
	i = 0;
	while (i < NB_RESOLUTIONS)
	{
		if (check_hitbox(pos, dim, x, y) == 1)
		{
			data->menu.res.state[i] = PRESS;
			data->set.saved_w = (unsigned int)data->menu.res.values[i].x;
			data->set.saved_h = (unsigned int)data->menu.res.values[i].y;
		}
		else
			data->menu.res.state[i] = IDLE;
		pos.x += dim.x;
		i++;
	}
}

static void	update_state(t_data *data, uint8_t *state, uint8_t hovering)
{
	if (hovering == 1 && *state == IDLE)
	{
		*state = HOVER;
		build_resolutions(data, data->menu.res);
	}
	else if (hovering == 0 && *state == HOVER)
	{
		*state = IDLE;
		build_resolutions(data, data->menu.res);
	}
}

void	update_resolutions(t_data *data)
{
	size_t		i;
	t_ulpoint	pos;
	t_ulpoint	dim;
	int			x;
	int			y;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
	dim = (t_ulpoint){.x = data->menu.res.dim.x / NB_RESOLUTIONS,
		.y = data->menu.res.dim.y};
	pos = (t_ulpoint){.x = data->menu.res.pos.x - data->menu.res.dim.x / 2
		+ dim.x / 2, .y = data->menu.res.pos.y};
	i = 0;
	while (i < NB_RESOLUTIONS)
	{
		update_state(data, &data->menu.res.state[i],
			check_hitbox(pos, dim, x, y));
		pos.x += dim.x;
		i++;
	}
}

void	build_resolutions(t_data *data, t_res res)
{
	size_t		i;
	t_ulpoint	pos;
	t_ulpoint	dim;
	uint32_t	*colors;

	dim = (t_ulpoint){.x = res.dim.x / NB_RESOLUTIONS, .y = res.dim.y};
	pos = (t_ulpoint){.x = res.pos.x - res.dim.x / 2 + dim.x / 2,
		.y = res.pos.y};
	i = 0;
	while (i < NB_RESOLUTIONS)
	{
		if (res.state[i] == IDLE)
			colors = res.color_idle;
		else if (res.state[i] == HOVER)
			colors = res.color_hover;
		else
			colors = res.color_press;
		draw_rectangle(data, pos, dim, colors);
		draw_image(data, pos, res.string[i]);
		pos.x += dim.x;
		i++;
	}
}
