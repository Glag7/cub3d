/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:15:50 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/06 17:03:34 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "data.h"
#include "keys.h"

#define LEFT 1
#define MIDDLE 2
#define RIGHT 3

int	mouse_hook(int click, int x, int y, void *data_)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = data_;
	if (click == LEFT)
	{
		data->lastshot = 0.;
		data->keys |= KEY_LM;
	}
	return (0);
}
