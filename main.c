/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:48:24 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/13 19:23:46 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	test_print_parsing(t_map *cube)
{
	int i = 0;
	printf("no = %s\n", cube->no);
	printf("so = %s\n", cube->so);
	printf("we = %s\n", cube->we);
	printf("ea = %s\n", cube->ea);
	printf("\n");
	printf("floor_color = %d, %d, %d\n", cube->floor_c[0], cube->floor_c[1], cube->floor_c[2]);
	printf("ceiling_color = %d, %d, %d\n", cube->ceiling_c[0], cube->ceiling_c[1], cube->ceiling_c[2]);
	printf("\n");
	printf("map_size_x = %d\n", cube->map_size_x);
	printf("map_size_y = %d\n", cube->map_size_y);
	printf("player_position = %d, %d\n", cube->player_position[0], cube->player_position[1]);
	printf("player_direction = %d, %d, %d, %d\n", cube->player_direction[0], cube->player_direction[1], cube->player_direction[2], cube->player_direction[3]);
	printf("\n");
	printf("current map :\n");
	while (i <= cube->map_size_y)
	{
		printf("%s\n", cube->map_array[i]);
		i++;
	}
	printf("\n");
	printf("copy map, fill :\n");
	i = 0;
	while (i <= cube->map_size_y)
	{
		printf("%s\n", cube->map_array_copy[i]);
		i++;
	}
}
int	main(int ac, char **av)
{
	t_map cube;

	ft_init(&cube);
	ft_check_args(ac);
	ft_check_map_file(&cube, av[1]);
	ft_map_into_array(&cube, av[1]);
	ft_find_player_position(&cube);
	ft_cp_array(&cube);
	ft_check_wall(&cube, cube.player_position[0], cube.player_position[1]);

	test_print_parsing(&cube);

	ft_free_array(cube.map_array_copy);
	ft_free_array(cube.map_array);
	free(cube.no);
	free(cube.so);
	free(cube.we);
	free(cube.ea);
	return (0);
}