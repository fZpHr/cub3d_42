/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:53:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/12 20:45:50 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_find_player_position(t_map *cube)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < cube->map_size_y)
	{
		while (cube->map_array[i][j] != '\0')
		{
			if (cube->map_array[i][j] == 'N' || cube->map_array[i][j] == 'S'
				|| cube->map_array[i][j] == 'W' || cube->map_array[i][j] == 'E')
			{
				cube->player_position[0] = j;
				cube->player_position[1] = i;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (cube->player_position[0] == 0 && cube->player_position[1] == 0)
		ft_error_handle("Error\n", "No player position", 1);
}

void	ft_check_wall(t_map *cube, int x, int y)
{
	if (y < 0 || y >= cube->map_size_y|| x < 0 || x >= cube->map_size_x)
	{
		ft_free_array(cube->map_array);
		ft_error_handle("Error\n", "Map not close with wall", 1);
	}
	else if (cube->map_array[y][x] == '1' || cube->map_array[y][x] == 'V')
		return ;
	if (y < 0 || y >= cube->map_size_y|| x < 0 || x >= cube->map_size_x)
	{
		ft_free_array(cube->map_array);
		ft_error_handle("Error\n", "Map not close with wall", 1);
	}
 	else if (cube->map_array[y][x] == 'A')
	{
		ft_free_array(cube->map_array);
		ft_error_handle("Error\n", "Map not close with wall", 1);
	}
	cube->map_array[y][x] = 'V';
	ft_check_wall(cube, x + 1, y);
	ft_check_wall(cube, x - 1, y);
	ft_check_wall(cube, x, y + 1);
	ft_check_wall(cube, x, y - 1);
}

void ft_player_direction(t_map *cube, char c)
{
	if (cube->player_direction[0] == 1 || cube->player_direction[1] == 1
		|| cube->player_direction[2] == 1 || cube->player_direction[3] == 1)
		ft_error_handle("Error\n", "Multiple player position", 1);
	if (c == 'N')
		cube->player_direction[0] = 1;
	else if (c == 'S')
		cube->player_direction[1] = 1;
	else if (c == 'W')
		cube->player_direction[2] = 1;
	else if (c == 'E')
		cube->player_direction[3] = 1;
}

void	ft_check_map_content(t_map *cube, int fd)
{
	char	*line;
	int		i;
	int count_tmp_x;

	i = 0;
	count_tmp_x = 0;
	line = get_next_line(fd);
	while(line)
	{
		ft_skip_spaces(line, &i);
		if (line[i] == '\n' && line[i + 1] == '\0')
			cube->map_position++;
		else
		{
			cube->map_size_y++;
			while(line[i])
			{
				count_tmp_x++;
				if (line[i] == '\n' && line[i + 1] != '\0')
				{
					free(line);
					ft_error_handle("Error\n", "Invalid map", 1);
				}
				else if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != 'N'
					&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E' && line[i] != ' ' && line[i] != '\n')
				{
					free(line);
					ft_error_handle("Error\n", "Invalid map", 1);
				}
				if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
					ft_player_direction(cube, line[i]);
				i++;
			}
			if (count_tmp_x > cube->map_size_x)
				cube->map_size_x = count_tmp_x;
			count_tmp_x = 0;
		}
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
	close(fd);
}
