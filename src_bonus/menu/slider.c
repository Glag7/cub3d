/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:17:53 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/18 19:24:58 by ttrave           ###   ########.fr       */
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
	else if (x > slider.pos.x - part(slider.dim.x, 0.45) + part(slider.dim.x, 0.9))
		x = slider.pos.x - part(slider.dim.x, 0.45) + part(slider.dim.x, 0.9);
	colors[0] = 0xFF000000;
	colors[1] = 0xFFD0D0D0;
	draw_rectangle(data, slider.pos, slider.dim, colors);
	colors[0] = 0xFF000000;
	colors[1] = 0xFF909090;
	draw_rectangle(data, (t_ulpoint){.x = x, .y = slider.pos.y},
		(t_ulpoint){.x = part(slider.dim.x, 0.1), .y = slider.dim.y}, colors);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	draw_slider(t_data *data, t_slider slider)
{
	uint32_t	colors[2];

	colors[0] = 0xFF000000;
	colors[1] = 0xFFD0D0D0;
	draw_rectangle(data, slider.pos, slider.dim, colors);
	colors[0] = 0xFF000000;
	colors[1] = 0xFF909090;
	draw_rectangle(data, (t_ulpoint){.x = slider.pos.x - part(slider.dim.x, 0.45) + part(part(slider.dim.x, 0.9), (slider.v_curr - slider.v_min) / (slider.v_max - slider.v_min)), .y = slider.pos.y},
		(t_ulpoint){.x = part(slider.dim.x, 0.1), .y = slider.dim.y}, colors);
}

static void	update_value(t_slider *slider, size_t x)
{
	if (x < slider->pos.x - part(slider->dim.x, 0.45))
		x = slider->pos.x - part(slider->dim.x, 0.45);
	else if (x > slider->pos.x - part(slider->dim.x, 0.45) + part(slider->dim.x, 0.9))
		x = slider->pos.x - part(slider->dim.x, 0.45) + part(slider->dim.x, 0.9);
	slider->v_curr = ((double)(x - (slider->pos.x - part(slider->dim.x, 0.45)))
		/ (double)(part(slider->dim.x, 0.9)))
		* (double)(slider->v_max - slider->v_min) + (double)slider->v_min;
}

void	update_sliders(t_data *data)
{
	double	old_v_curr;
	size_t	i;
	int		x;
	int		y;

	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
	i = 0;
	while (i < NB_SETTINGS)
	{
		if (data->menu.sliders[i].state == PRESS)
		{
			old_v_curr = data->menu.sliders[i].v_curr;
			update_value(&data->menu.sliders[i], (size_t)x);
			if (old_v_curr != data->menu.sliders[i].v_curr)
			{
				move_slider_head(data, data->menu.sliders[i], (size_t)x);
				build_textfield(data, data->menu.textfields[i]);
			}
		}
		i++;
	}
}
