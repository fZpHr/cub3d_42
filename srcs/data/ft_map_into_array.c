/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_into_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/14 11:18:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_fill_array(t_map *cube, char *line, int fd, int *j)
{
	int	i;

	i = 0;
	while ((*j) < cube->map_size_y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[i])
		{
			if (line[i] == ' ')
				line[i] = 'A';
			else if (line[i] == '\n')
				line[i] = 'A';
			cube->map_array[(*j)][i] = line[i];
			i++;
		}
		cube->map_array[(*j)][i] = '\0';
		i = 0;
		free(line);
		(*j)++;
	}
}

void	fill_array(t_map *cube, char *map)
{
	char	*line;
	int		fd;
	int		j;
	int		i;

	i = 0;
	j = 0;
	fd = open(map, O_RDONLY);
	while (i < cube->map_position)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	loop_fill_array(cube, line, fd, &j);
	cube->map_array[j] = NULL;
	close(fd);
}

void	ft_map_into_array(t_map *cube, char *map)
{
	int	i;
	int	l;

	i = 0;
	l = cube->map_size_y;
	cube->map_array = (char **)ft_malloc(sizeof(char *) * (l + 1));
	while (i < l)
	{
		cube->map_array[i] = (char *)malloc(sizeof(char)
				* cube->map_size_x + 1);
		if (!cube->map_array[i])
		{
			while (i >= 0)
			{
				free(cube->map_array[i]);
				i--;
			}
			free(cube->map_array);
			ft_error_handle(cube, "Error\n", "Malloc failed", 1);
		}
		i++;
	}
	fill_array(cube, map);
}
