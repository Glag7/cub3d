/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_flat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:27:54 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/26 16:51:24 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include "data.h"
#include "map.h"
#include "ray.h"
#include "render.h"

static inline void __attribute__((always_inline))
	init_ddata(t_data *data, t_draw *ddata, double hei, double inc)
{
	const double	zoffset = data->set.planwid * data->play.az / M_PI * 4.
		+ hei * data->play.z;

	ddata->start = ((double)data->set.hei - hei) * .5 + zoffset + 2.5;
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
	const double	inc = (1.) / hei * (double)img.w;

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
void	drawv4(t_data *data, t_ray *ray, size_t x)
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
		img.px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img.w);
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
		
		img.px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img.w);
	}
	else
	{
		img = data->tmp;
		img.px += (size_t)((ray->pos.y - floor(ray->pos.y)) * (double)img.w);
	}
	drawv2(data, img, x,( data->set.planwid / ray->len));
}

static void	find_sprite(t_ray *ray, t_data *data, double len, size_t x)
{
		t_ray ray3 = *ray;
		t_ray *ray2 = &ray3;
		ray2->pos.x += ray2->len * ray2->vec.x;//non copier
		ray2->pos.y += ray2->len * ray2->vec.y;
		t_point ogpos = ray2->pos;
	
		if (data->map.map[data->map.wid * ray->ipos.y + ray->ipos.x] & YSIDE)
		{
			if (ray2->side == YSIDE)
			{
				ray2->pos.x = .5 + floor(ray2->pos.x);
				ray2->pos.y += (ray2->pos.x - ogpos.x) * (ray2->vec.y / ray2->vec.x);//inutile
				//ray2->pos.x += .5 * (double)ray2->istep.x;
				//ray2->pos.y += .5 * ray2->vec.y / ray2->vec.x * (double)ray2->istep.x;//inutile ?
			}
		//	else if (ray2->pos.y - floor(ray2->pos.y) > .5)
		//	{
		//
		//		break ;
		//	}
			else
			{
				ray2->pos.x += .5 * (double)ray2->istep.x;
				ray2->pos.y += .5 * ray2->vec.y / ray2->vec.x * (double)ray2->istep.x;//inutile ?
				//ray2->pos.y = .5 + floor(ray2->pos.y);
				//ray2->pos.x += (ray2->pos.y - ogpos.y) * (ray2->vec.x / ray2->vec.y);//inutile
			}
				double increase = sqrt((ray2->pos.x - ogpos.x) * (ray2->pos.x - ogpos.x) +(ray2->pos.y - ogpos.y) * (ray2->pos.y - ogpos.y));
				ray2->len = (len - increase - ray2->len) * data->set.coslen[x];
			if ( (int)floor(ogpos.y + 1.e-6 * (double)ray2->istep.y) == (int)floor(ray2->pos.y))
			{
				//printf("%f %f\n", ray2->pos.x, ray2->pos.y);
				drawv4(data, ray2, x);
			}
		}
		else
		{
			if (ray2->side == YSIDE)
			{
				ray2->pos.y += .5 * (double)ray2->istep.y;
				ray2->pos.x += .5 * ray2->vec.x / ray2->vec.y * (double)ray2->istep.y;//inutile ?
			}
		//	else if (ray2->pos.y - floor(ray2->pos.y) > .5)
		//	{
		//
		//		break ;
		//	}
			else
			{
				ray2->pos.y = .5 + floor(ray2->pos.y);
				ray2->pos.x += (ray2->pos.y - ogpos.y) * (ray2->vec.x / ray2->vec.y);//inutile
			}
				double increase = sqrt((ray2->pos.x - ogpos.x) * (ray2->pos.x - ogpos.x) +(ray2->pos.y - ogpos.y) * (ray2->pos.y - ogpos.y));
				ray2->len = (len - increase - ray2->len) * data->set.coslen[x];
			if ( (int)floor(ogpos.x + 1.e-6 * (double)ray2->istep.x) == (int)floor(ray2->pos.x))
			{
				//printf("%f %f\n", ray2->pos.x, ray2->pos.y);
				drawv3(data, ray2, x);
			}
		}
}

static inline __attribute__((always_inline)) void
	update_ray(t_ray *ray)
{
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
}

static void	draw_sprites(t_ray *ray, t_data *data, double len, size_t x)
{
	while (ray->len < (len + 1.))
	{
		ray->side = !(ray->dist.x < ray->dist.y) * YSIDE;
		update_ray(ray);
		if (ray->ipos.x < 0)
			ray->ipos.x += data->map.wid;
		else if (ray->ipos.x >= data->map.wid)
			ray->ipos.x -= data->map.wid;
		if (ray->ipos.y < 0)
			ray->ipos.y += data->map.hei;
		else if (ray->ipos.y >= data->map.hei)
			ray->ipos.y -= data->map.hei;
		if (data->map.map[data->map.wid * ray->ipos.y + ray->ipos.x] & SPEC)
			find_sprite(ray, data, len, x);
	}
}

void	draw_flat(t_data *data, t_ray *ray, size_t x)
{
	const double	len = ray->len;

	if (ray->len > data->set.view)
		ray->len = INFINITY;
	else
		ray->len *= data->set.coslen[x];
	drawv(data, ray, x);
	ray->pos.x += 1.e-6 * (double)ray->istep.x;
	ray->pos.y += 1.e-6 * (double)ray->istep.y;
	ray->vec = (t_point){-ray->vec.x, -ray->vec.y};
	ray->istep = (t_ipoint){-ray->istep.x, -ray->istep.y};
	ray->dist.x = (ray->pos.x - floor(ray->pos.x)) * ray->step.x;
	ray->dist.y = (ray->pos.y - floor(ray->pos.y)) * ray->step.y;
	if (ray->vec.x < 0.)
		ray->dist.x = (ray->pos.x - floor(ray->pos.x)) * ray->step.x;
	else
		ray->dist.x = (1.0 - ray->pos.x + floor(ray->pos.x)) * ray->step.x;
	if (ray->vec.y < 0.)
		ray->dist.y = (ray->pos.y - floor(ray->pos.y)) * ray->step.y;
	else
		ray->dist.y = (1.0 - ray->pos.y + floor(ray->pos.y)) * ray->step.y;
	ray->hit = 0;
	ray->len = 0.;
	draw_sprites(ray, data, len, x);
}
