/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_windows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/10/16 18:11:47 by ttrave           ###   ########.fr       */
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
	draw_string(data, (t_str){TITLE, 0xFF202020, 0.1},
		(t_ulpoint){part(data->set.wid, 0.5), part(data->set.hei, 0.15)},
		(t_ulpoint){part(data->set.wid, 0.75), part(data->set.hei, 0.3)});
	draw_button(data, data->menu.buttons[BUT_START], IDLE);
	draw_button(data, data->menu.buttons[BUT_SETTINGS], IDLE);
	draw_button(data, data->menu.buttons[BUT_EXIT], IDLE);
	data->menu.window = WIN_MAIN;
}

static void	draw_settings_strings(t_data *data, size_t w, size_t h)
{
	draw_string(data, (t_str){"FOV", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.36), part(h, 0.08)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Render Distance", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.36), part(h, 0.21)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Cursor Sensitivity", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.36), part(h, 0.34)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Maximum Speed", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.36), part(h, 0.47)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Acceleration", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.36), part(h, 0.6)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Running Multiplicator", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.36), part(h, 0.73)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Speed Conservation", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.76), part(h, 0.08)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Texture Definition", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.76), part(h, 0.21)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Skybox Definition", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.76), part(h, 0.34)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Aerial Acceleration", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.76), part(h, 0.47)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Aerial Speed Conservation", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.76), part(h, 0.6)}, (t_ulpoint){w, h});
	draw_string(data, (t_str){"Resolution", 0xFF202020, 0.01},
		(t_ulpoint){part(w, 0.7), part(h, 0.7)}, (t_ulpoint){w, h});
}

static void	draw_settings(t_data *data)
{
	draw_button(data, data->menu.buttons[BUT_BACK], IDLE);
	draw_slider(data, data->menu.sliders[SET_FOV]);
	build_textfield(data, data->menu.textfields[SET_FOV]);
	draw_slider(data, data->menu.sliders[SET_VIEW]);
	build_textfield(data, data->menu.textfields[SET_VIEW]);
	draw_slider(data, data->menu.sliders[SET_SENSI]);
	build_textfield(data, data->menu.textfields[SET_SENSI]);
	draw_slider(data, data->menu.sliders[SET_SPEEDMAX]);
	build_textfield(data, data->menu.textfields[SET_SPEEDMAX]);
	draw_slider(data, data->menu.sliders[SET_ACCEL]);
	build_textfield(data, data->menu.textfields[SET_ACCEL]);
	draw_slider(data, data->menu.sliders[SET_ACCELDIFF]);
	build_textfield(data, data->menu.textfields[SET_ACCELDIFF]);
	draw_slider(data, data->menu.sliders[SET_SLOWER]);
	build_textfield(data, data->menu.textfields[SET_SLOWER]);
	draw_slider(data, data->menu.sliders[SET_TEXSIZ]);
	build_textfield(data, data->menu.textfields[SET_TEXSIZ]);
	draw_slider(data, data->menu.sliders[SET_SKYSIZ]);
	build_textfield(data, data->menu.textfields[SET_SKYSIZ]);
	draw_slider(data, data->menu.sliders[SET_ACCELAIR]);
	build_textfield(data, data->menu.textfields[SET_ACCELAIR]);
	draw_slider(data, data->menu.sliders[SET_SLOWERAIR]);
	build_textfield(data, data->menu.textfields[SET_SLOWERAIR]);
	build_textfield(data, data->menu.textfields[SET_WID]);
	build_textfield(data, data->menu.textfields[SET_HEI]);
}

void	draw_settings_menu(t_data *data)
{
	uint32_t	colors[2];

	colors[0] = 0xFF202020;
	colors[1] = 0xFF255873;
	draw_background(data);
	draw_rectangle(data, (t_ulpoint){.x = part(data->set.wid, 0.5),
		.y = part(data->set.hei, 0.5)},
		(t_ulpoint){.x = part(data->set.wid, 0.8),
		.y = part(data->set.hei, 0.9)}, colors);
	draw_settings(data);
	draw_string(data, (t_str){"Width", 0xFF202020, 0.01},
		(t_ulpoint){part(data->set.wid, 0.63), part(data->set.hei, 0.73)},
		(t_ulpoint){data->set.wid, data->set.hei});
	draw_string(data, (t_str){"Height", 0xFF202020, 0.01},
		(t_ulpoint){part(data->set.wid, 0.77), part(data->set.hei, 0.73)},
		(t_ulpoint){data->set.wid, data->set.hei});
	draw_string(data, (t_str){"X", 0xFF202020, 0.01},
		(t_ulpoint){part(data->set.wid, 0.7), part(data->set.hei, 0.78)},
		(t_ulpoint){data->set.wid, data->set.hei});
	draw_string(data, (t_str){"Resolution and definition changes will only take \
effect after restarting", 0xFF202020, 0.008},
		(t_ulpoint){part(data->set.wid, 0.57), part(data->set.hei, 0.9)},
		(t_ulpoint){data->set.wid, data->set.hei});
	draw_settings_strings(data, (size_t)data->set.wid, (size_t)data->set.hei);
	data->menu.window = WIN_SETTINGS;
}

void	draw_exit_menu(t_data *data)
{
	uint32_t	colors[2];

	colors[0] = 0xFF202020;
	colors[1] = 0xFF255873;
	draw_background(data);
	draw_rectangle(data, (t_ulpoint){.x = part(data->set.wid, 0.5),
		.y = part(data->set.hei, 0.5)},
		(t_ulpoint){.x = part(data->set.wid, 0.2),
		.y = part(data->set.hei, 0.25)}, colors);
	draw_string(data, (t_str){.str = "Are you sure ?", .color = 0xFF202020,
		.scale = 0.012},
		(t_ulpoint){.x = data->set.wid / 2, .y = part(data->set.hei, 0.45)},
		(t_ulpoint){.x = part(data->set.wid, 0.18),
		.y = part(data->set.hei, 0.1)});
	draw_button(data, data->menu.buttons[BUT_YES], IDLE);
	draw_button(data, data->menu.buttons[BUT_NO], IDLE);
	data->menu.window = WIN_EXIT;
}
