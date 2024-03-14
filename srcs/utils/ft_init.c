/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:22:23 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/14 16:12:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_map *map)
{
	map->map_array = NULL;
	map->map_array_copy = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->floor_c[0] = -1;
	map->ceiling_c[0] = -1;
	map->player_direction[0] = 0;
	map->player_direction[1] = 0;
	map->player_direction[2] = 0;
	map->player_direction[3] = 0;
	map->player_position[0] = 0;
	map->player_position[1] = 0;
	map->map_size_y = 0;
	map->map_size_x = 0;
	map->map_position = 0;
}
