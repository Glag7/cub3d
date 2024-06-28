/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:46:30 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 18:03:52 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECS_H
# define SPECS_H

typedef struct s_specs
{
	void	*mlx_img;
	char	*img_bin;
	int		size_line;
	int		w;
	int		h;
	double	dim_rect[2];
}	t_specs;

#endif
