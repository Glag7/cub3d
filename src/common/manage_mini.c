/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:17:52 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 16:46:12 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "set.h"
#include "mini.h"
#include "utils.h"

static void	fill_custom(uint8_t *mask, unsigned int d, unsigned int r)
{
	unsigned int	i;
	unsigned int	j;
	int			x;
	int			y;

	i = 0;
	while (i < d)
	{
		j = 0;
		while (j < d)
		{
			x = i - r;
			y = j - r;
			if ((unsigned int)sqrt((float)(x * x + y * y)) > r
				&& (i + j) % 2)
				mask[i + j * d] = 0;
			else
				mask[i + j * d] = 1;
			j++;
		}
		i++;
	}
}

static void	fill_circle(uint8_t *mask, unsigned int d, unsigned int r)
{
	unsigned int	i;
	unsigned int	j;
	int			x;
	int			y;

	i = 0;
	while (i < d)
	{
		j = 0;
		while (j < d)
		{
			x = i - r;
			y = j - r;
			if ((unsigned int)sqrt((float)(x * x + y * y)) > r)
				mask[i + j * d] = 0;
			else
				mask[i + j * d] = 1;
			j++;
		}
		i++;
	}
}

static void	fill_square(uint8_t *mask, unsigned int d)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < d)
	{
		j = 0;
		while (j < d)
		{
			mask[i + j * d] = 0;
			mask[i + j * d] = 1;
			j++;
		}
		i++;
	}
}

int	init_mini(t_mini *mini, t_set *set)
{
	mini->m_circle = malloc(set->d * set->d);
	mini->m_square = malloc(set->d * set->d);
	mini->m_custom = malloc(set->d * set->d);
	mini->m_curr = mini->m_custom;//
	if (mini->m_circle == NULL || mini->m_square == NULL || mini->m_custom == NULL)
	{
		free(mini->m_circle);
		free(mini->m_square);
		free(mini->m_custom);
		return (1);
	}
	fill_circle(mini->m_circle, set->d, set->r);
	fill_square(mini->m_square, set->d);
	fill_custom(mini->m_custom, set->d, set->r);
	return (0);
}

void	free_mini(t_mini *mini)
{
	free(mini->m_circle);
	free(mini->m_square);
	free(mini->m_custom);
	ft_bzero(mini, sizeof(*mini));
}
