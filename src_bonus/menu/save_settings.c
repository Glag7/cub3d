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

void	save_sliders(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < NB_SLIDERS)
	{
		if (data->menu.sliders[i].state == PRESS)
		{
			if (data->menu.sliders[i].type == UINT)
				*(uint32_t *)data->menu.sliders[i].dst
					= (uint32_t)data->menu.sliders[i].v_curr;
			else if (data->menu.sliders[i].type == DOUBLE)
				*(double *)data->menu.sliders[i].dst
					= data->menu.sliders[i].v_curr;
			data->menu.sliders[i].state = IDLE;
			break ;
		}
		i++;
	}
	// appliquer fonction pour modifier fov (et autres options eventuellement)
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

void	save_textfield(t_data *data, t_textfield *textfield)
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
	textfield->v_curr = input;
	if (textfield->precision == 0)
		*(uint32_t *)textfield->dst = (uint32_t)textfield->v_curr;
	else
		*(double *)textfield->dst = textfield->v_curr;
	// appliquer fonction pour modifier fov (et autres options eventuellement)
}

void	save_textfields(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < NB_TEXTFIELDS)
	{
		if (data->menu.textfields[i].state == PRESS)
		{
			save_textfield(data, &data->menu.textfields[i]);
			data->menu.textfields[i].state = IDLE;
			break ;
		}
		i++;
	}
}
