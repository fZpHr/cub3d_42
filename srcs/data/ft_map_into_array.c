/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_into_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/28 22:08:50 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Handle the line of the map, replace spaces and newlines by 'A'
 *
 * @param map 	struct of the map
 * @param line 	line to handle
 * @param j 	position of the line in the map
 * @param i 	position of the character in the line
 */
void	handle_line(t_map *map, char *line, int *j, int *i)
{
	if (line[(*i)] == ' ' || line[(*i)] == '\n')
		line[(*i)] = 'A';
	map->map_array[(*j)][(*i)] = line[(*i)];
	(*i)++;
}

void	loop_fill_array(t_map *map, char *line, int fd, int *j)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while ((*j) < map->map_size_y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (size < map->map_size_x)
		{
			if (line[i] != '\0')
				handle_line(map, line, j, &i);
			else
				map->map_array[(*j)][size] = 'A';
			size++;
		}
		map->map_array[(*j)][size] = '\0';
		size = 0;
		i = 0;
		free(line);
		(*j)++;
	}
}

void	fill_array(t_map *map, char *map_file)
{
	char	*line;
	int		fd;
	int		j;
	int		i;

	i = 0;
	j = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_error_handle(map, "Error\n", "Invalid map file", 1);
		return ;
	}
	while (i < map->map_position)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	loop_fill_array(map, line, fd, &j);
	map->map_array[j] = NULL;
	close(fd);
}

/**
 * @brief Fill the map array with the position of the map in the file,
 * 			and replace spaces and newlines by 'A'
 *
 * @param map 		struct of the map
 * @param map_file 	name of the file
 */
void	ft_map_into_array(t_map *map, char *map_file)
{
	int	i;
	int	l;

	i = 0;
	l = map->map_size_y;
	map->map_array = (char **)ft_malloc(sizeof(char *) * (l + 1));
	while (i < l)
	{
		map->map_array[i] = (char *)malloc(sizeof(char) * map->map_size_x + 1);
		if (!map->map_array[i])
		{
			while (i >= 0)
			{
				free(map->map_array[i]);
				i--;
			}
			free(map->map_array);
			ft_error_handle(map, "Error\n", "Malloc failed", 1);
		}
		i++;
	}
	fill_array(map, map_file);
}
