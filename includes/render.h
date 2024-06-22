/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:48 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/22 17:02:03 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdint.h>
# include <stddef.h>
# include "data.h"

int		draw(void *data_);
void	paint(uint32_t *px_, uint64_t color, size_t len);//TODO rm
void	drawv(t_data *data, uint32_t color, unsigned int x, unsigned int hei);
void	draw_minimap(t_data *data);
void	move(t_play *play, uint64_t keys);

#endif
