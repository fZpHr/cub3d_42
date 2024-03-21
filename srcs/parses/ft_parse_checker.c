/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:35:34 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/21 07:54:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_after_check(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (BONUS && ++i < 128)
	{
		j = MAX_FRAME;
		while (map->text[i].no[0] && --j >= 0)
		{
			free(map->text[i].no[j]);
			free(map->text[i].so[j]);
			free(map->text[i].we[j]);
			free(map->text[i].ea[j]);
		}
	}
	ft_free_array(map->map_array);
	ft_free_array(map->map_array_copy);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
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
	if (!BONUS)
		ft_check_map_file(&map, av[1]);
	else
		ft_check_map_file_bonus(&map, av[1]);
	ft_map_into_array(&map, av[1]);
	ft_find_player_position(&map);
	ft_cp_array(&map);
	ft_check_wall(&map);
	ft_assign_to_cube(cube, &map);
	ft_free_after_check(&map);
}
