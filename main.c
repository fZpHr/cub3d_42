/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:48:24 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/12 21:37:00 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

typedef struct
{
	void	*mlx;
	void	*win;
	void	*logo_png;
	void	*logo_jpg;
	void	*logo_bmp;
	void	*img;
}			mlx_t;

int	update(void *param)
{
	static int	i = 0;
	mlx_t		*mlx;
	int			color;

	mlx = (mlx_t *)param;
	if (i == 200)
		mlx_clear_window(mlx->mlx, mlx->win);
	if (i >= 250)
		mlx_set_font_scale(mlx->mlx, mlx->win, "default", 16.f);
	else
		mlx_set_font_scale(mlx->mlx, mlx->win, "default", 6.f);
	mlx_string_put(mlx->mlx, mlx->win, 160, 120, 0xFFFF2066,
		"this text should be hidden");
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->logo_png, 100, 100);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->logo_jpg, 210, 150);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->logo_bmp, 220, 40);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 150, 60);
	mlx_set_font(mlx->mlx, mlx->win, "default");
	mlx_string_put(mlx->mlx, mlx->win, 20, 50, 0xFFFFFFFF, "that's a text");
	color = 0;
	for (int j = 0; j < 400; j++)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, j, j, 0xFFFF0000 + color);
		mlx_pixel_put(mlx->mlx, mlx->win, 399 - j, j, 0xFF0000FF);
		color += (color < 255);
	}
	i++;
	return (0);
}

void	*create_image(mlx_t *mlx)
{
	unsigned char	pixel[4];
	void			*img;

	img = mlx_new_image(mlx->mlx, 100, 100);
	for (int i = 0, j = 0, k = 0; i < (100 * 100) * 4; i += 4, j++)
	{
		if (j >= 100)
		{
			j = 0;
			k++;
		}
		if (i < 10000 || i > 20000)
		{
			pixel[0] = i;
			pixel[1] = j;
			pixel[2] = k;
			pixel[3] = 0x99;
			mlx_set_image_pixel(mlx->mlx, img, j, k, *((int *)pixel));
		}
	}
	return (img);
}

int	key_hook(int key, void *param)
{
	int		x;
	int		y;
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	mlx_mouse_get_pos(mlx->mlx, &x, &y);
	switch (key)
	{
	case 41: // ESCAPE
		mlx_loop_end(mlx->mlx);
		break ;
	case 22: // (S)how
		mlx_mouse_show();
		break ;
	case 11: // (H)ide
		mlx_mouse_hide();
		break ;
	case 6: // (C)lear
		mlx_clear_window(mlx->mlx, mlx->win);
		break ;
	case 79: // RIGHT KEY
		mlx_mouse_move(mlx->mlx, mlx->win, x + 10, y);
		break ;
	case 80: // LEFT KEY
		mlx_mouse_move(mlx->mlx, mlx->win, x - 10, y);
		break ;
	case 81: // UP KEY
		mlx_mouse_move(mlx->mlx, mlx->win, x, y + 10);
		break ;
	case 82: // DOWN KEY
		mlx_mouse_move(mlx->mlx, mlx->win, x, y - 10);
		break ;
	default:
		break ;
	}
	return (0);
}

int	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(((mlx_t *)param)->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_map cube;

	ft_init(&cube);
	ft_check_args(ac);
	ft_check_map_file(&cube, av[1]);
	ft_map_into_array(&cube, av[1]);
	ft_find_player_position(&cube);
	ft_check_wall(&cube, cube.player_position[0], cube.player_position[1]);
	int i = 0;
	while (i <= cube.map_size_y)
	{
		printf("%s\n", cube.map_array[i]);
		i++;
	}
	ft_free_array(cube.map_array);
	free(cube.no);
	free(cube.so);
	free(cube.we);
	free(cube.ea);

	return (0);
}