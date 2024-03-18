/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:23:03 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/18 18:25:27 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

#define TILE	15
#define PLAYER	8

static void	ft_render_map(t_cub *cub);
static void	ft_render_rays(t_cub *cub, t_casting castings[RAYS]);
static void	ft_render_player(t_cub *cub);

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
	ft_render_map(cub);
	ft_render_rays(cub, castings);
	ft_render_player(cub);
}

static void	ft_render_map(t_cub *cub)
{
	t_ipos		p;
	int			c;
	t_texture	texture;

	p.y = -1;
	while (++p.y < cub->map_size.y)
	{
		p.x = -1;
		while (++p.x < cub->map_size.x)
		{
			texture = cub->textures[(int) cub->map_array[p.y][p.x].type];
			if (texture.map_color)
			{
				c = texture.map_color;
				if (cub->border_c)
					c = cub->border_c;
				ft_put_rect(cub->frame, (t_ipos){p.x * TILE + TILE,
					p.y * TILE + TILE}, (t_ipos){TILE, TILE}, c);
				if (cub->border_c)
					ft_put_rect(cub->frame, (t_ipos){p.x * TILE + TILE + 1,
						p.y * TILE + TILE + 1}, (t_ipos){TILE - 2, TILE - 2},
						texture.map_color);
			}
		}
	}
}

static void	ft_render_rays(t_cub *cub, t_casting castings[RAYS])
{
	int			rc;
	t_casting	c;

	rc = 0;
	while (rc < RAYS)
	{
		c = castings[rc];
		if (c.distance != -1)
			ft_put_line(cub->frame, (t_ipos){cub->position.x * TILE + TILE,
				cub->position.y * TILE + TILE},
				(t_ipos){c.x * TILE + TILE, c.y * TILE + TILE}, 0x0000FFFF);
		rc += 20;
	}
	c = ft_cast_ray(cub, cub->orientation);
	if (c.distance != -1)
		ft_put_line(cub->frame, (t_ipos){cub->position.x * TILE + TILE,
			cub->position.y * TILE + TILE},
			(t_ipos){c.x * TILE + TILE, c.y * TILE + TILE}, 0x00FF00FF);
}

static void	ft_render_player(t_cub *cub)
{
	ft_put_line(cub->frame,
		(t_ipos){cub->position.x * TILE + TILE, cub->position.y * TILE + TILE},
		(t_ipos){cub->position.x * TILE + TILE + cos(cub->orientation) * TILE,
		cub->position.y * TILE + TILE + sin(cub->orientation) * TILE},
		0x00FF0000);
	ft_put_rect(cub->frame,
		(t_ipos){cub->position.x * TILE + TILE - PLAYER / 2,
		cub->position.y * TILE + TILE - PLAYER / 2},
		(t_ipos){PLAYER, PLAYER}, 0x0000FF00);
}
