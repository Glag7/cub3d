/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_glass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:27:54 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/14 17:07:22 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include "data.h"
#include "map.h"
#include "ray.h"

static inline void __attribute__((always_inline))
	init_ddata(t_data *data, t_draw *ddata, double hei, double inc)
{
	const double	zoffset = data->set.planwid * data->play.az / M_PI * 4.
		+ hei * data->play.z;

	ddata->start = ((double)data->set.hei - hei * .25) * .5 + zoffset + 2.5;
	ddata->end = ((double)data->set.hei + hei) * .5 + zoffset + 2.5;
	ddata->index = 0.;
	ddata->ypx = data->px.y;
	if (ddata->start < 0.)
	{
		ddata->index = (double)-ddata->start * inc;
		ddata->start = 0.;
	}
	else if (ddata->start >= (int)data->set.hei)
		ddata->start = data->set.hei;
	if (ddata->end >= (int)data->set.hei)
		ddata->end = data->set.hei;
}

static void	drawv2(t_data *data, t_img img, unsigned int x, double hei)
{
	t_draw			ddata;
	int				i;
	const double	inc = 1. / hei * (double)img.w;

	init_ddata(data, &ddata, hei, inc);
	i = ddata.start;
	while (i < ddata.end)
	{
		if (img.px[(int)ddata.index * img.w]& 0XF0000000)//
			data->mlx.px[x + i *data->set.wid] = img.px[(int)ddata.index * img.w];
		++i;
		ddata.index += inc;
	}
}

//FIXME LES COOS ENTIERES SONT BAISEES, rapport avec le cos
void	drawv3(t_data *data, t_ray *ray, size_t x)
{
	t_img			img;

	/*if (ray->side == XSIDE && ray->vec.x <= 0.)
	{
		printf("how\n");
		img = data->tmp;
		img.px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img.w);
	}
	else if (ray->side == XSIDE)
	{
		printf("how\n");
		img = data->tmp;
		img.px += (size_t)((1. - (ray->pos.y - floor(ray->pos.y)))
				* (double)img.w);
	}*/

	if (ray->side == XSIDE && ray->vec.x <= 0.)
	{
		img = data->tmp;
		img.px += (size_t)((ray->pos.x - floor(ray->pos.x)) * (double)img.w);
	}
	//else if (ray->side == XSIDE)
	//{
	//	img = data->tmp;
	//	img.px += (size_t)((1. - (ray->pos.x - floor(ray->pos.x)))
	//			* (double)img.w);
	//}
	else if (ray->vec.y <= 0.)
	{
		img = data->tmp;
		//img.px += (size_t)((1. - (ray->pos.x - floor(ray->pos.x)))
		//		* (double)img.w);
		
		img.px += (size_t)((ray->pos.x - floor(ray->pos.x)) * (double)img.w);
	}
	else
	{
		img = data->tmp;
		img.px += (size_t)((ray->pos.x - floor(ray->pos.x)) * (double)img.w);
	}
	drawv2(data, img, x,( data->set.planwid / ray->len));
}
#include <math.h>
#include "data.h"
#include "render.h"
#include "map.h"
#include "mlx.h"
#include "utils.h"
#include "point.h"
#include "ray.h"

//XXX changer nom
//les coordonnees sont aramenees je crois
void	draw_sprites(t_ray *ray, t_data *data, double len, size_t x)
{
	while (ray->len < (len + 1.))
	{
		ray->side = !(ray->dist.x < ray->dist.y);
		if (ray->side == XSIDE)
		{
			ray->ipos.x += ray->istep.x;
			ray->len = ray->dist.x;
			ray->dist.x += ray->step.x;
		}
		else
		{
			ray->ipos.y += ray->istep.y;
			ray->len = ray->dist.y;
			ray->dist.y += ray->step.y;
		}
		if (ray->ipos.x < 0)
			ray->ipos.x += data->map.wid;
		else if (ray->ipos.x >= data->map.wid)
			ray->ipos.x -= data->map.wid;
		if (ray->ipos.y < 0)
			ray->ipos.y += data->map.hei;
		else if (ray->ipos.y >= data->map.hei)
			ray->ipos.y -= data->map.hei;
			//test intersection y
			//XXX < 0 tout ca tout ca
		if (data->map.map[data->map.wid * ray->ipos.y + ray->ipos.x] & GLASS)
		{
			ray->pos.x += ray->len * ray->vec.x;//non copier
			ray->pos.y += ray->len * ray->vec.y;
			t_point ogpos = ray->pos;
			
			if (ray->side == YSIDE)
			{
				ray->pos.y += .5 * (double)ray->istep.y;
				ray->pos.x += .5 * ray->vec.x / ray->vec.y * (double)ray->istep.y;//inutile ?
			}
			else if (ray->pos.y - floor(ray->pos.y) > .5)
			{

				break ;
			}
			else
			{
				ray->pos.y = .5 * (double)ray->istep.y + floor(ray->pos.y);
				ray->pos.x += (ray->pos.y - ogpos.y) * (ray->vec.x / ray->vec.y);//inutile
			}
				double increase = sqrt((ray->pos.x - ogpos.x) * (ray->pos.x - ogpos.x) +(ray->pos.y - ogpos.y) * (ray->pos.y - ogpos.y));
				ray->len = (len - increase - ray->len) * data->set.coslen[x];
			if ( (int)floor(ogpos.x + 1.e-4 * (double)ray->istep.x) == (int)floor(ray->pos.x))
			{
				//printf("%f %f\n", ray->pos.x, ray->pos.y);
				drawv3(data, ray, x);
			}
				if (x == data->set.wid / 2)
				{
			printf("%f %f\n", ray->pos.x, ray->pos.y);
				printf("%f\n", ray->pos.y - floor(ray->pos.y));
				}
			break ;//nn
		}
	}
}

//XXX change name
void	draw_glass(t_data *data, t_ray *ray, size_t x)
{
	const double	len = ray->len;

	if (ray->len > data->set.view)
		ray->len = INFINITY;
	else
		ray->len *= data->set.coslen[x];
	drawv(data, ray, x);
	ray->pos.x += 1.e-6 * (double)ray->istep.x;//FIXME still weird if angle is perfect
	ray->pos.y += 1.e-6 * (double)ray->istep.y;
	ray->vec = (t_point){-ray->vec.x, -ray->vec.y};

	ray->istep = (t_ipoint){-ray->istep.x, -ray->istep.y};
		ray->dist.x = (ray->pos.x - floor(ray->pos.x)) * ray->step.x;
		ray->dist.y = (ray->pos.y - floor(ray->pos.y)) * ray->step.y;
	if (ray->vec.x < 0.)
	{
		ray->dist.x = (ray->pos.x - floor(ray->pos.x)) * ray->step.x;
	}
	else
	{
		ray->dist.x = (1.0 - ray->pos.x + floor(ray->pos.x)) * ray->step.x;
	}
	if (ray->vec.y < 0.)
	{
		ray->dist.y = (ray->pos.y - floor(ray->pos.y)) * ray->step.y;
	}
	else
	{
		ray->dist.y = (1.0 - ray->pos.y + floor(ray->pos.y)) * ray->step.y;
	}
	ray->hit = 0;
	ray->len = 0.;
	draw_sprites(ray, data, len, x);
}
