/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_buttons.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:00:12 by ttrave            #+#    #+#             */
/*   Updated: 2024/10/15 20:02:43 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "menu.h"

void	init_buttons_settings(t_menu *menu, size_t w, size_t h)
{
	menu->buttons[BUT_BACK] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.32),
		.y = part(h, 0.88)}, .dim = (t_ulpoint){.x = part(w, 0.1),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_SETTINGS, .string = (t_str)
	{.str = "Back", .color = 0xFF000000, .scale = 0.015}};
}

void	init_buttons_exit(t_menu *menu, size_t w, size_t h)
{
	menu->buttons[BUT_YES] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.45),
		.y = part(h, 0.55)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFFff1b1e, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFFff3d40, .window = WIN_EXIT, .string = (t_str)
	{.str = "Yes", .color = 0xFF000000, .scale = 0.015}};
	menu->buttons[BUT_NO] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.55)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_EXIT, .string = (t_str)
	{.str = "No", .color = 0xFF000000, .scale = 0.015}};
}

void	init_buttons_main(t_menu *menu, size_t w, size_t h)
{
	menu->buttons[BUT_START] = (t_button){.pos = (t_ulpoint){part(w, 0.5),
		part(h, 0.3)}, .dim = (t_ulpoint){part(w, 0.2),
		part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_MAIN, .string = (t_str)
	{.str = "Start", .color = 0xFF000000, .scale = 0.015}};
	menu->buttons[BUT_SETTINGS] = (t_button){.pos = (t_ulpoint){part(w, 0.5),
		part(h, 0.5)}, .dim = (t_ulpoint){part(w, 0.2),
		part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_MAIN, .string = (t_str)
	{.str = "Settings", .color = 0xFF000000, .scale = 0.015}};
	menu->buttons[BUT_EXIT] = (t_button){.pos = (t_ulpoint){part(w, 0.5),
		part(h, 0.7)}, .dim = (t_ulpoint){part(w, 0.2),
		part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF101010,
		.color_idle[1] = 0xFF505050, .color_hover[0] = 0xFF303030,
		.color_hover[1] = 0xFF707070, .window = WIN_MAIN, .string = (t_str)
	{.str = "Exit", .color = 0xFF000000, .scale = 0.015}};
}
