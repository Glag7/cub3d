/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:25:35 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 15:30:49 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	paint(uint32_t *px_, uint64_t color, size_t len)
{
	uint64_t	*px;

	px = (uint64_t *)px_;
	len >>= 2;
	while (len)
	{
		*px = color;
		++px;
		--len;
	}
}
