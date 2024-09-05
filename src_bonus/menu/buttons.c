/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/27 17:27:35 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "mlx.h"
#include "utils.h"
#include "popup.h"
#include "data.h"

static int	check_button_hitbox(t_button button, size_t x, size_t y)
{
	return (x > button.pos.x - button.dim.x / 2
		&& x < button.pos.x + button.dim.x / 2
		&& y > button.pos.y - button.dim.y / 2
		&& y < button.pos.y + button.dim.y / 2);
}

static void	get_active_buttons(t_menu *menu, t_button **active_buttons)
{
	ft_bzero(active_buttons, 3 * sizeof(t_button *));
	if (menu->window == MAIN)
	{
		active_buttons[0] = &menu->buttons[0];// 0 or 1 if game already started
		active_buttons[1] = &menu->buttons[2];
		active_buttons[2] = &menu->buttons[4];
	}
	else if (menu->window == SETTINGS)
	{
		active_buttons[0] = &menu->buttons[3];
		;// more for settings ?
	}
	else
	{
		active_buttons[0] = &menu->buttons[5];
		active_buttons[1] = &menu->buttons[6];
	}
}

void	update_buttons(t_mlx *mlx, t_menu *menu, t_set *set)
{
	t_button	*active_buttons[3];
	bool	hovering;
	size_t	i;
	int	x;
	int	y;

	get_active_buttons(menu, active_buttons);
	mlx_mouse_get_pos(mlx->mlx, mlx->win, &x, &y);
	i = 0;
	while (active_buttons[i] != NULL)
	{
		hovering = check_button_hitbox(*active_buttons[i], (size_t)x, (size_t)y);
		if (active_buttons[i]->state == IDLE && hovering == 1)
		{
			draw_button(mlx, set, *active_buttons[i], HOVER);
			active_buttons[i]->state = HOVER;
		}
		else if (active_buttons[i]->state == HOVER && hovering == 0)
		{
			draw_button(mlx, set, *active_buttons[i], IDLE);
			active_buttons[i]->state = IDLE;
		}
		i++;
	}
}

static void	update_menu(t_data *data, size_t i)
{
	if (data->menu.window == MAIN)
	{
		if (i == 0)// start/resume
			data->game_state = GAME;// start game
		else if (i == 1)// settings
			draw_settings_menu(&data->mlx, &data->menu, &data->set);//build settings popup
		else if (i == 2)// exit
			draw_exit_menu(&data->mlx, &data->menu, &data->set);// build exit popup
	}
	else if (data->menu.window == SETTINGS)
	{
		if (i == 0)// back
			draw_main_menu(&data->mlx, &data->menu, &data->set);// build main menu
	}
	else if (data->menu.window == EXIT)
	{
		if (i == 0)// yes
			;// quitter
		else if (i == 1)// no
			draw_main_menu(&data->mlx, &data->menu, &data->set);// build main menu
	}
}

#include <stdio.h>
void	menu_mouse_hook(int button, int x, int y, t_data *data)
{
	t_button	*active_buttons[3];
	size_t		i;

	printf("mouse event = %i\n", button);// test pour voir si le relevement est detecte
	if (button != 1)
		return ;
	get_active_buttons(&data->menu, active_buttons);
	i = 0;
	while (active_buttons[i] != NULL)
	{
		if (check_button_hitbox(data->menu.buttons[i], (size_t)x, (size_t)y) == 1)
		{
			update_menu(data, i);
			break ;
		}
		i++;
	}
}
