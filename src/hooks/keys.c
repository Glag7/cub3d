/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:19:12 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/19 16:54:11 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include "mlx.h"
#include "data.h"
#include "img.h"

int	key_hook(int key, void *data_)
{
	t_data	*data;

	data = data_;
	printf("%d\n", key);
	if (key == XK_Escape)
		mlx_loop_end(data->mlx.mlx);
	return (0);
}
