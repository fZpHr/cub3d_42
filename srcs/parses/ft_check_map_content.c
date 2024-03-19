/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:53:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/19 17:42:13 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_handle_bonus(t_map *map, char *line, int *i)
{
	if (BONUS)
	{
		if (line[(*i)] != '2' && line[(*i)] != '3' && line[(*i)] != '4'
			&& line[(*i)] != 'X')
		{
			free(line);
			ft_error_handle(map, "Error\n", "Invalid map", 1);
		}
	}
	else
	{
		free(line);
		ft_error_handle(map, "Error\n", "Invalid map", 1);
	}
}

/**
 * @brief Find the player position in the map, and store it in the struct
 *
 * @param map struct of the map
 * @return void
 **/
void	ft_find_player_position(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->map_size_y)
	{
		while (map->map_array[i][j] != '\0')
		{
			if (map->map_array[i][j] == 'N' || map->map_array[i][j] == 'S'
				|| map->map_array[i][j] == 'W' || map->map_array[i][j] == 'E')
			{
				map->player_position[0] = j;
				map->player_position[1] = i;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (map->player_position[0] == 0 && map->player_position[1] == 0)
		ft_error_handle(map, "Error\n", "No player position", 1);
}

void	ft_player_direction(t_map *map, char *line, int i)
{
	if (map->player_direction[0] == 1 || map->player_direction[1] == 1
		|| map->player_direction[2] == 1 || map->player_direction[3] == 1)
	{
		free(line);
		ft_error_handle(map, "Error\n", "Multiple player position", 1);
	}
	if (line[i] == 'E')
		map->player_direction[0] = 1;
	else if (line[i] == 'S')
		map->player_direction[1] = 1;
	else if (line[i] == 'W')
		map->player_direction[2] = 1;
	else if (line[i] == 'N')
		map->player_direction[3] = 1;
}

void	else_map_content(t_map *map, char *line, int *i, int *count_tmp_x)
{
	map->map_size_y++;
	while (line[(*i)])
	{
		(*count_tmp_x)++;
		if (line[(*i)] == '\n' && line[(*i) + 1] != '\0')
		{
			free(line);
			ft_error_handle(map, "Error\n", "Invalid map", 1);
		}
		else if (line[(*i)] != '0' && line[(*i)] != '1'
			&& line[(*i)] != 'N' && line[(*i)] != 'S' && line[(*i)] != 'W'
			&& line[(*i)] != 'E' && line[(*i)] != ' ' && line[(*i)] != '\n')
			ft_handle_bonus(map, line, i);
		if (line[(*i)] == 'N' || line[(*i)] == 'S' || line[(*i)] == 'W'
			|| line[(*i)] == 'E')
			ft_player_direction(map, line, (*i));
		(*i)++;
	}
	if ((*count_tmp_x) > map->map_size_x)
		map->map_size_x = (*count_tmp_x);
}

/**
 * @brief Check if the map content is valid
 *
 * @param map struct of the map
 * @param fd file descriptor of the map, already used by gnl
 * @return void
 */
void	ft_check_map_content(t_map *map, int fd)
{
	char	*line;
	int		i;
	int		count_tmp_x;
	int		limiter;

	i = 0;
	count_tmp_x = 0;
	limiter = 0;
	line = get_next_line(fd);
	while (line)
	{
		ft_skip_spaces(line, &i, &count_tmp_x);
		if (line[i] == '\n' && line[i + 1] == '\0' && limiter == 0)
			map->map_position++;
		else
		{
			limiter = 1;
			else_map_content(map, line, &i, &count_tmp_x);
		}
		count_tmp_x = 0;
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
	close(fd);
}
