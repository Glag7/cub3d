/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:24:03 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/08 17:01:49 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_H
# define SET_H

# include <stdint.h>
# include <math.h>

# define DEF_D 151
# define DEF_OFFSET 20
# define DEF_NCASE 6
# define DEF_COLOR 0x00FFFFDD
# define DEF_NCOLOR 0x00111111
# define DEF_PCOLOR 0x00EE1111

# define DEF_FOV 90.
# define DEF_VIEW 1000.

# define DEF_WID 1360
# define DEF_HEI 768

# define DEF_SENSI .4

# define MAX_ANGLE M_PI_2
# define MIN_ANGLE -M_PI

# define DEF_TEXSIZ 1024
# define DEF_SKYSIZ 2048

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

	unsigned int	texsiz;
	unsigned int	skysiz;

	double			fov_deg;
	double			fov;
	double			tanfov;
	double			view;
	double			planwid;
	double			invplanwid;

	double			sensi;
	unsigned int	wid;
	unsigned int	hei;
	double			invwid;
	double			*invlen;
	double			*coslen;
}	t_set;

int		init_settings(t_set *set);
int		setfov(t_set *set, double fov_deg);
void	free_settings(t_set *set);

#endif
