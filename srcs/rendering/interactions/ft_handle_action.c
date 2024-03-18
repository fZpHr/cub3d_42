/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:21:11 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/18 16:53:30 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Handle the action of the player.
 * 			(When he tries to open or close a door)
 * 
 * @brief	- If the foreward tile is a closed door: open it !
 * 
 * @brief	- If the foreward tile is an opened door
 * 				AND the player is not inside the door: close it !
 * 
 * @param cub 	The game structure
*/
void	ft_handle_action(t_cub *cub)
{
	t_pos	pos;

	pos = (t_pos){cub->position.x + cos(cub->orientation),
		cub->position.y + sin(cub->orientation)};
	if (pos.x >= 0 && pos.x < cub->map_size.x
		&& pos.y >= 0 && pos.y < cub->map_size.y)
	{
		if (cub->map_array[(int) pos.y][(int) pos.x].type == 'X')
		{
			cub->map_array[(int) pos.y][(int) pos.x].type = '-';
			cub->map_array[(int) pos.y][(int) pos.x].is_solid = TRUE;
			cub->textures['-'].empty = FALSE;
			cub->textures['-'].no_anim = TRUE;
			cub->textures['-'].so_anim = TRUE;
			cub->textures['-'].we_anim = TRUE;
			cub->textures['-'].ea_anim = TRUE;
			cub->textures['-'].no_anim_num = 0;
			cub->textures['-'].so_anim_num = 0;
			cub->textures['-'].we_anim_num = 0;
			cub->textures['-'].ea_anim_num = 0;
			cub->textures['-'].anim_counter = 0;
		}
		else if (cub->map_array[(int) pos.y][(int) pos.x].type == 'O'
			&& cub->map_array[(int) cub->position.y] \
				[(int) cub->position.x].type != 'O')
		{
			cub->map_array[(int) pos.y][(int) pos.x].type = 'X';
			cub->map_array[(int) pos.y][(int) pos.x].is_solid = TRUE;
		}
	}
}
