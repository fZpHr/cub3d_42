/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_forward.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:12:20 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Handle forward player movement.
 * 
 * @brief	1. Update X coordinate
 * @brief		- If collide 3 steps X-forward, rollback.
 * 
 * @brief	2. Update Y coordinate
 * @brief		- If collide 3 steps Y-forward, rollback.
 * 
 * @brief	- Updating separately X and Y coordinates makes
 * 				the player slide on the walls if he can !
 * 
 * @param cub 	The game structure
 */
void	ft_move_forward(t_cub *cub)
{
	t_pos	rollback;
	float	x;
	float	y;

	rollback = cub->position;
	x = cos(cub->orientation) * WALK_SPEED;
	cub->position.x += x;
	if (ft_does_collide(cub, (t_pos){cub->position.x + x + x, cub->position.y}))
		cub->position.x = rollback.x;
	y = sin(cub->orientation) * WALK_SPEED;
	cub->position.y += y;
	if (ft_does_collide(cub, (t_pos){cub->position.x, cub->position.y + y + y}))
		cub->position.y = rollback.y;
}
