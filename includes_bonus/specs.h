/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:46:30 by glaguyon          #+#    #+#             */
/*   Updated: 2024/10/09 21:06:45 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECS_H
# define SPECS_H

/* ----- INCLUDES ----- */

# include <stddef.h>
# include <stdint.h>
# include "point.h"

# define PAD 64

/* ----- SRUCTURES ----- */

typedef struct s_ulpoint
{
	size_t	x;
	size_t	y;
}	t_ulpoint;

typedef struct s_dimensions
{
	size_t	w;
	size_t	h;
}	t_dim;

typedef struct s_specifications
{
	void		*img_mlx;
	uint32_t	*img_src;
	size_t		size_line;
	t_dim		dim_src;
	t_dim		dim_dst;
	t_point		mapping;
}	t_specs;

#endif
