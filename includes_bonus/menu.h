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
# include "specs.h"
# include "map.h"
# include "img.h"
# include "set.h"

/* ----- DEFINES ----- */

# define DEFAULT_COLOR	.color_idle[0] = 0x00101010, .color_idle[1] = 0x00505050, \
.color_hover[0] = 0x00303030, .color_hover[1] = 0x00707070
# define EXIT_COLOR		.color_idle[0] = 0x00101010, .color_idle[1] = 0x00ff1b1e, \
.color_hover[0] = 0x00303030, .color_hover[1] = 0x00ff3d40

/* ----- ENUMERATIONS ----- */

enum
{
	MENU = 0,
	GAME
};

enum
{
	IDLE = 0,
	HOVER
};

enum
{
	MAIN = 0,
	SETTINGS,
	EXIT
};

/* ----- STRUCTURES ----- */

typedef struct s_button
{
	t_ulpoint	pos;
	t_ulpoint	dim;
	t_img		string;
	uint32_t	color_idle[2];// outline, inside
	uint32_t	color_hover[2];
	bool		state;
}	t_button;

typedef struct s_menu
{
	t_img		title;
	uint32_t	*background;
	t_button	buttons[7];
	uint8_t		window;
}	t_menu;

/* ----- PROTOTYPES ----- */

void	update_buttons(t_mlx *mlx, t_menu *menu, t_set *set);

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
