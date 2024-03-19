/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:24:32 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/19 17:44:05 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the texture extension is valid
 *
 * @param map struct of the map
 * @param line current line of the file, content of the texture path
 * @return void
 */
int	ft_check_extension(char *line)
{
	if (ft_strncmp(line + (ft_strlen(line) - 4), ".xpm", 4) == 0)
		return (0);
	else
		return (1);
}

/**
 * @brief Check if the texture path is valid
 *
 * @param map struct of the map
 * @param line current line of the file, content of the texture path
 * @param i index of the line
 * @return 1 if the texture path is invalid, 0 otherwise
 */
int	ft_acces_texture(char *line, int i)
{
	int	fd;

	fd = open(line + i, __O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		return (1);
	}
	else
	{
		if (ft_check_extension(line) == 1)
			return (1);
		fd = open(line + i, O_RDONLY);
		if (fd < 0)
		{
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}
