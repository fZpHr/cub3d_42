/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_keyup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:19:44 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/29 04:18:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Handle the keyup event.
 * 
 * @brief	- `WASD` or arrows: Toggle the moving variables
 * 
 * @param keycode 	The key released
 * @param cub 		The game structure
 * 
 * @return int 		Always `0`
 */
int	ft_game_keyup(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->keys.forward = FALSE;
	if (keycode == XK_s)
		cub->keys.backward = FALSE;
	if (keycode == XK_a)
		cub->keys.left = FALSE;
	if (keycode == XK_d)
		cub->keys.right = FALSE;
	if (keycode == XK_Left)
		cub->keys.rot_left = FALSE;
	if (keycode == XK_Right)
		cub->keys.rot_right = FALSE;
	return (0);
}
