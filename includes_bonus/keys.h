/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:59:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/09/05 18:51:51 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/* ----- INCLUDES ----- */

# include "data.h"

/* ----- MACROS ----- */

# define KEY_W 1
# define KEY_S 2
# define KEY_A 4
# define KEY_D 8
# define KEY_LEFT 16
# define KEY_RIGHT 32
# define KEY_UP 64
# define KEY_DOWN 128
# define KEY_SHIFT 256
# define KEY_E 512
# define KEY_LM 1024
# define KEY_SPACE 2048
# define KEY_CTRL 4096
# define KEY_TAB 8192
# define KEY_0 16384
# define KEY_1 32769
# define KEY_2 65536
# define KEY_3 131072
# define KEY_4 262144
# define KEY_5 524288
# define KEY_6 1048576
# define KEY_7 2097152
# define KEY_8 4194304
# define KEY_9 8388608
# define KEY_MINUS 16777216
# define KEY_DOT 33554432
# define KEY_BACK 67108864

# define KEYS_DIGITS 134201344

/* ----- PROTOTYPES ----- */

int	key_hook_keypad(int key, t_data *data);
int	unkey_hook_keypad(int key, t_data *data);

#endif
