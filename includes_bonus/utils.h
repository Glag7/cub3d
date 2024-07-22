/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:57:19 by glaguyon          #+#    #+#             */
/*   Updated: 2024/06/28 18:41:07 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

void	ft_perror(const char *s);
void	*ft_memcpy(void *restrict dest, const void *restrict src, size_t n);
void	ft_bzero(void *restrict s, size_t n);

#endif
