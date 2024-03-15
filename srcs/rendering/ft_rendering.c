/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:38:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/15 20:31:29 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	ft_set_pixel(t_texture frame, int x, int y, int color)
{
	char	*dst;

	dst = frame.addr + (y * frame.line_size + x * (frame.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

t_casting	ft_cast_ray(t_cub *cub, float angle)
{
	t_casting	casting;
	t_ull		steps;
	float		step_x;
	float		step_y;

	casting.x = cub->position.x;
	casting.y = cub->position.y;
	step_x = cos(angle) * RAY_STEP;
	step_y = sin(angle) * RAY_STEP;
	steps = 0;
	while (steps < RAY_MAX_STEPS
		&& (int) casting.y >= 0 && (int) casting.y < cub->map_size.y
		&& (int) casting.x >= 0 && (int) casting.x < cub->map_size.x
		&& cub->map_array[(int) casting.y][(int) casting.x] != '1')
	{
		casting.x += step_x;
		casting.y += step_y;
		steps++;
	}
	casting.angle = angle;
	if (steps < RAY_MAX_STEPS
		&& (int) casting.y >= 0 && (int) casting.y < cub->map_size.y
		&& (int) casting.x >= 0 && (int) casting.x < cub->map_size.x
		&& cub->map_array[(int) casting.y][(int) casting.x] != '1')
		casting.distance = -1;
	else
		casting.distance = steps * RAY_STEP;
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

void	ft_render(t_cub *cub)
{
	ft_render_floor(cub);
	ft_render_ceiling(cub);

	float	angle = cub->orientation - FOV / 2;
	float	step = FOV / RAYS;
	int		width = WIDTH / RAYS;
	int		ray = 0;
	while (ray < RAYS)
	{
		t_casting	casting = ft_cast_ray(cub, angle);
		int			height = ((HEIGHT / casting.distance) * 1.5);
		int			x = ray * width;
		// printf("RAY: %d, %10f, %10f, %10f, %10f, [%8d]\n", ray, casting.x, casting.y, casting.angle, casting.distance, height);
		ft_put_chunk(cub, x, (t_ipos){width, height}, 0x00FFFFFF);
		angle += step;
		ray++;
	
	}

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

	cub->frames = 0;
	ft_keys_init(&cub->keys);
	ft_mlx_init(cub);
	mlx_loop(cub->mlx);
}
