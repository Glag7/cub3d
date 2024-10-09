/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:33:46 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/18 16:40:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "data.h"
#include "map.h"
#include "keys.h"

void	shoot(t_data *data, double delta)
{
	uint32_t	value;

	if (!(data->keys & KEY_LM) || !data->cross)
		return ;
	value = *data->cross;
	if ((value & CUBE) < 2)
		*data->cross = 0;
	else if (((int)(delta * 123456789.) & 3) == 2)
		*data->cross -= 1;
	data->keys &= ~KEY_LM;
}
