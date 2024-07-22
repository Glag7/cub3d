/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:48 by glaguyon          #+#    #+#             */
/*   Updated: 2024/07/17 13:15:44 by glag             ###   ########.fr       */
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
void	raycast(t_data *data);
void	drawv(t_data *data, t_ray *ray, size_t x);
void	draw_minimap(t_data *data);
void	move(t_data *data, double delta, uint64_t keys);
void	move_angle(t_data *data, double delta);

#endif
