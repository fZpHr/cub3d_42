/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_to_cube.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:37 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/20 05:31:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void		ft_keys_init(t_keys *keys);

int	ft_handle_img(t_cub *cub, t_map *map)
{
	(void)cub;
	(void)map;
	// cub->no.img = mlx_xpm_file_to_image(cub->mlx, map->no, &cub->no.width,
	// 		&cub->no.height);
	// if (!cub->no.img)
	// 	return (1);
	// cub->so.img = mlx_xpm_file_to_image(cub->mlx, map->so, &cub->so.width,
	// 		&cub->so.height);
	// if (!cub->so.img)
	// 	return (1);
	// cub->we.img = mlx_xpm_file_to_image(cub->mlx, map->we, &cub->we.width,
	// 		&cub->we.height);
	// if (!cub->we.img)
	// 	return (1);
	// cub->ea.img = mlx_xpm_file_to_image(cub->mlx, map->ea, &cub->ea.width,
	// 		&cub->ea.height);
	// if (!cub->ea.img)
	// 	return (1);
	return (0);
}

int	ft_handle_addr(t_cub *cub)
{
	(void)cub;
	// cub->no.addr = mlx_get_data_addr(cub->no.img, &cub->no.bits_per_pixel,
	// 		&cub->no.line_size, &cub->no.endian);
	// if (!cub->no.addr)
	// 	return (1);
	// cub->so.addr = mlx_get_data_addr(cub->so.img, &cub->so.bits_per_pixel,
	// 		&cub->so.line_size, &cub->so.endian);
	// if (!cub->so.addr)
	// 	return (1);
	// cub->we.addr = mlx_get_data_addr(cub->we.img, &cub->we.bits_per_pixel,
	// 		&cub->we.line_size, &cub->we.endian);
	// if (!cub->we.addr)
	// 	return (1);
	// cub->ea.addr = mlx_get_data_addr(cub->ea.img, &cub->ea.bits_per_pixel,
	// 		&cub->ea.line_size, &cub->ea.endian);
	// if (!cub->ea.addr)
	// 	return (1);
	return (0);
}

void	ft_init_cub_array(t_cub *cub, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_size_y)
	{
		cub->map_array[i] = ft_calloc(map->map_size_x, sizeof(t_tile));
		if (!cub->map_array[i])
			ft_error_handle(map, "Error\n", "Can't allocate memory", 1);
		j = 0;
		while (j < map->map_size_x)
		{
			cub->map_array[i][j].type = map->map_array[i][j];
			j++;
		}
		i++;
	}
}

/**
 * @brief Assigns the map data to the cub structure
 *
 * @param cub cub structure
 * @param map map structure
 * @return void
 */
void	ft_assign_to_cube(t_cub *cub, t_map *map)
{
	cub->map_array = ft_calloc(map->map_size_y, sizeof(t_tile *));
	if (!cub->map_array)
		ft_error_handle(map, "Error\n", "Can't allocate memory", 1);
	ft_init_cub_array(cub, map);
	cub->map_size.x = map->map_size_x;
	cub->map_size.y = map->map_size_y;
	cub->position.x = map->player_position[0] + 0.5;
	cub->position.y = map->player_position[1] + 0.5;
	cub->floor_c = (map->floor_c[0] << 16) + (map->floor_c[1] << 8)
		+ map->floor_c[2];
	cub->ceiling_c = (map->ceiling_c[0] << 16) + (map->ceiling_c[1] << 8)
		+ map->ceiling_c[2];
	if (map->player_direction[0] == 1)
		cub->orientation = 0;
	else if (map->player_direction[1] == 1)
		cub->orientation = PI_2;
	else if (map->player_direction[2] == 1)
		cub->orientation = PI;
	else if (map->player_direction[3] == 1)
		cub->orientation = 3 * PI_2;

	
	cub->frames = 0;
	ft_keys_init(&cub->keys);
	if (ft_mlx_init(cub))
	{
		// Precedents are not freed ==>> Memory leaks possible
		ft_game_quit(cub);
		return ;
	}

	cub->minimap = BONUS;
	cub->info = FALSE;

	// cub->border_c = 0xFFCCCCCC;
	cub->border_c = 0;


	for (int i = 0; i < 128; i++)
	{
		cub->textures[i].empty = TRUE;
		cub->textures[i].no = NULL;
		cub->textures[i].no_anim_count = 0;
		cub->textures[i].no_anim_num = 0;
		cub->textures[i].no_anim = TRUE;
		cub->textures[i].so = NULL;
		cub->textures[i].so_anim_count = 0;
		cub->textures[i].so_anim_num = 0;
		cub->textures[i].so_anim = TRUE;
		cub->textures[i].we = NULL;
		cub->textures[i].we_anim_count = 0;
		cub->textures[i].we_anim_num = 0;
		cub->textures[i].we_anim = TRUE;
		cub->textures[i].ea = NULL;
		cub->textures[i].ea_anim_count = 0;
		cub->textures[i].ea_anim_num = 0;
		cub->textures[i].ea_anim = TRUE;
		cub->textures[i].anim_delay = 30;
		cub->textures[i].anim_counter = 0;
		cub->textures[i].map_color = 0x00000000;
	}

	
	for (int i = 0; i < 128; i++)
	{
		if (map->text[i].no)
		{
			cub->textures[i].empty = FALSE;
			cub->textures[i].no = ft_calloc(2, sizeof(t_frame));
			cub->textures[i].no_anim_count = 1;
			cub->textures[i].no[0] = ft_load_texture(cub, map->text[i].no);
			if (cub->textures[i].no[0].img == NULL)
			{
				// Precedents are not freed ==>> Memory leaks possible
				ft_error_handle(map, "Error\n", "Can't load texture", 1);
			}
		}
		if (map->text[i].so)
		{
			cub->textures[i].empty = FALSE;
			cub->textures[i].so = ft_calloc(2, sizeof(t_frame));
			cub->textures[i].so_anim_count = 1;
			cub->textures[i].so[0] = ft_load_texture(cub, map->text[i].so);
			if (cub->textures[i].so[0].img == NULL)
			{
				// Precedents are not freed ==>> Memory leaks possible
				ft_error_handle(map, "Error\n", "Can't load texture", 1);
			}
		}
		if (map->text[i].we)
		{
			cub->textures[i].empty = FALSE;
			cub->textures[i].we = ft_calloc(2, sizeof(t_frame));
			cub->textures[i].we_anim_count = 1;
			cub->textures[i].we[0] = ft_load_texture(cub, map->text[i].we);
			if (cub->textures[i].we[0].img == NULL)
			{
				// Precedents are not freed ==>> Memory leaks possible
				ft_error_handle(map, "Error\n", "Can't load texture", 1);
			}
		}
		if (map->text[i].ea)
		{
			cub->textures[i].empty = FALSE;
			cub->textures[i].ea = ft_calloc(2, sizeof(t_frame));
			cub->textures[i].ea_anim_count = 1;
			cub->textures[i].ea[0] = ft_load_texture(cub, map->text[i].ea);
			if (cub->textures[i].ea[0].img == NULL)
			{
				// Precedents are not freed ==>> Memory leaks possible
				ft_error_handle(map, "Error\n", "Can't load texture", 1);
			}
		}
		cub->textures[i].map_color = map->text[i].mp;
	}
}

/**
 * @brief Initialize the keys structure.
 * 
 * @note	Point: avoid `uninitialized values` errors.
 * 
 * @param keys 	The keys structure
*/
static void	ft_keys_init(t_keys *keys)
{
	keys->forward = FALSE;
	keys->backward = FALSE;
	keys->rot_left = FALSE;
	keys->rot_right = FALSE;
}
