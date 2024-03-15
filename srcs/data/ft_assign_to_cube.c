/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_to_cube.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:37 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/15 20:28:15 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_handle_img(t_cub *cub, t_map *map)
{
	cub->no.img = mlx_xpm_file_to_image(cub->mlx, map->no, &cub->no.width, &cub->no.height);
	if (!cub->no.img)
		return (1);
	cub->so.img = mlx_xpm_file_to_image(cub->mlx, map->so, &cub->so.width, &cub->so.height);
	if (!cub->so.img)
		return (1);
	cub->we.img = mlx_xpm_file_to_image(cub->mlx, map->we, &cub->we.width, &cub->we.height);
	if (!cub->we.img)
		return (1);
	cub->ea.img = mlx_xpm_file_to_image(cub->mlx, map->ea, &cub->ea.width, &cub->ea.height);
	if (!cub->ea.img)
		return (1);
	return (0);
}

int	ft_handle_addr(t_cub *cub)
{
	cub->no.addr = mlx_get_data_addr(cub->no.img, &cub->no.bits_per_pixel, &cub->no.line_size, &cub->no.endian);
	if (!cub->no.addr)
		return (1);
	cub->so.addr = mlx_get_data_addr(cub->so.img, &cub->so.bits_per_pixel, &cub->so.line_size, &cub->so.endian);
	if (!cub->so.addr)
		return (1);
	cub->we.addr = mlx_get_data_addr(cub->we.img, &cub->we.bits_per_pixel, &cub->we.line_size, &cub->we.endian);
	if (!cub->we.addr)
		return (1);
	cub->ea.addr = mlx_get_data_addr(cub->ea.img, &cub->ea.bits_per_pixel, &cub->ea.line_size, &cub->ea.endian);
	if (!cub->ea.addr)
		return (1);
	return (0);
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
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_error_handle(map, "Error\n", "Can't initialize mlx", 1);
	cub->mlx_win = mlx_new_window(cub->mlx, map->map_size_x, map->map_size_y, "cub3d");
	if (!cub->mlx_win)
		ft_error_handle(map, "Error\n", "Can't create window", 1);
	cub->map_array = map->map_array;
	cub->map_size.x = map->map_size_x;
	cub->map_size.y = map->map_size_y;
	cub->position.x = map->player_position[0];
	cub->position.y = map->player_position[1];
	cub->floor_c =  (map->floor_c[0] << 16) + (map->floor_c[1] << 8) + map->floor_c[2];
	cub->ceiling_c = (map->ceiling_c[0] << 16) + (map->ceiling_c[1] << 8) + map->ceiling_c[2];
	if (ft_handle_img(cub, map) != 0)
		ft_error_handle(map, "Error\n", "Can't create img", 1);
	if (ft_handle_addr(cub) != 0)
		ft_error_handle(map, "Error\n", "Can't get data addr", 1);
	if (map->player_direction[0] == 1)
		cub->orientation = 0;
	else if (map->player_direction[1] == 1)
		cub->orientation = M_PI_2;
	else if (map->player_direction[2] == 1)
		cub->orientation = M_PI;
	else if (map->player_direction[3] == 1)
		cub->orientation = 3 * M_PI_2;
}
