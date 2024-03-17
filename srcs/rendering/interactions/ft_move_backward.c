/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_backward.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:12:49 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:13:01 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Handle backward player movement.
 * 
 * @brief	1. Update X coordinate
 * @brief		- If collide 3 steps X-backward, rollback.
 * 
 * @brief	2. Update Y coordinate
 * @brief		- If collide 3 steps Y-backward, rollback.
 * 
 * @brief	- Updating separately X and Y coordinates makes
 * 				the player slide on the walls if he can !
 * 
 * @param cub 	The game structure
*/
void	ft_move_backward(t_cub *cub)
{
	t_pos	rollback;
	float	x;
	float	y;

	rollback = cub->position;
	x = cos(cub->orientation) * WALK_SPEED;
	cub->position.x -= x;
	if (ft_does_collide(cub, (t_pos){cub->position.x - x - x, cub->position.y}))
		cub->position.x = rollback.x;
	y = sin(cub->orientation) * WALK_SPEED;
	cub->position.y -= y;
	if (ft_does_collide(cub, (t_pos){cub->position.x, cub->position.y - y - y}))
		cub->position.y = rollback.y;
}
