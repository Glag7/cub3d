/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:06:16 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/18 16:02:20 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "data.h"
#include "map.h"
#include "keys.h"

static inline __attribute__((always_inline)) int
	check_value(int32_t *value, uint32_t *cur)
{
	if (*value > VALUEONE * 9 / 10 && (*cur & SPEC) == DOOR)
	{
		*value = VALUEONE * 9 / 10;
		*cur &= ~MOVING;
		return (1);
	}
	else if (*value > VALUEONE && (*cur & SPEC) == FENCE)
	{
		*value = VALUEONE;
		*cur &= ~MOVING;
		return (1);
	}
	else if (*value < 0)
	{
		*value = 0;
		*cur &= ~MOVING;
		return (1);
	}
	return (0);
}

void	open_doors(t_data *data, double delta)
{
	int			i;
	int			stop;
	uint32_t	*cur;
	int32_t		value;

	i = -1;
	while (++i < 32)
	{
		if (cur == data->opening[i] || !data->opening[i])
			continue ;
		cur = data->opening[i];
		value = (*cur & VALUE) >> VALUEOFF;
		if (*cur & OPENING)
			value += (int32_t)(delta / ANIM_TIME * (double)VALUEONE);
		else if (*cur & CLOSING)
			value -= (int32_t)(delta / ANIM_TIME * (double)VALUEONE);
		else
			data->opening[i] = 0;
		stop = check_value(&value, cur);
		*cur = (*cur & ~VALUE) | value << VALUEOFF;
		if (stop)
			data->opening[i] = 0;
	}
}

void	open_door(t_data *data, double delta)
{
	if (data->keys & KEY_E && data->cross && data->cross_dist < ARM_LEN
		&& ((*data->cross & SPEC) == DOOR || (*data->cross & SPEC) == FENCE))
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
