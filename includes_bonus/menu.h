/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:50:21 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/08 17:12:01 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

/* ----- INCLUDES ----- */

# include "map.h"
# include "img.h"
# include "set.h"
# include "data.h"
# include "popup.h"

/* ----- PROTOTYPES ----- */

void	update_buttons(t_mlx *mlx, t_menu *menu, t_set *set);
void	menu_mouse_hook(int button, int x, int y, t_data *data);

void	save_background(t_mlx *mlx, t_menu *menu, t_set *set);
void	draw_background(t_mlx *mlx, t_menu *menu, t_set *set);
void	draw_rectangle(t_mlx *mlx, t_set *set, t_ulpoint pos, t_ulpoint dim, uint32_t *colors);
void	draw_string(t_mlx *mlx, t_set *set, t_ulpoint pos, t_img string);
void	draw_button(t_mlx *mlx, t_set *set, t_button button, bool state);

int		init_menu(t_mlx *mlx, t_menu *menu, t_set *set);

void	draw_main_menu(t_mlx *mlx, t_menu *menu, t_set *set);
void	draw_settings_menu(t_mlx *mlx, t_menu *menu, t_set *set);
void	draw_exit_menu(t_mlx *mlx, t_menu *menu, t_set *set);
void	build_menu(t_mlx *mlx, t_menu *menu, t_set *set, uint8_t *game_state);

size_t	part(size_t n, double fraction);
void	free_menu(t_menu *menu);

#endif
