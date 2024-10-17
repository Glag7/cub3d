/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:28:58 by glag              #+#    #+#             */
/*   Updated: 2024/10/11 02:05:11 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "set.h"

static int	ispower(unsigned int n)
{
	while (n && !(n & 1))
		n >>= 1;
	n >>= 1;
	return (!n);
}

int	load_settings(t_set *set)
{
	const int	fd = open("./.cubsettings",
			O_RDONLY);

	if (fd == -1 || read(fd, set, sizeof(*set)) != sizeof(*set)
		|| set->wid % 2 || set->wid > 10000
		|| set->hei % 2 || set->hei > 10000
		|| set->d % 2 != 1
		|| set->d + set->xoffset >= set->wid
		|| set->d + set->yoffset >= set->hei
		|| !set->texsiz || !ispower(set->texsiz)
		|| !set->skysiz || !ispower(set->skysiz)
		|| set->fov_deg < 1. || set->fov_deg > 179.)
	{
		set->invlen = NULL;
		set->coslen = NULL;
		close(fd);
		return (1);
	}
	set->invlen = NULL;
	set->coslen = NULL;
	if (fd != -1)
		close(fd);
	return (0);
}

void	free_settings(t_set *set)
{
	const int	fd = open("./.cubsettings",
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	t_set		saved_set;

	saved_set = *set;
	saved_set.wid = set->saved_w;
	saved_set.hei = set->saved_h;
	saved_set.texsiz = set->saved_texsiz;
	saved_set.skysiz = set->saved_skysiz;
	if (fd != -1)
	{
		write(fd, &saved_set, sizeof(*set));
		close(fd);
	}
	free(set->invlen);
	free(set->coslen);
}
