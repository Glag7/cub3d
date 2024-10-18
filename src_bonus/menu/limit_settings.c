/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:58:59 by ttrave            #+#    #+#             */
/*   Updated: 2024/10/19 19:02:48 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "popup.h"

double	check_input(double input, size_t i)
{
	size_t	n;

	if (i == SET_WID || i == SET_HEI)
		return ((double)((uint32_t)input - ((uint32_t)input & 1)));
	else if (i == SET_TEXSIZ || i == SET_SKYSIZ)
	{
		n = (size_t)1 << (8 * sizeof(size_t) - 1);
		while (n > 0 && n > (size_t)input)
			n >>= 1;
		if ((size_t)input > n + n / 2)
			return ((double)(n << 1));
		else
			return ((double)n);
	}
	else
		return (input);
}
