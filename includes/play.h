/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:24:33 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/23 15:38:49 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAY_H
# define PLAY_H

typedef struct s_play
{
	double	x;
	double	y;
	double	a;
	double	cosa;
	double	sina;
	double	speed;
}	t_play;

#endif
