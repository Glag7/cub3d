/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_textfields.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:30:55 by ttrave            #+#    #+#             */
/*   Updated: 2024/10/16 18:33:06 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "popup.h"
#include "menu.h"

void	init_textfields_settings_movements(t_set *set, t_menu *menu,
	size_t w, size_t h)
{
	menu->textfields[SET_SPEEDMAX] = (t_textfield){.pos = (t_ulpoint){part(w,
			0.17), part(h, 0.73)}, .dim = (t_ulpoint){part(w, 0.12), part(h,
			0.06)}, .precision = 2, .v_min = MIN_SPEEDMAX,
		.v_max = MAX_SPEEDMAX, .dst = &set->speedmax, .state = IDLE, .len = 0,
		.type = DOUBLE};
	menu->textfields[SET_ACCEL] = (t_textfield){.pos = (t_ulpoint){part(w,
			0.57), part(h, 0.31)}, .dim = (t_ulpoint){part(w, 0.12), part(h,
			0.06)}, .precision = 2, .v_min = MIN_ACCEL, .v_max = MAX_ACCEL,
		.dst = &set->accel, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_ACCELDIFF] = (t_textfield){.pos = (t_ulpoint){part(w,
			0.57), part(h, 0.45)}, .dim = (t_ulpoint){part(w, 0.12), part(h,
			0.06)}, .precision = 3, .v_min = MIN_ACCELDIFF,
		.v_max = MAX_ACCELDIFF, .dst = &set->acceldiff, .state = IDLE, .len = 0,
		.type = DOUBLE};
	menu->textfields[SET_SLOWER] = (t_textfield){.pos = (t_ulpoint){part(w,
			0.57), part(h, 0.59)}, .dim = (t_ulpoint){part(w, 0.12), part(h,
			0.06)}, .precision = 3, .v_min = MIN_SLOWER, .v_max = MAX_SLOWER,
		.dst = &set->slower, .state = IDLE, .len = 0, .type = DOUBLE};
}

void	init_textfields_settings(t_set *set, t_menu *menu, size_t w,
	size_t h)
{
	menu->textfields[SET_FOV] = (t_textfield){.pos = (t_ulpoint){part(w, 0.17),
		part(h, 0.31)}, .dim = (t_ulpoint){part(w, 0.12), part(h, 0.06)},
		.precision = 0, .v_min = MIN_FOV, .v_max = MAX_FOV,
		.dst = &set->fov_deg, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_VIEW] = (t_textfield){.pos = (t_ulpoint){part(w, 0.17),
		part(h, 0.45)}, .dim = (t_ulpoint){part(w, 0.12), part(h, 0.06)},
		.precision = 0, .v_min = MIN_VIEW, .v_max = MAX_VIEW,
		.dst = &set->view, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_SENSI] = (t_textfield){.pos = (t_ulpoint){part(w,
			0.17), part(h, 0.59)}, .dim = (t_ulpoint){part(w, 0.12), part(h,
			0.06)}, .precision = 2, .v_min = MIN_SENSI, .v_max = MAX_SENSI,
		.dst = &set->sensi, .state = IDLE, .len = 0, .type = DOUBLE};
	menu->textfields[SET_WID] = (t_textfield){.pos = (t_ulpoint){part(w, 0.63),
		part(h, 0.73)}, .dim = (t_ulpoint){part(w, 0.12), part(h, 0.06)},
		.precision = 0, .v_min = (double)MIN_WID, .v_max = (double)MAX_WID,
		.dst = &set->saved_w, .state = IDLE, .len = 0, .type = UINT};
	menu->textfields[SET_HEI] = (t_textfield){.pos = (t_ulpoint){part(w, 0.77),
		part(h, 0.73)}, .dim = (t_ulpoint){part(w, 0.12), part(h, 0.06)},
		.precision = 0, .v_min = (double)MIN_WID, .v_max = (double)MAX_WID,
		.dst = &set->saved_h, .state = IDLE, .len = 0, .type = UINT};
}
