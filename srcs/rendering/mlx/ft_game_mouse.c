/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:21:55 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:22:06 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Handle the mouse event.
*/
int	ft_game_mouse(int x, int y, t_cub *cub)
{
	(void)y;
	if (!BONUS || !HIDE_MOUSE)
		return (0);
	mlx_mouse_move(cub->mlx, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	x -= WIDTH / 2;
	if (x >= -100 && x <= 100)
		cub->orientation += x * ROT_SPEED_MOUSE;
	return (0);
}
