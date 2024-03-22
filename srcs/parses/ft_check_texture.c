/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:35:02 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/22 16:31:22 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_handle_texture(t_map *map, char *line, int i)
{
	if (ft_acces_texture(line, i) == 1)
	{
		free(line);
		ft_error_handle(map, "Error\n", "Invalid texture path", 1);
	}
}

void	ft_check_color(t_map *map, char *line, int *i, int *color)
{
	color[0] = ft_atoi(line + (*i));
	while ((line[(*i)] >= '0' && line[(*i)] <= '9') || line[(*i)] == ' ')
		(*i)++;
	if (line[(*i)] != ',')
		ft_error_handle_color(map, line);
	(*i)++;
	color[1] = ft_atoi(line + (*i));
	while ((line[(*i)] >= '0' && line[(*i)] <= '9') || line[(*i)] == ' ')
		(*i)++;
	if (line[(*i)] != ',')
		ft_error_handle_color(map, line);
	(*i)++;
	if (line[(*i)] == '\n' || line[(*i)] == '\0')
		ft_error_handle_color(map, line);
	color[2] = ft_atoi(line + (*i));
	while ((line[(*i)] >= '0' && line[(*i)] <= '9') || line[(*i)] == ' ')
		(*i)++;
	if ((line[(*i)] != '\n' && line[(*i + 1)] != '\0') || line[(*i)] != '\0'
		|| line[(*i)] == ' ')
		ft_error_handle_color(map, line);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		ft_error_handle_color(map, line);
}

void	ft_select_texture(t_map *map, char *line, int *i, int select)
{
	(*i) = (*i) + 2;
	if (select == 1)
	{
		ft_skip_spaces(line, i, NULL);
		ft_handle_texture(map, line, *i);
		map->no = ft_strdup(line + *i);
	}
	else if (select == 2)
	{
		ft_skip_spaces(line, i, NULL);
		ft_handle_texture(map, line, *i);
		map->so = ft_strdup(line + *i);
	}
	else if (select == 3)
	{
		ft_skip_spaces(line, i, NULL);
		ft_handle_texture(map, line, *i);
		map->we = ft_strdup(line + *i);
	}
	else if (select == 4)
	{
		ft_skip_spaces(line, i, NULL);
		ft_handle_texture(map, line, *i);
		map->ea = ft_strdup(line + *i);
	}
}

void	ft_select_color(t_map *map, char *line, int *i, int select)
{
	(*i)++;
	if (select == 1)
	{
		ft_skip_spaces(line, i, NULL);
		ft_check_color(map, line, i, map->floor_c);
	}
	else if (select == 2)
	{
		ft_skip_spaces(line, i, NULL);
		ft_check_color(map, line, i, map->ceiling_c);
	}
}

/**
 * @brief Check if the line is a texture or a color
 *
 * @param map struct of the map
 * @param line line to check send by gnl, can be a texture, a color or nothing
 * @return int 0 if the line is empty, 1 if the line is not a texture or a color
 */
int	ft_check_texture(t_map *map, char *line)
{
	int	i;

	i = 0;
	ft_skip_spaces(line, &i, NULL);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' '
		&& map->no == NULL)
		ft_select_texture(map, line, &i, 1);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' '
		&& map->so == NULL)
		ft_select_texture(map, line, &i, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' '
		&& map->we == NULL)
		ft_select_texture(map, line, &i, 3);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' '
		&& map->ea == NULL)
		ft_select_texture(map, line, &i, 4);
	else if (line[i] == 'F' && line[i + 1] == ' ' && map->floor_c[0] == -1)
		ft_select_color(map, line, &i, 1);
	else if (line[i] == 'C' && line[i + 1] == ' ' && map->ceiling_c[0] == -1)
		ft_select_color(map, line, &i, 2);
	else if (line[i] == '\0')
		return (0);
	else
		return (1);
	return (0);
}
