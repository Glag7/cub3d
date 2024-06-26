/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/26 17:32:36 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "data.h"
#include "render.h"
#include "mlx.h"
#include "utils.h"

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ipoint
{
	unsigned int	x;
	unsigned int	y;
}	t_ipoint;

#define MAXLEN 20.
#define XSIDE 0
#define YSIDE 1

static void	trace_ray(t_data *data, double a, size_t x)
{
	t_point	pos;//pos du rayon au debut
	t_point	vec;//direction
	t_point	step;//longueur de la diagonale quand on avance sur x ou y
	t_point	dist;//longueur du rayon en x et y
	t_ipoint	ipos;//pos dans la map
	t_ipoint	istep;//ou aller dans la map
	int		hit;//hit
	int		side;//EW/NS
	double	len;//len

	pos = (t_point){data->play.x, data->play.y};
	ipos = (t_ipoint){pos.x, pos.y};
	vec = (t_point){cos(a), -sin(a)};
	step = (t_point){sqrt(1. + (vec.y * vec.y) / (vec.x * vec.x)), sqrt(1. + (vec.x * vec.x) / (vec.y * vec.y))};

	if (vec.x < 0.)
	{
		istep.x = -1;
		dist.x = (pos.x - floor(pos.x)) * step.x;//quelle longueur le rayon aura au premier x
	}
	else
	{
		istep.x = 1;
		dist.x = (1.0 - pos.x + floor(pos.x)) * step.x;
	}
	if (vec.y < 0.)
	{
		istep.y = -1;
		dist.y = (pos.y - floor(pos.y)) * step.y;
	}
	else
	{
		istep.y = 1;
		dist.y = (1.0 - pos.y + floor(pos.y)) * step.y;
	}
	hit = 0;
	len = 0.;
	while (!hit && len < data->set.view)
	{
		if (dist.x < dist.y)
		{
			ipos.x += istep.x;
			len = dist.x;
			dist.x += step.x;
			side = XSIDE;
		}
		else
		{
			ipos.y += istep.y;
			len = dist.y;
			dist.y += step.y;
			side = YSIDE;
		}
		if (data->map.map[data->map.wid * ipos.y + ipos.x])
			hit = 1 ;

	}
	if (!hit)	
		len = INFINITY;	

	//
	int color;
	if (side == XSIDE && vec.x > 0)
		color = 0x000000FF;
	else if (side == XSIDE)
		color = 0x0000FF00;
	else if (vec.y > 0)
		color = 0x00FF0000;
	else
		color = 0x00FFFF00;
	drawv(data, color, x, (unsigned int)((double)data->set.hei / len));
}

static void	raycast(t_data *data)
{
	double	astep;
	double	a;
	size_t	i;

	i = data->set.offthread;
	astep = data->set.fov * (double)data->set.nthread / (double)data->set.wid;
	a = data->play.a + data->set.fov * 0.5;
	while (i < data->set.wid)
	{
		trace_ray(data, a, i);
		i += data->set.nthread;
		a -= astep;
	}
}


/*
void	raycast(t_data *data)
{
	double dirX = cos(data->play.a), dirY = sin(data->play.a);
	double planeX = 0, planeY = 0.66;
	double posX = data->play.x;
	double posY = data->play.y;
	int w = DEF_WID;
	int h = DEF_HEI;
	for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)posX;
      int mapY = (int)posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      //these are derived as:
      //deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      //deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      //unlike (dirX, dirY) is not 1, however this does not matter, only the
      //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      //stepping further below works. So the values can be computed as below.
      // Division through zero is prevented, even though technically that's not
      // needed in C++ with IEEE 754 floating point values.
      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(data->map.map[mapX + data->map.wid * mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h) drawEnd = h - 1;
      int color;
        if (side == 0 && stepX > 0)
                color = 0x000000FF;
        else if (side == 0)
                color = 0x0000FF00;
        else if (stepY > 0)
                color = 0x00FF0000;
        else
                color = 0x00FFFF00;
	while (drawStart < drawEnd)
	{
		data->mlx.px[x + drawStart * w] = color;
		drawStart++;
	}
    }
}
*/


int	draw(void *data_)
{
	t_data	*data;
	size_t	half;

	data = data_;
	move(&data->play, data->keys);
	half = (data->set.wid * data->set.hei) / 2;
	raycast(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
