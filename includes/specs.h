/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:46:30 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/15 17:49:10 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECS_H
# define SPECS_H

#include <stdint.h>

typedef struct s_specs
{
	void	*mlx_img;
	char	*img_bin;
	int32_t	bpp;
	int32_t	size_line;
	bool	endian;
	int32_t	w;
	int32_t	h;
	double	dim_rect[2];
}	t_specs;

#endif
