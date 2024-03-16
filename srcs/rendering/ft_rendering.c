/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:38:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/16 03:50:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	ft_set_pixel(t_texture frame, int x, int y, int color)
{
	char	*dst;

	dst = frame.addr + (y * frame.line_size + x * (frame.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

void	ft_put_line(t_texture frame, t_ipos start, t_ipos end, int color)
{
	int		dx;
	int		dy;
	int		steps;
	double	x;
	double	y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x = (double) dx / steps;
	y = (double) dy / steps;
	for (int i = 0; i < steps; i++)
	{
		ft_set_pixel(frame, start.x + x * i, start.y + y * i, color);
	}
}

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

// t_casting	ft_cast_ray(t_cub *cub, double angle)
// {
// 	t_casting	casting;
// 	t_ull		steps;
// 	double		step_x;
// 	double		step_y;

// 	casting.x = cub->position.x;
// 	casting.y = cub->position.y;
// 	step_x = cos(angle) * RAY_STEP;
// 	step_y = sin(angle) * RAY_STEP;
// 	steps = 0;
// 	while (steps < RAY_MAX_STEPS
// 		&& (int) casting.y >= 0 && (int) casting.y < cub->map_size.y
// 		&& (int) casting.x >= 0 && (int) casting.x < cub->map_size.x
// 		&& cub->map_array[(int) casting.y][(int) casting.x] != '1')
// 	{
// 		casting.x += step_x;
// 		casting.y += step_y;
// 		steps++;
// 	}
// 	casting.angle = angle;
// 	if (steps < RAY_MAX_STEPS
// 		&& (int) casting.y >= 0 && (int) casting.y < cub->map_size.y
// 		&& (int) casting.x >= 0 && (int) casting.x < cub->map_size.x
// 		&& cub->map_array[(int) casting.y][(int) casting.x] != '1')
// 		casting.distance = -1;
// 	else
// 		casting.distance = steps * RAY_STEP;
// 	return (casting);
// }

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

	while (casting->hor_y >= 0 && casting->hor_y < cub->map_size.y
		&& casting->hor_x >= 0 && casting->hor_x < cub->map_size.x
		&& cub->map_array[(int) casting->hor_y - (casting->angle < PI ? 0 : 1)][(int) casting->hor_x] != '1')
	{
		casting->hor_x += casting->hor_step_x;
		casting->hor_y += casting->hor_step_y;
	}

	if (casting->hor_y < 0 || casting->hor_y >= cub->map_size.y
		|| casting->hor_x < 0 || casting->hor_x >= cub->map_size.x
		|| cub->map_array[(int) casting->hor_y - (casting->angle < PI ? 0 : 1)][(int) casting->hor_x] != '1')
		casting->hor_dist = -1;
	else
		casting->hor_dist = sqrt(pow(cub->position.x - casting->hor_x, 2)
			+ pow(cub->position.y - casting->hor_y, 2));
}

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
		&& casting->ver_x >= 0 && casting->ver_x < cub->map_size.x
		&& cub->map_array[(int) casting->ver_y][(int) casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1)] != '1')
	{
		casting->ver_x += casting->ver_step_x;
		casting->ver_y += casting->ver_step_y;
	}

	if (casting->ver_y < 0 || casting->ver_y >= cub->map_size.y
		|| casting->ver_x < 0 || casting->ver_x >= cub->map_size.x
		|| cub->map_array[(int) casting->ver_y][(int) casting->ver_x - (casting->angle < PI_2 || casting->angle > 3 * PI_2 ? 0 : 1)] != '1')
		casting->ver_dist = -1;
	else
		casting->ver_dist = sqrt(pow(cub->position.x - casting->ver_x, 2)
			+ pow(cub->position.y - casting->ver_y, 2));
}

t_casting	ft_cast_ray(t_cub *cub, double angle)
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

void	ft_put_chunk(t_cub *cub, int x, t_ipos size, int color)
{
	if (size.x > WIDTH)
		size.x = WIDTH;
	if (size.y > HEIGHT)
		size.y = HEIGHT;
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			ft_set_pixel(cub->frame, x + i, (HEIGHT - size.y) / 2 + j, color);
		}
	}
}

void	ft_render_minimap(t_cub *cub, t_casting castings[RAYS])
{
	// int		TILE_SIZE = 15;
	// int		PLAYER_SIZE = 5;
	int		TILE_SIZE = 30;
	int		PLAYER_SIZE = 10;
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

	for (int rc = 0; rc < RAYS; rc++)
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
	// if (c.hor_dist != -1)
	// 	ft_put_line(cub->frame,
	// 		(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE, cub->position.y * TILE_SIZE + TILE_SIZE},
	// 		(t_ipos){c.hor_x * TILE_SIZE + TILE_SIZE, c.hor_y * TILE_SIZE + TILE_SIZE},
	// 		0x00FF00FF);
	// if (c.ver_dist != -1)
	// 	ft_put_line(cub->frame,
	// 		(t_ipos){cub->position.x * TILE_SIZE + TILE_SIZE, cub->position.y * TILE_SIZE + TILE_SIZE},
	// 		(t_ipos){c.ver_x * TILE_SIZE + TILE_SIZE, c.ver_y * TILE_SIZE + TILE_SIZE},
	// 		0x00FF00FF);

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

void	ft_render(t_cub *cub)
{
	ft_render_floor(cub);
	ft_render_ceiling(cub);

	t_casting	castings[RAYS];

	double	angle = cub->orientation - FOV / 2;
	if (angle < 0)
		angle += 2 * PI;
	double	step = (double) FOV / RAYS;
	double	width = (double) WIDTH / RAYS;
	int		ray = 0;
	while (ray < RAYS)
	{
		double		a = angle + step * ray;
		if (a >= 2 * PI)
			a -= 2 * PI;
		t_casting	casting = ft_cast_ray(cub, a);
		int			height = ((HEIGHT / casting.distance) * 1.5);
		int			x = ray * width;
		// printf("RAY: %d, %10f, %10f, %10f, %10f, [%8d]\n", ray, casting.x, casting.y, casting.angle, casting.distance, height);
		ft_put_chunk(cub, x, (t_ipos){width + 1, height}, 0x00FFFFFF);
		castings[ray] = casting;
		ray++;
	}

	ft_render_minimap(cub, castings);

	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->frame.img, 0, 0);

	cub->frames++;
	// if (cub->frame % 10 == 0)
	// 	printf("Frame: %lld\n", cub->frame);
}

int	ft_game_quit(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
	return (0);
}

int	ft_game_keydown(int keycode, t_cub *cub)
{
	(void)keycode;
	(void)cub;
	printf("Keydown: %d\n", keycode);
	printf("  Player\n");
	printf("    > pos: %10f, %10f\n", cub->position.x, cub->position.y);
	printf("    > dir: %10frad (%3fdeg)\n", cub->orientation, cub->orientation * 180 / PI);
	if (keycode == XK_Escape)
		ft_game_quit(cub);
	if (keycode == XK_w)
		cub->keys.forward = TRUE;
	if (keycode == XK_s)
		cub->keys.backward = TRUE;
	if (keycode == XK_a)
		cub->keys.rot_left = TRUE;
	if (keycode == XK_d)
		cub->keys.rot_right = TRUE;
	return (0);
}

int	ft_game_keyup(int keycode, t_cub *cub)
{
	(void)cub;
	printf("Keyup: %d\n", keycode);
	if (keycode == XK_w)
		cub->keys.forward = FALSE;
	if (keycode == XK_s)
		cub->keys.backward = FALSE;
	if (keycode == XK_a)
		cub->keys.rot_left = FALSE;
	if (keycode == XK_d)
		cub->keys.rot_right = FALSE;
	return (0);
}

void ft_handle_keys(t_cub *cub)
{
	if (cub->keys.forward)
	{
		cub->position.x += cos(cub->orientation) * WALK_SPEED;
		cub->position.y += sin(cub->orientation) * WALK_SPEED;
	}
	if (cub->keys.backward)
	{
		cub->position.x -= cos(cub->orientation) * WALK_SPEED;
		cub->position.y -= sin(cub->orientation) * WALK_SPEED;
	}
	if (cub->keys.rot_left)
	{
		cub->orientation -= ROT_SPEED;
	}
	if (cub->keys.rot_right)
	{
		cub->orientation += ROT_SPEED;
	}
	if (cub->orientation > 2 * PI)
		cub->orientation -= 2 * PI;
	else if (cub->orientation < 0)
		cub->orientation += 2 * PI;
}

int	ft_game_loop(t_cub *cub)
{
	ft_handle_keys(cub);
	ft_render(cub);
	return (0);
}

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

void	ft_keys_init(t_keys *keys)
{
	keys->forward = FALSE;
	keys->backward = FALSE;
	keys->rot_left = FALSE;
	keys->rot_right = FALSE;
}

void	ft_rendering(t_cub *cub)
{
	(void)cub;

	cub->position.x = 5.661107;
	cub->position.y = 10.273338;
	cub->orientation = 1.919818;

	cub->frames = 0;
	ft_keys_init(&cub->keys);
	ft_mlx_init(cub);
	mlx_loop(cub->mlx);
}
