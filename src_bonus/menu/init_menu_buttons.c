/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_buttons.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:00:12 by ttrave            #+#    #+#             */
/*   Updated: 2024/10/16 18:06:24 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "menu.h"

void	init_buttons_settings(t_menu *menu, size_t w, size_t h)
{
	menu->buttons[BUT_BACK] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.17),
		.y = part(h, 0.83)}, .dim = (t_ulpoint){.x = part(w, 0.1),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF202020,
		.color_idle[1] = 0xFF3f6881, .color_hover[0] = 0xFF505050,
		.color_hover[1] = 0xFF5D869F, .window = WIN_SETTINGS, .string = (t_str)
	{.str = "Back", .color = 0xFF202020, .scale = 0.015}};
}

void	init_buttons_exit(t_menu *menu, size_t w, size_t h)
{
	menu->buttons[BUT_YES] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.45),
		.y = part(h, 0.55)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF202020,
		.color_idle[1] = 0xFFD03030, .color_hover[0] = 0xFF505050,
		.color_hover[1] = 0xFFEE4E4E, .window = WIN_EXIT, .string = (t_str)
	{.str = "Yes", .color = 0xFF202020, .scale = 0.015}};
	menu->buttons[BUT_NO] = (t_button){.pos = (t_ulpoint){.x = part(w, 0.55),
		.y = part(h, 0.55)}, .dim = (t_ulpoint){.x = part(w, 0.08),
		.y = part(h, 0.08)}, .state = IDLE, .color_idle[0] = 0xFF202020,
		.color_idle[1] = 0xFF3f6881, .color_hover[0] = 0xFF505050,
		.color_hover[1] = 0xFF5D869F, .window = WIN_EXIT, .string = (t_str)
	{.str = "No", .color = 0xFF202020, .scale = 0.015}};
}

void	init_buttons_main(t_menu *menu, size_t w, size_t h)
{
	menu->buttons[BUT_START] = (t_button){.pos = (t_ulpoint){part(w, 0.5),
		part(h, 0.3)}, .dim = (t_ulpoint){part(w, 0.2),
		part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF202020,
		.color_idle[1] = 0xFF3f6881, .color_hover[0] = 0xFF505050,
		.color_hover[1] = 0xFF5D869F, .window = WIN_MAIN, .string = (t_str)
	{.str = "Start", .color = 0xFF202020, .scale = 0.015}};
	menu->buttons[BUT_SETTINGS] = (t_button){.pos = (t_ulpoint){part(w, 0.5),
		part(h, 0.5)}, .dim = (t_ulpoint){part(w, 0.2),
		part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF202020,
		.color_idle[1] = 0xFF3f6881, .color_hover[0] = 0xFF505050,
		.color_hover[1] = 0xFF5D869F, .window = WIN_MAIN, .string = (t_str)
	{.str = "Settings", .color = 0xFF202020, .scale = 0.015}};
	menu->buttons[BUT_EXIT] = (t_button){.pos = (t_ulpoint){part(w, 0.5),
		part(h, 0.7)}, .dim = (t_ulpoint){part(w, 0.2),
		part(h, 0.1)}, .state = IDLE, .color_idle[0] = 0xFF202020,
		.color_idle[1] = 0xFF3f6881, .color_hover[0] = 0xFF505050,
		.color_hover[1] = 0xFF5D869F, .window = WIN_MAIN, .string = (t_str)
	{.str = "Exit", .color = 0xFF202020, .scale = 0.015}};
}
