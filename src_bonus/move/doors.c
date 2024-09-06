/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:06:16 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/06 18:09:05 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "data.h"
#include "map.h"
#include "keys.h"

#define TIME 1.
void	open_doors(t_data *data, double delta)
{
	int			i;
	uint32_t	*cur;
	int32_t	value;
	int	stop;

	stop = 0;
	i = 0;
	while (i < 32)
	{
		if (cur == data->opening[i])
		{
			data->opening[i++] = NULL;
			continue ;
		}
		cur = data->opening[i];
		if (cur)
		{
			value = (*cur & VALUE) >> VALUEOFF;
			if (*cur & OPENING)
				value += (int32_t)(delta / TIME * (double)VALUEONE);
			else if (*cur & CLOSING)
			{
				value -= (int32_t)(delta / TIME * (double)VALUEONE);
			}
			else
				data->opening[i] = 0;
			if (value > VALUEONE * 9 / 10)
			{
				value = VALUEONE * 9 / 10;
				*cur &= ~MOVING;
				stop = 1;
			}
			else if (value < 0)
			{
				value = 0;
				*cur &= ~MOVING;
				stop = 1;
			}
			*cur = (*cur & ~VALUE) | value << VALUEOFF;
			if (stop)
				data->opening[i] = 0;
			
		}
		++i;
	}
}//FIXME door can be added twice

void	open_door(t_data *data, double delta)
{
	if (data->keys & KEY_E && data->cross && data->cross_dist < ARM_LEN
		&& (*data->cross & SPEC) == DOOR)
	{
		if ((*data->cross & MOVING))
			*data->cross = (*data->cross & ~MOVING) | (~*data->cross & MOVING);
		else if (!(*data->cross & VALUE))
			*data->cross |= OPENING;
		else
			*data->cross |= CLOSING;
		data->opening[data->i_open] = data->cross;
		data->i_open = (data->i_open + 1) % 31 + 1;
		data->keys &= ~KEY_E;
	}
	open_doors(data, delta);
}
