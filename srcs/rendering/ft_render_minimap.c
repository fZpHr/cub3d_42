/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:23:03 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 11:23:27 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Render the minimap.
 * 
 * @brief	1. Draw the map
 * @brief		- For each tile of the map:
 * @brief			- Draw a gray rectangle (to make the border)
 * @brief			- Draw a smaller rectangle, representing the content
 * 
 * @brief	2. Draw the player
 * @brief		- Draw the rays (1 every 20 rays)
 * @brief		- Draw a ray representing the player's orientation
 * @brief		- Draw a rectangle for the player
 * 
 * @param cub 		The game structure
 * @param castings 	The result of the ray casting
*/
void	ft_render_minimap(t_cub *cub, t_casting castings[RAYS])
{
	int		TILE_SIZE = 15;
	int		PLAYER_SIZE = 8;
	int		i;
	int		j;

	i = 0;
	while (i < cub->map_size.y)
	{
		j = 0;
		while (j < cub->map_size.x)
		{
			t_texture	texture = cub->textures[(int) cub->map_array[i][j].type];
			if (texture.map_color)
			{
				ft_put_rect(cub->frame,
					(t_ipos){j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE},
					(t_ipos){TILE_SIZE, TILE_SIZE}, cub->border_c ? cub->border_c : texture.map_color);
				if (cub->border_c)
					ft_put_rect(cub->frame,
						(t_ipos){j * TILE_SIZE + TILE_SIZE + 1, i * TILE_SIZE + TILE_SIZE + 1},
						(t_ipos){TILE_SIZE - 2, TILE_SIZE - 2}, texture.map_color);
			}
			j++;
		}
		i++;
	}

	for (int rc = 0; rc < RAYS; rc += 20)
	{
		t_casting c = castings[rc];
		if (c.distance != -1)
			ft_put_line(cub->frame,
				(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE, cub->position.y * TILE_SIZE + TILE_SIZE},
				(t_ipos){c.x * TILE_SIZE + TILE_SIZE, c.y * TILE_SIZE + TILE_SIZE},
				0x0000FFFF);
	}
	
	t_casting c = ft_cast_ray(cub, cub->orientation);
	if (c.distance != -1)
		ft_put_line(cub->frame,
			(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE, cub->position.y * TILE_SIZE + TILE_SIZE},
			(t_ipos){c.x * TILE_SIZE + TILE_SIZE, c.y * TILE_SIZE + TILE_SIZE},
			0x00FF00FF);

	ft_put_line(cub->frame,
		(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE, cub->position.y * TILE_SIZE + TILE_SIZE},
		(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE + cos(cub->orientation) * TILE_SIZE,
			cub->position.y * TILE_SIZE + TILE_SIZE + sin(cub->orientation) * TILE_SIZE},
		0x00FF0000);
	ft_put_rect(cub->frame,
		(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE - PLAYER_SIZE / 2,
			cub->position.y * TILE_SIZE + TILE_SIZE - PLAYER_SIZE / 2},
		(t_ipos){PLAYER_SIZE, PLAYER_SIZE}, 0x0000FF00);
}
