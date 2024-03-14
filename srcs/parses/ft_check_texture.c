/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:35:02 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/14 11:17:40 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_handle_texture(t_map *cube, char *line, int i)
{
	if (line[i] != '.')
	{
		free(line);
		ft_error_handle(cube, "Error\n", "Invalid map texture name", 1);
	}
	else
		ft_acces_texture(cube, line, i);
}

void	ft_check_color(t_map *cube, char *line, int *i, int *color)
{
	color[0] = ft_atoi(line + (*i));
	while (line[(*i)] >= '0' && line[(*i)] <= '9')
		(*i)++;
	if (line[(*i)] != ',')
		ft_error_handle_color(cube, line);
	(*i)++;
	color[1] = ft_atoi(line + (*i));
	while (line[(*i)] >= '0' && line[(*i)] <= '9')
		(*i)++;
	if (line[(*i)] != ',')
		ft_error_handle_color(cube, line);
	(*i)++;
	color[2] = ft_atoi(line + (*i));
	(*i)++;
	if (line[(*i)] == ' ')
		ft_skip_spaces(line, i, NULL);
	if (line[(*i)] != '\n' && line[(*i + 1)] != '\0')
		ft_error_handle_color(cube, line);
	while (line[(*i)] >= '0' && line[(*i)] <= '9')
		(*i)++;
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		ft_error_handle_color(cube, line);
}

void	ft_select_texture(t_map *cube, char *line, int *i, int select)
{
	(*i) = (*i) + 2;
	if (select == 1)
	{
		ft_skip_spaces(line, i, NULL);
		ft_handle_texture(cube, line, *i);
		cube->no = ft_strdup(line + *i);
	}
	else if (select == 2)
	{
		ft_skip_spaces(line, i, NULL);
		ft_handle_texture(cube, line, *i);
		cube->so = ft_strdup(line + *i);
	}
	else if (select == 3)
	{
		ft_skip_spaces(line, i, NULL);
		ft_handle_texture(cube, line, *i);
		cube->we = ft_strdup(line + *i);
	}
	else if (select == 4)
	{
		ft_skip_spaces(line, i, NULL);
		ft_handle_texture(cube, line, *i);
		cube->ea = ft_strdup(line + *i);
	}
}

void	ft_select_color(t_map *cube, char *line, int *i, int select)
{
	(*i)++;
	if (select == 1)
	{
		ft_skip_spaces(line, i, NULL);
		ft_check_color(cube, line, i, cube->floor_c);
	}
	else if (select == 2)
	{
		ft_skip_spaces(line, i, NULL);
		ft_check_color(cube, line, i, cube->ceiling_c);
	}
}

int	ft_check_texture(t_map *cube, char *line)
{
	int	i;

	i = 0;
	ft_skip_spaces(line, &i, NULL);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' '
		&& cube->no == NULL)
		ft_select_texture(cube, line, &i, 1);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' '
		&& cube->so == NULL)
		ft_select_texture(cube, line, &i, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' '
		&& cube->we == NULL)
		ft_select_texture(cube, line, &i, 3);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' '
		&& cube->ea == NULL)
		ft_select_texture(cube, line, &i, 4);
	else if (line[i] == 'F' && line[i + 1] == ' ' && cube->floor_c[0] == -1)
		ft_select_color(cube, line, &i, 1);
	else if (line[i] == 'C' && line[i + 1] == ' ' && cube->ceiling_c[0] == -1)
		ft_select_color(cube, line, &i, 2);
	else if (line[i] == '\0')
		return (0);
	else
		return (1);
	return (0);
}
