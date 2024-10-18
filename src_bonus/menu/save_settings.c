/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/09/21 19:02:48 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "data.h"
#include "menu.h"

static void	update_fov(t_set *set, double fov_deg)
{
	size_t	i;
	double	cur;
	double	inc;

	set->fov_deg = fov_deg;
	set->fov = fov_deg * M_PI / 180.;
	set->tanfov = tan(set->fov * .5);
	set->planwid = (double)set->wid / (set->tanfov * 2.);
	set->invplanwid = 1. / set->planwid;
	cur = set->tanfov;
	inc = -2. * set->tanfov * set->invwid;
	i = 0;
	while (i < set->wid)
	{
		set->invlen[i] = 1. / sqrt(1. + cur * cur);
		set->coslen[i] = cos(atan2(cur * set->invlen[i], set->invlen[i]));
		++i;
		cur += inc;
	}
}

void	save_sliders(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < NB_SLIDERS)
	{
		if (data->menu.sliders[i].state == PRESS)
		{
			data->menu.sliders[i].state = IDLE;
			break ;
		}
		i++;
	}
	update_fov(&data->set, data->set.fov_deg);
}

static int	check_syntax_input(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] == '-')
		i++;
	if (i > 1 || str[i] < '0' || str[i] > '9')
		return (1);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] != '.')
		return (1);
	i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] <= '0' || str[i] > '9')
		return (1);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

static void	save_textfield(t_data *data, t_textfield *textfield, size_t i)
{
	double	input;

	if (check_syntax_input(textfield->buffer) == 1)
	{
		build_textfield(data, *textfield);
		return ;
	}
	input = atof(textfield->buffer);
	if (input < textfield->v_min)
		input = textfield->v_min;
	else if (input > textfield->v_max)
		input = textfield->v_max;
	input = check_input(input, i);
	if (textfield->type == UINT)
		*(uint32_t *)textfield->dst = (uint32_t)input;
	else
		*(double *)textfield->dst = input;
	update_fov(&data->set, data->set.fov_deg);
}

void	save_textfields(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < NB_TEXTFIELDS)
	{
		if (data->menu.textfields[i].state == PRESS)
		{
			save_textfield(data, &data->menu.textfields[i], i);
			break ;
		}
		i++;
	}
}
