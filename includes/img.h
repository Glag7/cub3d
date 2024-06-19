/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:15:51 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/19 15:01:09 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

# define DEF_WID 1360
# define DEF_HEI 768

# include <stdint.h>

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	size_t		wid;
	size_t		hei;
	uint32_t	*px;
}	t_mlx;

void	free_mlx(t_mlx *mlx);
int		init_mlx(t_mlx *mlx);

#endif
