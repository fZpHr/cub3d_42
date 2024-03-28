/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:53:28 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 21:02:04 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Handle left player movement.
 * 
 * @brief	1. Update X coordinate
 * @brief		- If collide 3 steps X-left, rollback.
 * 
 * @brief	2. Update Y coordinate
 * @brief		- If collide 3 steps Y-left, rollback.
 * 
 * @brief	- Updating separately X and Y coordinates makes
 * 				the player slide on the walls if he can !
 * 
 * @param cub 	The game structure
*/
void	ft_move_left(t_cub *cub)
{
	t_pos	rollback;
	float	x;
	float	y;

	rollback = cub->position;
	x = cos(cub->orientation - PI / 2) * TRANSL_SPEED;
	cub->position.x += x;
	if (ft_does_collide(cub, (t_pos){cub->position.x + x + x, cub->position.y}))
		cub->position.x = rollback.x;
	y = sin(cub->orientation - PI / 2) * TRANSL_SPEED;
	cub->position.y += y;
	if (ft_does_collide(cub, (t_pos){cub->position.x, cub->position.y + y + y}))
		cub->position.y = rollback.y;
}
