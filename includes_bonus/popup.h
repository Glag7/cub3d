/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:50:21 by ttrave            #+#    #+#             */
/*   Updated: 2024/08/08 17:12:01 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

/* ----- INCLUDES ----- */

# include <stdbool.h>
# include "specs.h"
# include "map.h"
# include "img.h"
# include "set.h"

/* ----- ENUMERATIONS ----- */

enum
{
	MENU = 0,
	GAME
};

enum
{
	MAIN = 0,
	SETTINGS,
	EXIT
};

enum
{
	IDLE = 0,
	HOVER
};

/* ----- STRUCTURES ----- */

typedef struct s_button
{
	t_ulpoint	pos;
	t_ulpoint	dim;
	t_img		string;
	uint32_t	color_idle[2];
	uint32_t	color_hover[2];
	bool		state;
}	t_button;

typedef struct s_menu
{
	t_img		title;
	t_img		confirm;
	uint32_t	*background;
	t_button	buttons[7];
	uint8_t		window;
	uint8_t		resume;
	uint8_t		first_render;
	uint8_t		prev_tab;
}	t_menu;

#endif
