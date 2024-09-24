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

# include "specs.h"
# include "map.h"
# include "img.h"
# include "set.h"

/* ----- DEFINES ----- */

# define NB_BUTTONS	6
# define NB_SETTINGS	3

# define OUTLINE_WIDTH	5
# define GRADIENT_WIDTH	5
# define PREV_TAB	1

# define WIDTH_CHAR	5
# define HEIGHT_CHAR	7

# define WIDTH_CHAR_IMG		205
# define HEIGHT_CHAR_IMG	7

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
	HOVER,
	PRESS
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

enum
{
	SET_FOV = 0,
	SET_VIEW,
	SET_SENSI
};

enum
{
	UINT = 0,
	DOUBLE
};

/* ----- STRUCTURES ----- */

typedef struct s_string
{
	char		*str;
	uint32_t	color;
}	t_str;

typedef struct s_textfield
{
	t_ulpoint	pos;
	t_ulpoint	dim;
	uint8_t		type;
	double		*src;
}	t_textfield;

typedef struct s_slider
{
	t_ulpoint	pos;
	t_ulpoint	dim;
	uint8_t		state;
	uint8_t		type;
	void		*dst;
	double		v_min;
	double		v_max;
	double		v_curr;
}	t_slider;

typedef struct s_button
{
	t_ulpoint	pos;
	t_ulpoint	dim;
	t_img		string;
	uint32_t	color_idle[2];
	uint32_t	color_hover[2];
	uint8_t		state;
	uint8_t		window;
}	t_button;

typedef struct s_menu
{
	t_img		title;
	t_img		confirm;
	t_img		resume;
	uint32_t	*background;
	t_button	buttons[NB_BUTTONS];
	t_slider	sliders[NB_SETTINGS];
	t_textfield	textfields[NB_SETTINGS];
	t_img		characters;
	uint8_t		window;
	uint8_t		first_start;
	uint8_t		first_render;
	uint8_t		prev_keys;
	t_ulpoint	save_mouse;
}	t_menu;

#endif
