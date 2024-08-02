/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:46:23 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/02 18:47:20 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOOR_H
# define FLOOR_H

# include "point.h"

typedef struct s_floor
{
	t_ipoint	pos;
	t_point		inc;
	t_point		cur;
	double		dist;
}	t_floor;

#endif
