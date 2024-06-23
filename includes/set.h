/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:24:03 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/23 15:13:08 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_H
# define SET_H

# include <stdint.h>

# define DEF_D 151
# define DEF_OFFSET 20
# define DEF_NCASE 5
# define DEF_COLOR 0x00FFFFDD
# define DEF_NCOLOR 0x00111111
# define DEF_PCOLOR 0x00EE1111

# define DEF_FOV 90.
# define DEF_VIEW 10.

# define DEF_LWID 1
# define DEF_WID 1360
# define DEF_HEI 768

typedef struct s_set
{
	unsigned int	d;
	unsigned int	r;
	unsigned int	xoffset;
	unsigned int	yoffset;
	unsigned int	ncase;
	unsigned int	pstart;
	unsigned int	pend;
	uint32_t		color;
	uint32_t		ncolor;
	uint32_t		pcolor;
	double			ratio;

	double			fov;
	double			view;

	unsigned int	lwid;
	unsigned int	nthread;
	unsigned int	offthread;
	unsigned int	wid;
	unsigned int	hei;
	uint32_t		__padding2;
}	t_set;

void	init_settings(t_set *set);

#endif
