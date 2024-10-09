/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:32:51 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/04 18:34:22 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

int	key_hook(int key, void *data_);
int	unkey_hook(int key, void *data_);
int	mouse_hook(int click, int x, int y, void *data_);
int	win_hook(void *data_);
int	in_hook(void *data_);
int	out_hook(void *data_);

#endif
