/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_to_cube.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:37 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:33 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	ft_keys_init(t_keys *keys);
static void	ft_init_cub_array(t_cub *cub, t_map *map);
static void	ft_assign_map(t_cub *cub, t_map *map);
static void	ft_assign_player(t_cub *cub, t_map *map);

/**
 * @brief Assigns the map data to the cub structure
 *
 * @param cub 	cub structure
 * @param map 	map structure
 */
void	ft_assign_to_cube(t_cub *cub, t_map *map)
{
	ft_assign_map(cub, map);
	ft_assign_player(cub, map);
	ft_keys_init(&cub->keys);
	if (ft_mlx_init(cub))
	{
		ft_error_handle(map, NULL, NULL, -42);
		ft_game_quit(cub, 1);
	}
	ft_assign_vars(cub);
	if (!BONUS)
		ft_assign_textures(cub, map);
	else
		ft_assign_textures_bonus(cub, map);
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
	keys->left = FALSE;
	keys->right = FALSE;
	keys->rot_left = FALSE;
	keys->rot_right = FALSE;
}

static void	ft_init_cub_array(t_cub *cub, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_size_y)
	{
		cub->map_array[i] = ft_calloc(map->map_size_x, sizeof(t_tile));
		if (!cub->map_array[i])
		{
			ft_error_handle(map, "Error\n", "Can't allocate memory", -42);
			ft_game_quit(cub, 1);
		}
		j = 0;
		while (j < map->map_size_x)
		{
			cub->map_array[i][j].type = map->map_array[i][j];
			j++;
		}
		i++;
	}
}

static void	ft_assign_map(t_cub *cub, t_map *map)
{
	cub->map_array = ft_calloc(map->map_size_y, sizeof(t_tile *));
	if (!cub->map_array)
		ft_error_handle(map, "Error\n", "Can't allocate memory", 1);
	ft_init_cub_array(cub, map);
	cub->map_size.x = map->map_size_x;
	cub->map_size.y = map->map_size_y;
	cub->floor_c = (map->floor_c[0] << 16) + (map->floor_c[1] << 8)
		+ map->floor_c[2];
	cub->ceiling_c = (map->ceiling_c[0] << 16) + (map->ceiling_c[1] << 8)
		+ map->ceiling_c[2];
}

static void	ft_assign_player(t_cub *cub, t_map *map)
{
	cub->position.x = map->player_position[0] + 0.5;
	cub->position.y = map->player_position[1] + 0.5;
	if (map->player_direction[0] == 1)
		cub->orientation = 0;
	else if (map->player_direction[1] == 1)
		cub->orientation = PI_2;
	else if (map->player_direction[2] == 1)
		cub->orientation = PI;
	else if (map->player_direction[3] == 1)
		cub->orientation = 3 * PI_2;
}
