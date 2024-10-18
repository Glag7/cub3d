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

# include <stdbool.h>
# include "map.h"
# include "img.h"
# include "set.h"
# include "data.h"
# include "popup.h"

/* ----- PROTOTYPES ----- */

int		init_menu(t_mlx *mlx, t_menu *menu, t_set *set);

void	init_buttons_settings(t_menu *menu, size_t w, size_t h);
void	init_buttons_exit(t_menu *menu, size_t w, size_t h);
void	init_buttons_main(t_menu *menu, size_t w, size_t h);

void	init_textfields_settings_movements(t_set *set, t_menu *menu, size_t w, size_t h);
void	init_textfields_settings(t_set *set, t_menu *menu, size_t w, size_t h);

bool	check_hitbox(t_ulpoint pos, t_ulpoint dim, size_t x, size_t y);
void	update_buttons(t_data *data);

void	save_background(t_data *data);
void	draw_background(t_data *data);
void	draw_rectangle(t_data *data, t_ulpoint pos, t_ulpoint dim, uint32_t *colors);
void	draw_image(t_data *data, t_ulpoint pos, t_img string);
void	draw_button(t_data *data, t_button button, uint8_t state);

void	draw_main_menu(t_data *data);
void	draw_settings_menu(t_data *data);
void	draw_exit_menu(t_data *data);

void	build_menu(t_data *data);
void	close_menu(t_data *data);

void	menu_mouse_hook(int x, int y, t_data *data);
void	menu_unmouse_hook(int x, int y, t_data *data);

double	check_input(double input, size_t i);

void	save_textfields(t_data *data);
void	save_sliders(t_data *data);

void	draw_slider(t_data *data, t_slider slider);
void	update_sliders(t_data *data);

void	build_textfield(t_data *data, t_textfield textfield);
void	update_textfields(t_data *data);

void	print_uint(t_data *data, t_textfield textfield, double scale,
		size_t len);
void	print_double(t_data *data, t_textfield textfield, double scale,
		size_t len);

void	draw_string(t_data *data, t_str string, t_ulpoint pos, t_ulpoint dim);

uint32_t	get_pixel(uint32_t src_px, uint32_t add_px);
size_t	part(size_t n, double fraction);
void	free_menu(t_menu *menu);

void	manage_menu(t_data *data);
void	manage_menu_hooks(t_data *data);

#endif
