/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:53:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/11 20:04:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	resolver_map(t_map *cube, int x, int y)
{
	if (y < 0 || y >= cube->count_y || x < 0 || x >= cube->count_x
		|| cube->map_array[y][x] == '1' || cube->map_array[y][x] == 'V')
		return ;
	if (cube->map_array[y][x] == 'C')
		cube->check_c++;
	if (cube->map_array[y][x] == 'E')
		cube->check_e++;
	cube->map_array[y][x] = 'V';
	resolver_map(cube, x + 1, y);
	resolver_map(cube, x - 1, y);
	resolver_map(cube, x, y + 1);
	resolver_map(cube, x, y - 1);
}

/* int	check_map(t_map *cube)
{
	int	i;
	int	j;
	int	i;
	int	j;
	int	i;
	int	j;

	if (cube->count_y == cube->count_x)
		return (0);
	resolver_map(cube, (cube->img_player_x / 90), (cube->img_player_y / 90));
	if (cube->check_c == cube->count_c && cube->check_e > 0
		&& cube->check_c > 0)
		return (1);
	return (0);
} */
int	check_wall(t_map *cube)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (i < cube->count_x)
	{
		if (cube->map_array[0][i] != '1')
			return (0);
		if (cube->map_array[cube->count_y - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < cube->count_y)
	{
		while (cube->map_array[i][j])
			j++;
		if (j != cube->count_x + 1)
			return (0);
		if (cube->map_array[i][0] != '1')
			return (0);
		if (cube->map_array[i][cube->count_x - 1] != '1')
			return (0);
		i++;
		j = 0;
	}
	return (1);
}
