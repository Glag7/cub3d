/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:07:39 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/02 18:47:14 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "data.h"
#include "point.h"
#include "floor.h"

static inline __attribute__((always_inline)) void
	assign_pos_y_from_data_horizon_and_check_it_is_not_negative(
	t_data *dat, t_floor *f)
{
	f->pos.y = dat->horizon - 1;
	if (f->pos.y < -1)
		f->pos.y = -1;
}

void	draw_floor(t_data *dat)
{
	const double	camheipx = (dat->play.z + .5) * dat->set.planwid;
	const t_point	baseinc = (t_point){(dat->set.invplanwid
			* dat->play.sina), -(dat->set.invplanwid * dat->play.cosa)};
	const t_point	start = (t_point){dat->play.cosa - dat->set.tanfov
		* dat->play.sina, dat->play.sina + dat->set.tanfov * dat->play.cosa};
	t_floor			f;

	assign_pos_y_from_data_horizon_and_check_it_is_not_negative(dat, &f);
	while (++f.pos.y < (int)dat->set.hei)
	{
		f.dist = camheipx / (double)(f.pos.y - dat->horizon);
		f.inc.x = baseinc.x * f.dist * (double)dat->tmp.w;
		f.inc.y = baseinc.y * -f.dist * (double)dat->tmp.h;
		f.cur.x = (dat->play.x + f.dist * start.x) * (double)dat->tmp.w;
		f.cur.y = (dat->play.y - f.dist * start.y) * (double)dat->tmp.h;
		f.pos.x = -1;
		while (++f.pos.x < (int)dat->set.wid)
		{
			f.cur.x += f.inc.x;
			f.cur.y += f.inc.y;
			dat->mlx.px[f.pos.x + f.pos.y * dat->set.wid]
				= dat->tmp.px[((int)f.cur.x & (dat->tmp.w - 1))
				+ ((int)f.cur.y & (dat->tmp.h - 1)) * dat->tmp.w];
		}
	}
}
