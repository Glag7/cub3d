/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:17:53 by ttrave            #+#    #+#             */
/*   Updated: 2024/10/16 16:12:18 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "menu.h"
#include "mlx.h"

void	move_slider_head(t_data *data, t_slider slider, size_t x)
{
	uint32_t	colors[2];

	if (x < slider.pos.x - part(slider.dim.x, 0.45))
		x = slider.pos.x - part(slider.dim.x, 0.45);
	else if (x > slider.pos.x - part(slider.dim.x, 0.45)
		+ part(slider.dim.x, 0.9))
		x = slider.pos.x - part(slider.dim.x, 0.45) + part(slider.dim.x, 0.9);
	colors[0] = 0xFF202020;
	colors[1] = 0xFFD0D0D0;
	draw_rectangle(data, slider.pos, slider.dim, colors);
	colors[0] = 0xFF202020;
	colors[1] = 0xFF909090;
	draw_rectangle(data, (t_ulpoint){.x = x, .y = slider.pos.y},
		(t_ulpoint){.x = part(slider.dim.x, 0.1), .y = slider.dim.y}, colors);
}

void	draw_slider(t_data *data, t_slider slider)
{
	uint32_t	colors[2];
	double		v_curr;

	colors[0] = 0xFF202020;
	colors[1] = 0xFFD0D0D0;
	draw_rectangle(data, slider.pos, slider.dim, colors);
	colors[0] = 0xFF202020;
	colors[1] = 0xFF909090;
	if (slider.type == UINT)
		v_curr = *(uint32_t *)slider.dst;
	else
		v_curr = *(double *)slider.dst;
	draw_rectangle(data, (t_ulpoint){.x = slider.pos.x
		- part(slider.dim.x, 0.45) + part(part(slider.dim.x, 0.9),
			(v_curr - slider.v_min) / (slider.v_max - slider.v_min)),
		.y = slider.pos.y}, (t_ulpoint){.x = part(slider.dim.x, 0.1),
		.y = slider.dim.y}, colors);
}

static void	update_value(t_slider *slider, size_t x)
{
	double	v_curr;

	if (x < slider->pos.x - part(slider->dim.x, 0.45))
		x = slider->pos.x - part(slider->dim.x, 0.45);
	else if (x > slider->pos.x - part(slider->dim.x, 0.45)
		+ part(slider->dim.x, 0.9))
		x = slider->pos.x - part(slider->dim.x, 0.45)
			+ part(slider->dim.x, 0.9);
	v_curr = ((double)(x - (slider->pos.x - part(slider->dim.x, 0.45)))
			/ (double)(part(slider->dim.x, 0.9)))
		* (double)(slider->v_max - slider->v_min) + (double)slider->v_min;
	if (slider->type == UINT)
		*(uint32_t *)slider->dst = (uint32_t)v_curr;
	else
		*(double *)slider->dst = v_curr;
}

static int	update_slider(t_slider *slider, size_t x)
{
	double	v_curr;
	double	old_v_curr;

	if (slider->type == UINT)
		old_v_curr = *(uint32_t *)slider->dst;
	else
		old_v_curr = *(double *)slider->dst;
	update_value(slider, (size_t)x);
	if (slider->type == UINT)
		v_curr = *(uint32_t *)slider->dst;
	else
		v_curr = *(double *)slider->dst;
	return (old_v_curr != v_curr);
}

void	update_sliders(t_data *data)
{
	size_t	i;
	int		x;
	int		y;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
	i = 0;
	while (i < NB_SLIDERS)
	{
		if (data->menu.sliders[i].state == PRESS
			&& update_slider(&data->menu.sliders[i], x) == 1)
		{
			move_slider_head(data, data->menu.sliders[i], (size_t)x);
			build_textfield(data, data->menu.textfields[i]);
		}
		i++;
	}
}
