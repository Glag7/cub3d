/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/27 17:27:35 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img.h"
#include "menu.h"
#include "set.h"
#include "popup.h"

void	draw_main_menu(t_mlx *mlx, t_menu *menu, t_set *set)
{
	draw_background(mlx, menu, set);
	draw_string(mlx, set, (t_ulpoint){.x = part(set->wid, 0.5), .y = part(set->hei, 0.2)}, menu->title);
	draw_button(mlx, set, menu->buttons[0], IDLE);// 0 ou 1 si deja commence
	draw_button(mlx, set, menu->buttons[2], IDLE);
	draw_button(mlx, set, menu->buttons[4], IDLE);
	menu->window = MAIN;
}

void	draw_settings_menu(t_mlx *mlx, t_menu *menu, t_set *set)
{
	uint32_t	colors[2];

	colors[0] = 0x00101010;
	colors[1] = 0x00505050;
	draw_background(mlx, menu, set);
	draw_rectangle(mlx, set, (t_ulpoint){.x = part(set->wid, 0.5), .y = part(set->hei, 0.5)}, (t_ulpoint){.x = part(set->wid, 0.5), .y = part(set->hei, 0.8)}, colors);
	draw_button(mlx, set, menu->buttons[3], IDLE);
	;// draw options
	menu->window = SETTINGS;
}

void	draw_exit_menu(t_mlx *mlx, t_menu *menu, t_set *set)
{
	uint32_t	colors[2];

	colors[0] = 0x00101010;
	colors[1] = 0x00505050;
	draw_background(mlx, menu, set);
	draw_rectangle(mlx, set, (t_ulpoint){.x = part(set->wid, 0.5), .y = part(set->hei, 0.5)}, (t_ulpoint){.x = part(set->wid, 0.2), .y = part(set->hei, 0.25)}, colors);
	draw_button(mlx, set, menu->buttons[5], IDLE);
	draw_button(mlx, set, menu->buttons[6], IDLE);
	menu->window = EXIT;
}

void	build_menu(t_mlx *mlx, t_menu *menu, t_set *set, uint8_t *game_state)
{
	*game_state = MENU;
	save_background(mlx, menu, set);
	draw_main_menu(mlx, menu, set);
}
