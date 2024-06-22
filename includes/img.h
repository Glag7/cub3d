/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:15:51 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 16:16:31 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

# include <stdint.h>

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	uint32_t	*px;
}	t_mlx;

void	free_mlx(t_mlx *mlx);
int		init_mlx(t_mlx *mlx, unsigned int wid, unsigned int hei);

#endif
