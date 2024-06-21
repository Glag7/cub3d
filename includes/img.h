/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:15:51 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/21 19:52:19 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

# define DEF_WID 1360
# define DEF_HEI 768
# define DEF_D 151
# define DEF_OFFSET 20

# include <stddef.h>
# include <stdint.h>

typedef struct s_min
{
	uint8_t		*mask;
	unsigned int	d;
	unsigned int	offset;
}	t_min;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	uint32_t	*px;
	t_min		mini;
	unsigned int	wid;
	unsigned int	hei;
	uint64_t	keys;
}	t_mlx;

void	free_mlx(t_mlx *mlx);
int		init_mlx(t_mlx *mlx);

#endif
