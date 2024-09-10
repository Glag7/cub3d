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

/* ----- DEFINES ----- */

# define NB_BUTTONS	6
# define OUTLINE_WIDTH	5

/* ----- ENUMERATIONS ----- */

enum
{
	WIN_MAIN = 0,
	WIN_SETTINGS,
	WIN_EXIT
};

enum
{
	IDLE = 0,
	HOVER
};

enum
{
	BUT_START = 0,
	BUT_SETTINGS,
	BUT_BACK,
	BUT_EXIT,
	BUT_YES,
	BUT_NO
};

/* ----- STRUCTURES ----- */

typedef struct s_slider
{
	t_ulpoint	pos;
	t_ulpoint	dim;
	union
	{
		uint32_t	*data;
		double		*data;
	}
	union
	{
		uint32_t	v_min;
		double		v_min;
	}
	union
	{
		uint32_t	v_max;
		double		v_max;
	}
}	t_slider;

typedef struct s_button
{
	t_ulpoint	pos;
	t_ulpoint	dim;
	t_img		string;
	uint32_t	color_idle[2];
	uint32_t	color_hover[2];
	bool		state;
	uint8_t		window;
}	t_button;

typedef struct s_menu
{
	t_img		title;
	t_img		confirm;
	t_img		resume;
	uint32_t	*background;
	t_button	buttons[NB_BUTTONS];
	uint8_t		window;
	uint8_t		first_start;
	uint8_t		first_render;
	uint8_t		prev_tab;
}	t_menu;

#endif
