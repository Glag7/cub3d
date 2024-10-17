/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:24:03 by glaguyon          #+#    #+#             */
/*   Updated: 2024/10/11 01:32:54 by glag             ###   ########.fr       */
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

# define DEF_CROSSCOLOR 0x00FF0000

# define DEF_FOV 90.
# define MIN_FOV 1.
# define MAX_FOV 179.

# define DEF_VIEW 1000.
# define MIN_VIEW 1.
# define MAX_VIEW 2000.

# define DEF_WID 680
# define MIN_WID 2
# define MAX_WID 9999

# define DEF_HEI 384
# define MIN_HEI 2
# define MAX_HEI 9999

# define DEF_SENSI .4
# define MIN_SENSI .1
# define MAX_SENSI 1.

# define MAX_ANGLE M_PI_2
# define MIN_ANGLE -M_PI

# define DEF_TEXSIZ 1024
# define DEF_SKYSIZ 2048

# define ARM_LEN 1.5

# define DEF_ACCEL 20.
# define MIN_ACCEL 10.
# define MAX_ACCEL 50.

# define DEF_ACCELAIR .3

# define DEF_ACCELDIFF 3.
# define MIN_ACCELDIFF 1.
# define MAX_ACCELDIFF 5.

# define DEF_SPEEDDIFF 2.

# define DEF_SPEEDMAX 1.5
# define MIN_SPEEDMAX .1
# define MAX_SPEEDMAX 5.

# define DEF_FASTER .5

# define DEF_SLOWER .001
# define MIN_SLOWER .001
# define MAX_SLOWER 1.

# define DEF_SLOWERAIR .8

typedef struct s_set
{
	uint32_t		saved_w;
	uint32_t		saved_h;
	uint32_t		color;
	uint32_t		ncolor;
	uint32_t		pcolor;
	uint32_t		crosscolor;
	uint32_t		pad;
	unsigned int	d;
	unsigned int	r;
	unsigned int	xoffset;
	unsigned int	yoffset;
	unsigned int	ncase;
	unsigned int	pstart;
	unsigned int	pend;
	unsigned int	texsiz;
	unsigned int	skysiz;
	double			fov_deg;
	double			fov;
	double			tanfov;
	double			view;
	double			planwid;
	double			invplanwid;
	double			ratio;
	double			sensi;
	unsigned int	wid;
	unsigned int	hei;
	double			invwid;
	double			*invlen;
	double			*coslen;
	double			accel;
	double			accelair;
	double			acceldiff;
	double			speeddiff;
	double			speedmax;
	double			faster;
	double			slower;
	double			slowerair;
}	t_set;

int		init_settings(t_set *set);
int		setfov(t_set *set, double fov_deg);
int		load_settings(t_set *set);
void	free_settings(t_set *set);

#endif
