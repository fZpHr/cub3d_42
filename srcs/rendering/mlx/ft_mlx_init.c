/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:15:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Initialize the MLX (window, configs, hooks).
 * 
 * @param cub 	The game structure
 * 
 * @return int 	`0` if everything went well, `1` otherwise
 */
int	ft_mlx_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_error("MLX initialization failed"));
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, NAME);
	if (!cub->mlx_win)
		return (ft_error("Window creation failed"));
	cub->frame.img = NULL;
	cub->frame = ft_mlx_new_frame(cub, TRUE);
	if (!cub->frame.img)
		return (1);
	mlx_do_key_autorepeatoff(cub->mlx);
	if (BONUS && HIDE_MOUSE)
		mlx_mouse_hide(cub->mlx, cub->mlx_win);
	if (BONUS && HIDE_MOUSE)
		mlx_mouse_move(cub->mlx, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(cub->mlx, &ft_game_loop, cub);
	mlx_hook(cub->mlx_win, ON_DESTROY, 0L, &ft_game_quit, cub);
	mlx_hook(cub->mlx_win, ON_KEYDOWN, MASK_KEY_PRESS, &ft_game_keydown, cub);
	mlx_hook(cub->mlx_win, ON_KEYUP, MASK_KEY_RELEASE, &ft_game_keyup, cub);
	mlx_hook(cub->mlx_win, ON_MOUSEMOVE, MASK_MOUSE_MOVE, &ft_game_mouse, cub);
	return (0);
}
