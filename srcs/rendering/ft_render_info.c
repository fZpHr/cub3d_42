/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

#define INFO_W 155
#define INFO_H 320
#define PADDING 10

static void	ft_put_keys(t_cub *cub);
static void	ft_put_str(t_cub *cub, t_ipos pos, char *str);
static void	ft_put_lli(t_cub *cub, t_ivec3 info, long long n);
static void	ft_put_float(t_cub *cub, t_ivec3 info, float n);

/**
 * @brief The information about the game state, player position, speed, etc.
 * 
 * @brief	- Player X
 * @brief	- Player Y
 * @brief	- Player Angle (rad)
 * @brief	- Player Angle (deg)
 * 
 * @brief	---
 * 
 * @brief	- Walk Speed
 * @brief	- Rotation Speed
 * @brief	- Rotation Speed (Mouse)
 * 
 * @brief	---
 * 
 * @brief	- Rays
 * @brief	- FOV (deg)
 * 
 * @brief	---
 * 
 * @brief	- `W` `A` `S` `D` (current pressed keys)
 * 
 * @param cub 	The game structure
 */
void	ft_render_info(t_cub *cub)
{
	ft_put_rect(cub->frame, (t_ipos){WIDTH - INFO_W - PADDING,
		HEIGHT - INFO_H - PADDING}, (t_ipos){INFO_W, INFO_H}, 0x000000);
	ft_put_str(cub, (t_ipos){0, 0}, "Player X:");
	ft_put_float(cub, (t_ivec3){55, 15, 13}, cub->position.x);
	ft_put_str(cub, (t_ipos){0, 30}, "Player Y:");
	ft_put_float(cub, (t_ivec3){55, 45, 13}, cub->position.y);
	ft_put_str(cub, (t_ipos){0, 60}, "Player Angle (rad):");
	ft_put_float(cub, (t_ivec3){55, 75, 13}, cub->orientation);
	ft_put_str(cub, (t_ipos){0, 90}, "Player Angle (deg):");
	ft_put_float(cub, (t_ivec3){55, 105, 13}, cub->orientation * 180 / PI);
	ft_put_str(cub, (t_ipos){0, 130}, "Walk Speed:");
	ft_put_float(cub, (t_ivec3){55, 145, 13}, WALK_SPEED);
	ft_put_str(cub, (t_ipos){0, 160}, "Rotation Speed:");
	ft_put_float(cub, (t_ivec3){55, 175, 13}, ROT_SPEED);
	ft_put_str(cub, (t_ipos){0, 190}, "Rotation Speed (Mouse):");
	ft_put_float(cub, (t_ivec3){55, 205, 13}, ROT_SPEED_MOUSE);
	ft_put_str(cub, (t_ipos){0, 220}, "Rays:");
	ft_put_lli(cub, (t_ivec3){55, 235, 13}, RAYS);
	ft_put_str(cub, (t_ipos){0, 250}, "FOV (deg):");
	ft_put_float(cub, (t_ivec3){55, 265, 13}, FOV * 180 / PI);
	ft_put_keys(cub);
}

static void	ft_put_keys(t_cub *cub)
{
	ft_put_str(cub, (t_ipos){26, 280}, "<  W  A  S  D  >");
	ft_put_lli(cub, (t_ivec3){26, 295, 1}, cub->keys.rot_left);
	ft_put_lli(cub, (t_ivec3){44, 295, 1}, cub->keys.forward);
	ft_put_lli(cub, (t_ivec3){62, 295, 1}, cub->keys.left);
	ft_put_lli(cub, (t_ivec3){80, 295, 1}, cub->keys.backward);
	ft_put_lli(cub, (t_ivec3){98, 295, 1}, cub->keys.right);
	ft_put_lli(cub, (t_ivec3){116, 295, 1}, cub->keys.rot_right);
}

static void	ft_put_str(t_cub *cub, t_ipos pos, char *str)
{
	mlx_string_put(cub->mlx, cub->mlx_win, WIDTH - INFO_W + pos.x,
		HEIGHT - INFO_H + PADDING + pos.y, 0xFFFFFF, str);
}

static void	ft_put_lli(t_cub *cub, t_ivec3 info, long long n)
{
	char	*str;

	str = ft_lli_to_str(n, info.z);
	ft_put_str(cub, (t_ipos){info.x, info.y}, str);
	free(str);
}

static void	ft_put_float(t_cub *cub, t_ivec3 info, float n)
{
	char	*str;

	str = ft_ftoa(n, info.z);
	ft_put_str(cub, (t_ipos){info.x, info.y}, str);
	free(str);
}
