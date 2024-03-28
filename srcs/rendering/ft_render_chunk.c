/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_chunk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:24:59 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	ft_get_texture_no_so(t_cub *cub, t_casting casting,
				t_frame *texture, int *texture_x);
static void	ft_get_texture_we_ea(t_cub *cub, t_casting casting,
				t_frame *texture, int *texture_x);
static void	ft_draw(t_cub *cub, int x, t_ivec3 info, t_frame texture);

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
	t_frame		texture;
	int			texture_x;

	texture.img = NULL;
	ft_get_texture_no_so(cub, casting, &texture, &texture_x);
	ft_get_texture_we_ea(cub, casting, &texture, &texture_x);
	if (!texture.img)
		return ;
	ft_draw(cub, x, (t_ivec3){size.x, size.y, texture_x}, texture);
}

static void	ft_get_texture_no_so(t_cub *cub, t_casting casting,
	t_frame *texture, int *texture_x)
{
	t_texture	texture_t;

	if (casting.facing == NORTH)
	{
		texture_t = cub->textures[(int) cub->map_array[(int) casting.y] \
				[(int) casting.x].type];
		if (texture_t.no[texture_t.no_anim_num].img)
			*texture = texture_t.no[texture_t.no_anim_num];
		*texture_x = texture->width - 1
			- (int)(casting.x * texture->width) % texture->width;
	}
	else if (casting.facing == SOUTH)
	{
		texture_t = cub->textures[(int) cub->map_array[(int) casting.y - 1] \
				[(int) casting.x].type];
		if (texture_t.so[texture_t.no_anim_num].img)
			*texture = texture_t.so[texture_t.so_anim_num];
		*texture_x = (int)(casting.x * texture->width) % texture->width;
	}
}

static void	ft_get_texture_we_ea(t_cub *cub, t_casting casting,
	t_frame *texture, int *texture_x)
{
	t_texture	texture_t;

	if (casting.facing == WEST)
	{
		texture_t = cub->textures[(int) cub->map_array[(int) casting.y] \
				[(int) casting.x].type];
		if (texture_t.we[texture_t.no_anim_num].img)
			*texture = texture_t.we[texture_t.we_anim_num];
		*texture_x = (int)(casting.y * texture->width) % texture->width;
	}
	else if (casting.facing == EAST)
	{
		texture_t = cub->textures[(int) cub->map_array[(int) casting.y] \
				[(int) casting.x - 1].type];
		if (texture_t.ea[texture_t.no_anim_num].img)
			*texture = texture_t.ea[texture_t.ea_anim_num];
		*texture_x = texture->width - 1
			- (int)(casting.y * texture->width) % texture->width;
	}
}

static void	ft_draw(t_cub *cub, int x, t_ivec3 info, t_frame texture)
{
	t_ipos	size;
	t_ipos	texture_pos;
	int		color;
	int		win_y_offset;
	t_ipos	win;

	size = (t_ipos){info.x, info.y};
	texture_pos.x = info.z;
	win_y_offset = (HEIGHT - size.y) / 2;
	win.y = -1;
	while (++win.y < size.y && win.y + win_y_offset < HEIGHT)
	{
		if (win.y + win_y_offset < 0)
			continue ;
		win.x = -1;
		while (++win.x < size.x && win.x + x < WIDTH)
		{
			texture_pos.y = texture.height * (float) win.y / size.y;
			color = *(int *)(char *)(texture.addr
					+ (texture_pos.y * texture.line_size + texture_pos.x * 4));
			if (color != 0 && win.x + x >= 0 && win.y + win_y_offset < HEIGHT)
				ft_put_pixel(cub->frame,
					win.x + x, win.y + win_y_offset, color);
		}
	}
}
