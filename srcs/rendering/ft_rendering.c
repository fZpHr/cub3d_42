/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:38:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/17 05:10:11 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"


/**
 * @brief Set the pixel of the frame at the given position
 * 			to the given color using addresses.
 * 
 * @param frame 	The frame to edit
 * @param x 		The x position of the pixel
 * @param y 		The y position of the pixel
 * @param color 	The color to set (in ARGB format)
*/
void	ft_set_pixel(t_texture frame, int x, int y, int color)
{
	char	*dst;

	dst = frame.addr + (y * frame.line_size + x * (frame.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


/**
 * @brief Fill a rectangle of the frame with the given color (see ft_set_pixel).
 * 
 * @param frame 	The frame to edit
 * @param pos 		The position of the rectangle (in px)
 * @param size 		The size of the rectangle (width, height, in px)
 * @param color 	The color to set (in ARGB format)
*/
void	ft_put_rect(t_texture frame, t_ipos pos, t_ipos size, int color)
{
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			ft_set_pixel(frame, pos.x + i, pos.y + j, color);
		}
	}
}

/**
 * @brief Draw a line between two points of the frame with the given color.
 * 
 * @param frame 	The frame to edit
 * @param start 	The start position of the line (in px)
 * @param end 		The end position of the line (in px)
 * @param color 	The color to set (in ARGB format)
*/
void	ft_put_line(t_texture frame, t_ipos start, t_ipos end, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	x;
	float	y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x = (float) dx / steps;
	y = (float) dy / steps;
	for (int i = 0; i < steps; i++)
	{
		ft_set_pixel(frame, start.x + x * i, start.y + y * i, color);
	}
}

/**
 * @brief The floor == colored rectangle, expanding along the width
 * 			from the middle to the bottom of the screen.
 * 
 * @param cub 	The game structure
*/
void	ft_render_floor(t_cub *cub)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = HEIGHT / 2 - 1; j < HEIGHT; j++)
		{
			ft_set_pixel(cub->frame, i, j, cub->floor_c);
		}
	}
}

/**
 * @brief The ceiling == colored rectangle, expanding along the width
 * 			from the top to the middle of the screen.
 * 
 * @param cub 	The game structure
*/
void	ft_render_ceiling(t_cub *cub)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT / 2; j++)
		{
			ft_set_pixel(cub->frame, i, j, cub->ceiling_c);
		}
	}
}

/**
 * @brief Check if the ray is hitting horizontally a wall.
 * 
 * @brief	1. Step to the closest horizontal grid line
 * @brief		- `y = closest y coordinate of a horizontal grid line`
 * @brief		- `x = pos.x - (pos.y - y) / tan(a)` --> The x of the ray at y
 * 
 * @brief	2. Define deltas to checks all the other horizontal grid lines
 * @brief		- `delta_y = -1 if ray facing up else 1`
 * @brief		- `delta_x = 1 / tan(-a) if ray facing left else -1 / tan(-a)`
 * 
 * @note `-a` is used trigo instead of `a` because the Y axis is inverted.
 * 
 * @param cub 		The game structure
 * @param casting 	The ray casting structure, with all the results !
*/
void	ft_hor_casting(t_cub *cub, t_casting *casting)
{
	casting->hor_y = (int) cub->position.y;
	if (casting->angle < PI)
		casting->hor_y++;
	casting->hor_x = cub->position.x - (cub->position.y - casting->hor_y) / tan(casting->angle);

	casting->hor_step_y = -1;
	if (casting->angle < PI)
		casting->hor_step_y = 1;
	casting->hor_step_x = 1 / tan(-casting->angle);
	if (casting->angle < PI)
		casting->hor_step_x = -casting->hor_step_x;

	while (casting->hor_y - (casting->angle < PI ? 0 : 1) >= 0 && casting->hor_y < cub->map_size.y
		&& casting->hor_x >= 0 && casting->hor_x < cub->map_size.x
		&& cub->map_array[(int) casting->hor_y - (casting->angle < PI ? 0 : 1)][(int) casting->hor_x] != '1')
	{
		casting->hor_x += casting->hor_step_x;
		casting->hor_y += casting->hor_step_y;
	}

	if (casting->hor_y - (casting->angle < PI ? 0 : 1) < 0 || casting->hor_y >= cub->map_size.y
		|| casting->hor_x < 0 || casting->hor_x >= cub->map_size.x
		|| cub->map_array[(int) casting->hor_y - (casting->angle < PI ? 0 : 1)][(int) casting->hor_x] != '1')
		casting->hor_dist = -1;
	else
		casting->hor_dist = sqrt(pow(cub->position.x - casting->hor_x, 2)
			+ pow(cub->position.y - casting->hor_y, 2));
}

/**
 * @brief Check if the ray is hitting vertically a wall.
 * 
 * @brief	1. Step to the closest vertical grid line
 * @brief		- `x = closest x coordinate of a vertical grid line`
 * @brief		- `y = pos.y - (pos.x - x) * tan(a)` --> The y of the ray at x
 * 
 * @brief	2. Define deltas to checks all the other vertical grid lines
 * @brief		- `delta_x = -1 if ray facing left else 1`
 * @brief		- `delta_y = tan(-a) if ray facing up else -tan(-a)`
 * 
 * @note `-a` is used trigo instead of `a` because the Y axis is inverted.
 * 
 * @param cub 		The game structure
 * @param casting 	The ray casting structure, with all the results !
*/
void	ft_ver_casting(t_cub *cub, t_casting *casting)
{
	casting->ver_x = (int) cub->position.x;
	if (casting->angle < PI_2 || casting->angle > 3 * PI_2)
		casting->ver_x++;
	casting->ver_y = cub->position.y - (cub->position.x - casting->ver_x) * tan(casting->angle);

	casting->ver_step_x = -1;
	if (casting->angle < PI_2 || casting->angle > 3 * PI_2)
		casting->ver_step_x = 1;
	casting->ver_step_y = tan(-casting->angle);
	if (casting->angle < PI_2 || casting->angle > 3 * PI_2)
		casting->ver_step_y = -casting->ver_step_y;

	while (casting->ver_y >= 0 && casting->ver_y < cub->map_size.y
		&& casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1) >= 0 && casting->ver_x < cub->map_size.x
		&& cub->map_array[(int) casting->ver_y][(int) casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1)] != '1')
	{
		casting->ver_x += casting->ver_step_x;
		casting->ver_y += casting->ver_step_y;
	}

	if (casting->ver_y < 0 || casting->ver_y >= cub->map_size.y
		|| casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1) < 0 || casting->ver_x >= cub->map_size.x
		|| cub->map_array[(int) casting->ver_y][(int) casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1)] != '1')
		casting->ver_dist = -1;
	else
		casting->ver_dist = sqrt(pow(cub->position.x - casting->ver_x, 2)
			+ pow(cub->position.y - casting->ver_y, 2));
}

/**
 * @brief Cast a ray from the player position to the given angle.
 * 
 * @brief	1. Make an horizontal collision detection:
 * @brief		- If the ray hits, save the
 * @brief			- x and y position of the collision
 * @brief			- distance to the collision
 * @brief			- facing of the wall (either `NORTH` or `SOUTH`)
 * @brief		- else, save `-1` as the distance.
 * 
 * @brief	2. Make a vertical collision detection:
 * @brief		- If the ray hits, save the
 * @brief			- x and y position of the collision
 * @brief			- distance to the collision
 * @brief			- facing of the wall (either `WEST` or `EAST`)
 * @brief		- else, save `-1` as the distance.
 * 
 * @brief	3. Take the closest collision, save it and return it.
 * @brief		- If the ray hits, save the
 * @brief			- x and y position of the collision
 * @brief			- distance to the collision
 * @brief			- facing of the wall (either `WEST` or `EAST`)
 * @brief		- else, save `-1` as the distance.
 * 
 * @brief	- This way, we check max `map's height + map's width` collisions !
 * 
 * @param cub 		The game structure
 * @param angle 	The angle of the ray (in rad)
 * 
 * @return t_casting 	The result of the ray casting
*/
t_casting	ft_cast_ray(t_cub *cub, float angle)
{
	t_casting	casting;

	casting.angle = angle;
	casting.hor_dist = -1;
	casting.ver_dist = -1;
	ft_hor_casting(cub, &casting);
	ft_ver_casting(cub, &casting);
	if (casting.hor_dist != -1 && (casting.hor_dist <= casting.ver_dist || casting.ver_dist == -1))
	{
		casting.x = casting.hor_x;
		casting.y = casting.hor_y;
		casting.distance = casting.hor_dist;
		casting.facing = (casting.angle < PI) ? NORTH : SOUTH;
	}
	else if (casting.ver_dist != -1 && (casting.ver_dist <= casting.hor_dist || casting.hor_dist == -1))
	{
		casting.x = casting.ver_x;
		casting.y = casting.ver_y;
		casting.distance = casting.ver_dist;
		casting.facing = (casting.angle < PI_2 || casting.angle > 3 * PI_2) ? WEST : EAST;
	}
	else
		casting.distance = -1;
	return (casting);
}

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
void	ft_put_chunk(t_cub *cub, int x, t_ipos size, t_casting casting)
{
	t_texture	texture;
	int			texture_x;
	if (casting.facing == NORTH)
	{
		texture = cub->no;
		texture_x = texture.width - 1 - (int) (casting.x * texture.width) % texture.width;
	}
	else if (casting.facing == SOUTH)
	{
		texture = cub->so;
		texture_x = (int) (casting.x * texture.width) % texture.width;
		
	}
	else if (casting.facing == WEST)
	{
		texture = cub->we;
		texture_x = (int) (casting.y * texture.width) % texture.width;
	}
	else if (casting.facing == EAST)
	{
		texture = cub->ea;
		texture_x = texture.width - 1 - (int) (casting.y * texture.width) % texture.width;
	}

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
			if (win_x + x >= 0 && win_y + win_y_offset < HEIGHT)
				ft_set_pixel(cub->frame, win_x + x, win_y + win_y_offset, color);
		}
	}
}

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
			if (cub->map_array[i][j] == '1' || cub->map_array[i][j] == '0')
			{
				ft_put_rect(cub->frame,
					(t_ipos){j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE},
					(t_ipos){TILE_SIZE, TILE_SIZE}, 0x00CCCCCC);
				ft_put_rect(cub->frame,
					(t_ipos){j * TILE_SIZE + TILE_SIZE + 1, i * TILE_SIZE + TILE_SIZE + 1},
					(t_ipos){TILE_SIZE - 2, TILE_SIZE - 2},
					cub->map_array[i][j] == '1' ? 0x00EEEEEE : 0x00000000);
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

	// ft_put_line(cub->frame,
	// 	(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE, cub->position.y * TILE_SIZE + TILE_SIZE},
	// 	(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE + cos(cub->orientation) * TILE_SIZE,
	// 		cub->position.y * TILE_SIZE + TILE_SIZE + sin(cub->orientation) * TILE_SIZE},
	// 	0x00FF0000);
	ft_put_rect(cub->frame,
		(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE - PLAYER_SIZE / 2,
			cub->position.y * TILE_SIZE + TILE_SIZE - PLAYER_SIZE / 2},
		(t_ipos){PLAYER_SIZE, PLAYER_SIZE}, 0x0000FF00);
}

/**
 * @brief Render a frame.
 * 
 * @brief	1. Render the floor and the ceiling
 * 				(see ft_render_floor and ft_render_ceiling)
 * 
 * @brief	2. Ray casting (see ft_cast_ray)
 * @brief		- Cast `RAYS` rays evenly from
 * 					`dir - FOV / 2` to `dir + FOV / 2`
 * @brief		- Cast and save the result in `castings` (for the minimap)
 * 
 * @brief	3. Calculate wall height
 * @brief		- Fish-eye correction: `dist *= cos(dir - a)`
 * @brief		- `height = (HEIGHT / dist) * 1.5`
 * 
 * @brief	4. Draw the wall (see ft_put_chunk)
 * 
 * @brief	5. Draw the minimap (see ft_render_minimap)
 * 
 * @param cub 	The game structure
*/
void	ft_render(t_cub *cub)
{
	ft_render_floor(cub);
	ft_render_ceiling(cub);

	t_casting	castings[RAYS];

	float	angle = cub->orientation - FOV / 2;
	if (angle < 0)
		angle += 2 * PI;
	float	step = (float) FOV / RAYS;
	float	width = (float) WIDTH / RAYS;
	int		ray = 0;
	while (ray < RAYS)
	{
		float		a = angle + step * ray;
		if (a >= 2 * PI)
			a -= 2 * PI;
		t_casting	casting = ft_cast_ray(cub, a);
		if (casting.distance != -1)
		{
			casting.distance *= cos(cub->orientation - casting.angle);
			if (casting.distance < 0.2)
				casting.distance = 0.2;
			int			height = ((HEIGHT / casting.distance) * 1.5);
			int			x = ray * width;
			ft_put_chunk(cub, x, (t_ipos){width + 1, height}, casting);
		}
		castings[ray] = casting;
		ray++;
	}

	ft_render_minimap(cub, castings);

	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->frame.img, 0, 0);

	cub->frames++;
}

/**
 * @brief Quit the game.
 * 
 * @param cub 	The game structure
 * 
 * @return int 	Always `0`
*/
int	ft_game_quit(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
	return (0);
}

/**
 * @brief Handle the keydown event.
 * 
 * @brief	- `Escape`: Quit the game
 * 
 * @brief	- `WASD` or arrows: Toggle the moving variables
 * 
 * @param keycode 	The key pressed
 * @param cub 		The game structure
 * 
 * @return int 		Always `0`
*/
int	ft_game_keydown(int keycode, t_cub *cub)
{
	(void)keycode;
	(void)cub;
	if (keycode == XK_Escape)
		ft_game_quit(cub);
	if (keycode == XK_w || keycode == XK_Up)
		cub->keys.forward = TRUE;
	if (keycode == XK_s || keycode == XK_Down)
		cub->keys.backward = TRUE;
	if (keycode == XK_a || keycode == XK_Left)
		cub->keys.rot_left = TRUE;
	if (keycode == XK_d || keycode == XK_Right)
		cub->keys.rot_right = TRUE;
	return (0);
}

/**
 * @brief Handle the keyup event.
 * 
 * @brief	- `WASD` or arrows: Toggle the moving variables
 * 
 * @param keycode 	The key released
 * @param cub 		The game structure
 * 
 * @return int 		Always `0`
*/
int	ft_game_keyup(int keycode, t_cub *cub)
{
	(void)cub;
	printf("Keyup: %d\n", keycode);
	if (keycode == XK_w || keycode == XK_Up)
		cub->keys.forward = FALSE;
	if (keycode == XK_s || keycode == XK_Down)
		cub->keys.backward = FALSE;
	if (keycode == XK_a || keycode == XK_Left)
		cub->keys.rot_left = FALSE;
	if (keycode == XK_d || keycode == XK_Right)
		cub->keys.rot_right = FALSE;
	return (0);
}


/**
 * @brief Check if the player is colliding with a wall at the given position,
 * 			or if he is out of the map.
 * 
 * @param cub 		The game structure
 * @param position 	The position to check
 * 
 * @return t_bool 	`TRUE` if the player shouldn't be here, `FALSE` otherwise
*/
t_bool	ft_does_collide(t_cub *cub, t_pos position)
{
	return (position.x < 0 || position.x >= cub->map_size.x
		|| cub->map_array[(int) position.y][(int) position.x] == '1');
}

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

/**
 * @brief Check if a key is pressed --> move of the player if needed.
 * 
 * @param cub 	The game structure
*/
void	ft_handle_keys(t_cub *cub)
{
	if (cub->keys.forward)
		ft_move_forward(cub);
	if (cub->keys.backward)
		ft_move_backward(cub);
	if (cub->keys.rot_left)
		cub->orientation -= ROT_SPEED;
	if (cub->keys.rot_right)
		cub->orientation += ROT_SPEED;
	if (cub->orientation > 2 * PI)
		cub->orientation -= 2 * PI;
	else if (cub->orientation < 0)
		cub->orientation += 2 * PI;
}

/**
 * @brief The game loop.
 * 
 * @param cub 	The game structure
 * 
 * @return int 	Always `0`
*/
int	ft_game_loop(t_cub *cub)
{
	ft_handle_keys(cub);
	ft_render(cub);
	return (0);
}


/**
 * @brief Create a new MLX frame (screen sized) and return all the info.
 * 
 * @param cub 		The game structure
 * @param free_old 	Should we free the old frame ? (in cub is not NULL)
 * 
 * @return t_texture 	The new frame
*/
t_texture	ft_mlx_new_frame(t_cub *cub, t_bool free_old)
{
	t_texture	frame;

	if (free_old && cub->frame.img)
	{
		mlx_destroy_image(cub->mlx, cub->frame.img);
		cub->frame.img = NULL;
	}
	frame.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img,
		&frame.bits_per_pixel, &frame.line_size, &frame.endian);
	// if (!frame.img || !frame.addr)
	// 	TODO: Do stuff...
	return (frame);
}


/**
 * @brief Initialize the MLX (window, configs, hooks).
 * 
 * @param cub 	The game structure
*/
void	ft_mlx_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, NAME);
	cub->frame.img = NULL;
	cub->frame = ft_mlx_new_frame(cub, TRUE);
	mlx_do_key_autorepeaton(cub->mlx);
	mlx_loop_hook(cub->mlx, &ft_game_loop, cub);
	mlx_hook(cub->mlx_win, ON_DESTROY, 0L, &ft_game_quit, cub);
	mlx_hook(cub->mlx_win, ON_KEYDOWN, MASK_KEY_PRESS, &ft_game_keydown, cub);
	mlx_hook(cub->mlx_win, ON_KEYUP, MASK_KEY_RELEASE, &ft_game_keyup, cub);
}

/**
 * @brief Initialize the keys structure.
 * 
 * @note	Point: avoid `uninitialized values` errors.
 * 
 * @param keys 	The keys structure
*/
void	ft_keys_init(t_keys *keys)
{
	keys->forward = FALSE;
	keys->backward = FALSE;
	keys->rot_left = FALSE;
	keys->rot_right = FALSE;
}

/**
 * @brief Initialize the MLX and start the rendering loop.
 * 
 * @param cub 	The game structure
*/
void	ft_rendering(t_cub *cub)
{
	(void)cub;

	cub->frames = 0;
	ft_keys_init(&cub->keys);
	ft_mlx_init(cub);
	mlx_loop(cub->mlx);
}
