/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:38:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/15 17:10:36 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	ft_render_floor(t_cub *cub)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = HEIGHT / 2; j < HEIGHT; j++)
		{
			mlx_pixel_put(cub->mlx, cub->mlx_win, i, j, cub->floor_c);
		}
	}
}

void	ft_render_ceiling(t_cub *cub)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT / 2; j++)
		{
			mlx_pixel_put(cub->mlx, cub->mlx_win, i, j, cub->ceiling_c);
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
	while (steps < RAY_MAX_STEPS && (int) casting.y >= 0 && (int) casting.y < cub->map_size.y && (int) casting.x >= 0 && (int) casting.x < cub->map_size.x
		&& cub->map_array[(int) casting.y][(int) casting.x] != '1')
	{
		casting.x += step_x;
		casting.y += step_y;
		steps++;
	}
	casting.angle = angle;
	if (cub->map_array[(int) casting.y][(int) casting.x] != '1')
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
			mlx_pixel_put(cub->mlx, cub->mlx_win, x + i, (HEIGHT - size.y) / 2 + j, color);
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

	cub->frame++;
	// if (cub->frame % 10 == 0)
	// 	printf("Frame: %lld\n", cub->frame);
}

int	ft_game_loop(t_cub *cub)
{
	ft_render(cub);
	return (0);
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
	if (keycode == XK_Escape)
		ft_game_quit(cub);
	if (keycode == XK_space || 1)
	{
		printf("Player\n");
		printf("  > pos: %10f, %10f\n", cub->position.x, cub->position.y);
		printf("  > dir: %10frad (%3fdeg)\n", cub->orientation, cub->orientation * 180 / PI);
	}
	if (keycode == XK_w)
	{
		cub->position.x += cos(cub->orientation) * WALK_SPEED;
		cub->position.y += sin(cub->orientation) * WALK_SPEED;
	}
	if (keycode == XK_s)
	{
		cub->position.x -= cos(cub->orientation) * WALK_SPEED;
		cub->position.y -= sin(cub->orientation) * WALK_SPEED;
	}
	if (keycode == XK_a)
	{
		cub->orientation -= ROT_SPEED;
	}
	if (keycode == XK_d)
	{
		cub->orientation += ROT_SPEED;
	}
	if (cub->orientation > 2 * PI)
		cub->orientation -= 2 * PI;
	else if (cub->orientation < 0)
		cub->orientation += 2 * PI;
	return (0);
}

void	ft_mlx_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, NAME);
	mlx_do_key_autorepeaton(cub->mlx);
	mlx_loop_hook(cub->mlx, &ft_game_loop, cub);
	mlx_hook(cub->mlx_win, ON_DESTROY, 0L, &ft_game_quit, cub);
	mlx_hook(cub->mlx_win, ON_KEYDOWN, MASK_KEY_PRESS, &ft_game_keydown, cub);
}

void	ft_rendering(t_cub *cub)
{
	(void)cub;

	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");

	for (int i = 0; i < cub->map_size.y; i++)
	{
		write(1, "|", 1);
		for (int j = 0; j < cub->map_size.x; j++)
		{
			write(1, &(char){cub->map_array[i][j]}, 1);
		}
		write(1, "|\n", 2);
	}
	
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	printf("Rendering...\n");
	cub->frame = 0;
	ft_mlx_init(cub);
	mlx_loop(cub->mlx);
}
