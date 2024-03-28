/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:10:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	ft_destroy_imgs(t_cub *cub);
static void	ft_destroy_img(void *mlx_ptr, void *img_ptr);

/**
 * @brief Destroy, free, and quit the game with `exit(0)`.
 * 
 * @param cub 	The game structure
 * @param code 	The exit code
 * 
 * @return int 	Always `0`
 */
int	ft_game_quit(t_cub *cub, int code)
{
	int	i;

	mlx_do_key_autorepeaton(cub->mlx);
	if (BONUS && HIDE_MOUSE)
		mlx_mouse_show(cub->mlx, cub->mlx_win);
	ft_destroy_imgs(cub);
	i = 0;
	while (i < cub->map_size.y)
		free(cub->map_array[i++]);
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
	if (code == 0)
		write(1, "Bye !\n", 6);
	exit(code);
	return (0);
}

static void	ft_destroy_imgs(t_cub *cub)
{
	int		i;
	t_ull	j;

	i = 0;
	while (i < 128)
	{
		j = -1;
		while (++j < cub->textures[i].no_anim_count)
			ft_destroy_img(cub->mlx, cub->textures[i].no[j].img);
		free(cub->textures[i].no);
		j = -1;
		while (++j < cub->textures[i].so_anim_count)
			ft_destroy_img(cub->mlx, cub->textures[i].so[j].img);
		free(cub->textures[i].so);
		j = -1;
		while (++j < cub->textures[i].we_anim_count)
			ft_destroy_img(cub->mlx, cub->textures[i].we[j].img);
		free(cub->textures[i].we);
		j = -1;
		while (++j < cub->textures[i].ea_anim_count)
			ft_destroy_img(cub->mlx, cub->textures[i].ea[j].img);
		free(cub->textures[i].ea);
		i++;
	}
}

static void	ft_destroy_img(void *mlx_ptr, void *img_ptr)
{
	if (mlx_ptr && img_ptr)
		mlx_destroy_image(mlx_ptr, img_ptr);
}
