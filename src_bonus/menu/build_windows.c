/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_windows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/22 19:52:09 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img.h"
#include "menu.h"
#include "set.h"
#include "popup.h"
#include "mlx.h"
#include "status.h"

void	draw_main_menu(t_data *data)
{
	draw_background(data);
	draw_image(data, (t_ulpoint){.x = part(data->set.wid, 0.5),
		.y = part(data->set.hei, 0.15)}, data->menu.title);
	draw_button(data, data->menu.buttons[BUT_START], IDLE);
	draw_button(data, data->menu.buttons[BUT_SETTINGS], IDLE);
	draw_button(data, data->menu.buttons[BUT_EXIT], IDLE);
	data->menu.window = WIN_MAIN;
}

static void	draw_settings_strings(t_data *data, size_t w, size_t h)
{
	draw_string(data, (t_str){"FOV", 0xFF000000, 0.015},
		(t_ulpoint){part(w, 0.55), part(h, 0.11)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Render Distance", 0xFF000000, 0.015},
		(t_ulpoint){part(w, 0.55), part(h, 0.27)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Cursor Sensitivity", 0xFF000000, 0.015},
		(t_ulpoint){part(w, 0.55), part(h, 0.45)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Width", 0xFF000000, 0.015},
		(t_ulpoint){part(w, 0.50), part(h, 0.81)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"X", 0xFF000000, 0.015},
		(t_ulpoint){part(w, 0.57), part(h, 0.81)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Height", 0xFF000000, 0.015},
		(t_ulpoint){part(w, 0.64), part(h, 0.81)}, (t_ulpoint){w, h});
}

void	draw_settings_menu(t_data *data)
{
	uint32_t	colors[2];

	colors[0] = 0x00101010;
	colors[1] = 0x00505050;
	draw_background(data);
	draw_rectangle(data, (t_ulpoint){.x = part(data->set.wid, 0.5),
		.y = part(data->set.hei, 0.5)},
		(t_ulpoint){.x = part(data->set.wid, 0.5),
		.y = part(data->set.hei, 0.9)}, colors);
	draw_button(data, data->menu.buttons[BUT_BACK], IDLE);
	draw_slider(data, data->menu.sliders[SET_FOV]);
	build_textfield(data, data->menu.textfields[SET_FOV]);
	draw_slider(data, data->menu.sliders[SET_VIEW]);
	build_textfield(data, data->menu.textfields[SET_VIEW]);
	draw_slider(data, data->menu.sliders[SET_SENSI]);
	build_textfield(data, data->menu.textfields[SET_SENSI]);
	build_textfield(data, data->menu.textfields[SET_WID]);
	build_textfield(data, data->menu.textfields[SET_HEI]);
	draw_settings_strings(data, (size_t)data->set.wid, (size_t)data->set.hei);
	data->menu.window = WIN_SETTINGS;
}

void	draw_exit_menu(t_data *data)
{
	uint32_t	colors[2];

	colors[0] = 0x00101010;
	colors[1] = 0x00505050;
	draw_background(data);
	draw_rectangle(data, (t_ulpoint){.x = part(data->set.wid, 0.5),
		.y = part(data->set.hei, 0.5)},
		(t_ulpoint){.x = part(data->set.wid, 0.2),
		.y = part(data->set.hei, 0.25)}, colors);
	draw_string(data, (t_str){.str = "Are you sure ?", .color = 0xFF000000,
		.scale = 0.012},
		(t_ulpoint){.x = data->set.wid / 2, .y = part(data->set.hei, 0.45)},
		(t_ulpoint){.x = part(data->set.wid, 0.18),
		.y = part(data->set.hei, 0.1)});
	draw_button(data, data->menu.buttons[BUT_YES], IDLE);
	draw_button(data, data->menu.buttons[BUT_NO], IDLE);
	data->menu.window = WIN_EXIT;
}
