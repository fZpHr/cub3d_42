/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_chunk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:24:59 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/18 13:49:28 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/**
 * @brief Put a chunk of the texture on the frame at the given position.
 * 
 * @brief	1. Get the texture and the texture_x position
 * @brief		- Depending on the facing of the wall, the texture is different
 * @brief		- `NORTH`: `tx = tw - 1 - (x * tw) % tw`
 * @brief		- `SOUTH`: `tx = (x * tw) % tw`
 * @brief		- `WEST`: `tx = (y * tw) % tw`
 * @brief		- `EAST`: `tx = tw - 1 - (y * tw) % tw`
 * 
 * @brief	2. Let's draw ! For each vertical pixel (from `0` to `size.y`):
 * @brief		- `ty = (y * th) / size.y`
 * @brief		- The color is taken from the texture using addresses
 * @brief		- To center vertically, we offset `y` by `(HEIGHT - size.y) / 2`
 * @brief		- Update the pixels of the line `y` (from `x` to `x + size.x`)
 * 
 * @param cub 		The game structure
 * @param x 		The x screen's pos of the left side of the chunk (in px)
 * @param size 		The size of the chunk (width, height, in px)
 * @param casting 	The result of the ray casting
*/
void	ft_render_chunk(t_cub *cub, int x, t_ipos size, t_casting casting)
{
	t_texture	texture_t;
	t_frame		texture;
	int			texture_x;
	texture.img = NULL;
	if (casting.facing == NORTH)
	{
		texture_t = cub->textures[(int) cub->map_array[(int) casting.y][(int) casting.x].type];
		if (texture_t.no)
			texture = texture_t.no[(cub->frames / texture_t.anim_delay) % texture_t.anim_no];
		texture_x = texture.width - 1 - (int) (casting.x * texture.width) % texture.width;
	}
	else if (casting.facing == SOUTH)
	{
		texture_t = cub->textures[(int) cub->map_array[(int) casting.y - 1][(int) casting.x].type];
		if (texture_t.so)
			texture = texture_t.so[(cub->frames / texture_t.anim_delay) % texture_t.anim_so];
		texture_x = (int) (casting.x * texture.width) % texture.width;
		
	}
	else if (casting.facing == WEST)
	{
		texture_t = cub->textures[(int) cub->map_array[(int) casting.y][(int) casting.x].type];
		if (texture_t.we)
			texture = texture_t.we[(cub->frames / texture_t.anim_delay) % texture_t.anim_we];
		texture_x = (int) (casting.y * texture.width) % texture.width;
	}
	else if (casting.facing == EAST)
	{
		texture_t = cub->textures[(int) cub->map_array[(int) casting.y][(int) casting.x - 1].type];
		if (texture_t.ea)
			texture = texture_t.ea[(cub->frames / texture_t.anim_delay) % texture_t.anim_ea];
		texture_x = texture.width - 1 - (int) (casting.y * texture.width) % texture.width;
	}
	if (!texture.img)
		return ;

	int	texture_y, color;
	int win_y_offset = (HEIGHT - size.y) / 2;
	for (int win_y = 0; win_y < size.y && win_y + win_y_offset < HEIGHT; win_y++)
	{
		if (win_y + win_y_offset < 0)
			continue;
		for (int win_x = 0; win_x < size.x && win_x + x < WIDTH; win_x++)
		{
			texture_y = texture.height * (float) win_y / size.y;
			color = *(int *)(char *)(texture.addr
				+ (texture_y * texture.line_size + texture_x * 4));
			if (color != 0 && win_x + x >= 0 && win_y + win_y_offset < HEIGHT)
				ft_put_pixel(cub->frame, win_x + x, win_y + win_y_offset, color);
		}
	}
}
