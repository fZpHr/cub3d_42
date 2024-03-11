/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_into_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:56:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/11 20:26:15 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skip_intro(char *line, int fd)
{
	while (line[0] == ' ' || line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
}
void	count_xy(t_map *cube)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("map.ber", O_RDONLY);
	line = get_next_line(fd);
	cube->count_x = 0;
	cube->count_y = 0;
	i = 0;
	while (line)
	{
		while (line[i])
		{
			cube->count_x++;
			i++;
		}
		cube->count_y++;
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
	free(line);
	close(fd);
	cube->count_x /= cube->count_y;
}

void	fill_array(t_map *cube)
{
	char	*line;
	int		fd;
	int		j;
	int		i;

	i = 0;
	j = 0;
	fd = open("map.ber", O_RDONLY);
	while (j < cube->count_y)
	{
		line = get_next_line(fd);
		while (line[i])
		{
			cube->map_array[j][i] = line[i];
			i++;
		}
		cube->map_array[j][i] = '\0';
		i = 0;
		free(line);
		j++;
	}
	close(fd);
}

void	map_into_array(t_map *cube)
{
	int i;

	i = 0;
	cube->map_array = (char **)malloc(sizeof(char *) * cube->count_y);
	while (i < cube->count_y)
	{
		cube->map_array[i] = (char *)malloc(sizeof(char *) * cube->count_x + 1);
		if (!cube->map_array[i])
		{
			while (i >= 0)
			{
				free(cube->map_array[i]);
				i--;
			}
			return ;
		}
		i++;
	}
	fill_array(cube);
}