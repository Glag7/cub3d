/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:25:29 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 19:10:49 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdint.h>
# include "set.h"

typedef struct s_mini
{
	uint8_t	*m_curr;
	uint8_t	*m_circle;
	uint8_t	*m_square;
	uint8_t	*m_custom;
}	t_mini;

int		init_mini(t_mini *mini, t_set *set);
void	set_diameter(t_set *set, unsigned int d);
void	free_mini(t_mini *mini);

#endif
