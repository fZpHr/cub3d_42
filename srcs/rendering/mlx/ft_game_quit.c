/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:10:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:10:29 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Quit the game.
 * 
 * @param cub 	The game structure
 * 
 * @return int 	Always `0`
*/
int	ft_game_quit(t_cub *cub)
{
	mlx_do_key_autorepeaton(cub->mlx);
	if (BONUS && HIDE_MOUSE)
		mlx_mouse_show(cub->mlx, cub->mlx_win);
	for (int i = 0; i < 128; i++)
	{
		for (t_ull j = 0; j < cub->textures[i].anim_no; j++)
			mlx_destroy_image(cub->mlx, cub->textures[i].no[j].img);
		free(cub->textures[i].no);
		for (t_ull j = 0; j < cub->textures[i].anim_so; j++)
			mlx_destroy_image(cub->mlx, cub->textures[i].so[j].img);
		free(cub->textures[i].so);
		for (t_ull j = 0; j < cub->textures[i].anim_we; j++)
			mlx_destroy_image(cub->mlx, cub->textures[i].we[j].img);
		free(cub->textures[i].we);
		for (t_ull j = 0; j < cub->textures[i].anim_ea; j++)
			mlx_destroy_image(cub->mlx, cub->textures[i].ea[j].img);
		free(cub->textures[i].ea);
	}
	for (int i = 0; i < cub->map_size.y; i++)
		free(cub->map_array[i]);
	free(cub->map_array);
	if (cub->frame.img)
		mlx_destroy_image(cub->mlx, cub->frame.img);
	if (cub->mlx_win)
		mlx_destroy_window(cub->mlx, cub->mlx_win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	printf("Goodbye !\n");
	exit(0);
	return (0);
}
