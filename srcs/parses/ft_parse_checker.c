/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:35:34 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/17 10:01:11 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_print_parsing(t_map *map, t_cub *cub)
{
	int	i;

	i = 0;
	printf("no = %s\n", map->no);
	printf("so = %s\n", map->so);
	printf("we = %s\n", map->we);
	printf("ea = %s\n", map->ea);
	printf("\n");
	printf("floor_color = %d, %d, %d\n", map->floor_c[0], map->floor_c[1],
		map->floor_c[2]);
	printf("ceiling_color = %d, %d, %d\n", map->ceiling_c[0], map->ceiling_c[1],
		map->ceiling_c[2]);
	printf("\n");
	printf("map_size_x = %d\n", map->map_size_x);
	printf("map_size_y = %d\n", map->map_size_y);
	printf("player_position = %d, %d\n", map->player_position[0],
		map->player_position[1]);
	printf("player_direction = %d, %d, %d, %d\n", map->player_direction[0],
		map->player_direction[1], map->player_direction[2],
		map->player_direction[3]);
	printf("\n");
	printf("current map :\n");
	while (i < map->map_size_y)
	{
		printf("%s\n", map->map_array[i]);
		i++;
	}
	printf("\n");
	printf("copy map, fill :\n");
	i = 0;
	while (i < map->map_size_y)
	{
		printf("%s\n", map->map_array_copy[i]);
		i++;
	}
	printf("\n");
	printf("assign to cub :\n");
	printf("\n");
	printf("cub, map size x = %d\n", cub->map_size.x);
	printf("cub, map size y = %d\n", cub->map_size.y);
	printf("cub, position x = %f\n", cub->position.x);
	printf("cub, position y = %f\n", cub->position.y);
	printf("cub, floor color = %d\n", cub->floor_c);
	printf("cub, ceiling color = %d\n", cub->ceiling_c);
	printf("cub, player orientation PI = %f\n", cub->orientation);
	printf("\n");
	// printf("no img = %p\n", cub->no.img);
	// printf("no addr = %p\n", cub->no.img);
	// printf("no bits_per_pixel = %d\n", cub->no.bits_per_pixel);
	// printf("line_size = %d\n", cub->no.line_size);
	// printf("no width = %d\n", cub->no.width);
	// printf("no height = %d\n", cub->no.height);
	// printf("endian = %d\n", cub->no.endian);
	// printf("\n");
	// printf("so img = %p\n", cub->so.img);
	// printf("so addr = %p\n", cub->so.img);
	// printf("so bits_per_pixel = %d\n", cub->so.bits_per_pixel);
	// printf("line_size = %d\n", cub->so.line_size);
	// printf("so width = %d\n", cub->so.width);
	// printf("so height = %d\n", cub->so.height);
	// printf("endian = %d\n", cub->so.endian);
	// printf("\n");
	// printf("we img = %p\n", cub->we.img);
	// printf("we addr = %p\n", cub->we.img);
	// printf("we bits_per_pixel = %d\n", cub->we.bits_per_pixel);
	// printf("line_size = %d\n", cub->we.line_size);
	// printf("we width = %d\n", cub->we.width);
	// printf("we height = %d\n", cub->we.height);
	// printf("endian = %d\n", cub->we.endian);
	// printf("\n");
	// printf("ea img = %p\n", cub->ea.img);
	// printf("ea addr = %p\n", cub->ea.img);
	// printf("ea bits_per_pixel = %d\n", cub->ea.bits_per_pixel);
	// printf("line_size = %d\n", cub->ea.line_size);
	// printf("ea width = %d\n", cub->ea.width);
	// printf("ea height = %d\n", cub->ea.height);
	// printf("endian = %d\n", cub->ea.endian);
}

/**

	* @brief Initialize the map struct and
				parse the map file then assign to the cub struct
 *
 * @param cube cub struct
 * @param ac number of arguments
 * @param av arguments
 * @return void
 */
void	ft_parse_checker(t_cub *cube, int ac, char **av)
{
	t_map	map;

	ft_init(&map);
	ft_check_args(ac);
	ft_check_map_file(&map, av[1]);
	ft_map_into_array(&map, av[1]);
	ft_find_player_position(&map);
	ft_cp_array(&map);
	ft_check_wall(&map, map.player_position[0], map.player_position[1]);
	ft_assign_to_cube(cube, &map);
	test_print_parsing(&map, cube);
	ft_free_array(map.map_array);
	ft_free_array(map.map_array_copy);
	free(map.no);
	free(map.so);
	free(map.we);
	free(map.ea);
}
