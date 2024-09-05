/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:32:51 by glaguyon          #+#    #+#             */
/*   Updated: 2024/08/08 17:19:52 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

int	key_hook(int key, void *data_);
int	unkey_hook(int key, void *data_);
int	win_hook(void *data_);
int	in_hook(void *data_);
int	out_hook(void *data_);
int	manage_mouse_hook(int button, int x, int y, void *data_ptr);

#endif
