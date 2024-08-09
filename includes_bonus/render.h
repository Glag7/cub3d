/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:48 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/09 17:35:52 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdint.h>
# include <stddef.h>
# include "data.h"
# include "map.h"
# include "ray.h"

int		loop(void *data_);
void	draw_floor(t_data *data);
void	raycast(t_data *data);
void	drawv(t_data *data, t_ray *ray, size_t x);
void	draw_sprites(t_ray *ray, t_data *data, double len, size_t x);
void	draw_minimap(t_data *data);

#endif
