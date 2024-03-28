/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_keydown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:20:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 18:21:05 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Handle the keydown event.
 * 
 * @brief	- `Escape`: Quit the game
 * 
 * @brief	- `WASD` or arrows: Toggle the moving variables
 * 
 * @param keycode 	The key pressed
 * @param cub 		The game structure
 * 
 * @return int 		Always `0`
*/
int	ft_game_keydown(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		ft_game_quit(cub, 0);
	if (keycode == XK_i)
		cub->info = !cub->info;
	if (BONUS && (keycode == XK_m
			|| keycode == XK_Shift_L || keycode == XK_Tab))
		cub->minimap = !cub->minimap;
	if (BONUS && (keycode == XK_e
			|| keycode == XK_Shift_R || keycode == XK_space))
		ft_handle_action(cub);
	if (keycode == XK_w || keycode == XK_Up)
		cub->keys.forward = TRUE;
	if (keycode == XK_s || keycode == XK_Down)
		cub->keys.backward = TRUE;
	if (keycode == XK_a || keycode == XK_Left)
		cub->keys.rot_left = TRUE;
	if (keycode == XK_d || keycode == XK_Right)
		cub->keys.rot_right = TRUE;
	return (0);
}
