/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:39:56 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/18 22:27:11 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the map is close with wall, with flood fill algorithm
 *
 * @param map struct of the map
 * @param x position of the player x in the map
 * @param y position of the player y in the map
 * @return void
 */
void	ft_flood_fill(t_map *map, int x, int y)
{
    if (y < 0 || y >= map->map_size_y || x < 0 || x >= map->map_size_x)
        ft_error_handle(map, "Error\n", "Map not close with wall", 1);
    else if (map->map_array_copy[y][x] == '1'
        || map->map_array_copy[y][x] == 'V')
        return ;
    else if (map->map_array_copy[y][x] == 'A')
        ft_error_handle(map, "Error\n", "Map not close with wall", 1);
    map->map_array_copy[y][x] = 'V';
    ft_flood_fill(map, x + 1, y);
    ft_flood_fill(map, x - 1, y);
    ft_flood_fill(map, x, y + 1);
    ft_flood_fill(map, x, y - 1);
}

void    ft_check_wall(t_map *map)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while(i < map->map_size_y)
    {
        while(j < map->map_size_x)
        {
            if (map->map_array[i][j] == '0')
                  ft_flood_fill(map, j, i);
            j++;
        }
        j = 0;
        i++;
    }
}
