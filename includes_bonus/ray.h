/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:47:00 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/15 18:25:15 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "point.h"

typedef struct s_ray
{
	t_point		pos;
	t_point		vec;
	t_point		step;
	t_point		dist;
	t_ipoint	ipos;
	t_ipoint	istep;
	int			hit;
	int			side;
	double		len;
}	t_ray;

typedef struct s_draw
{
	double	index;
	double	ypx;
	int		i;
	int		start;
	int		end;
}	t_draw;

#endif
