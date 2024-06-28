/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:04:47 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 18:48:56 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "data.h"
#include "img.h"

int	win_hook(void *data_)
{
	t_data	*data;

	data = data_;
	mlx_loop_end(data->mlx.mlx);
	return (0);
}
