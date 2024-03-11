/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:00:16 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/11 20:14:11 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_loop_map(char *line, int fd)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (line)
	{
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\n' && line[i] != '1'
				&& line[i] != '0' && line[i] != '2' && line[i] != 'N'
				&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
				ft_error_handle("Error\n", "Invalid map", 1);
			if (line[i] == '\n')
				n++;
			i++;
		}
		if (n > 1)
			ft_error_handle("Error\n", "Invalid map", 1);
		n = 0;
		i = 0;
		free(line);
		line = get_next_line(fd);
	}
}

void	ft_check_map(char *map)
{
	int		fd;
	char	*line;

	if (ft_strcmp(map + (ft_strlen(map) - 4), ".cub") != 0)
		ft_error_handle("Invalid file format : ", map, 1);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error_handle("Invalid file : ", map, 1);
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		close(fd);
		ft_error_handle("Error\n", "Empty file", 1);
	}
	else
	{
		ft_loop_map(line, fd);
		close(fd);
	}
}
