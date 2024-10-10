/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:28:58 by glag              #+#    #+#             */
/*   Updated: 2024/10/10 20:39:00 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "set.h"

void	export_settings(t_set *set)
{
	const int	fd = open("./.cubsettings", O_CREAT | O_TRUNC | O_WRONLY);

	if (fd == -1)
		return ;
	write(fd, set, sizeof(*set));
	close(fd);
}
