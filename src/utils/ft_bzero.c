/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:32:13 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/18 17:03:32 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	ft_bzero(void *restrict s, size_t n)
{
	size_t	ptr;

	ptr = (size_t) s;
	if (n >= 8)
	{
		while (ptr % 8)
		{
			*(uint8_t *)ptr = 0;
			ptr += 1;
			n -= 1;
		}
	}
	while (n >= 8)
	{
		*(uint64_t *)ptr = 0;
		ptr += 8;
		n -= 8;
	}
	while (n)
	{
		*(uint8_t *)ptr = 0;
		ptr += 1;
		n -= 1;
	}
}
