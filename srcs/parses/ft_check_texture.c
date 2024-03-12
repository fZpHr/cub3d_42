/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:35:02 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/12 20:21:05 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

void	ft_handle_texture(char *line, int i)
{
	int fd;

	if (line[i] != '.')
		ft_error_handle("Error\n", "Invalid map", 1);
	else
	{
		fd = open(line + i, O_RDONLY);
		if (fd < 0)
			ft_error_handle("Error\n", "Invalid texture file", 1);
		else
			close(fd);
	}
}

void	ft_check_color(char *line, int *i, int *color)
{
	color[0] = ft_atoi(line + (*i));
	while (line[(*i)] >= '0' && line[(*i)] <= '9')
		(*i)++;
	if (line[(*i)] != ',')
		ft_error_handle("Error\n", "Invalid map", 1);
	(*i)++;
	color[1] = ft_atoi(line + (*i));
	while (line[(*i)] >= '0' && line[(*i)] <= '9')
		(*i)++;
	if (line[(*i)] != ',')
		ft_error_handle("Error\n", "Invalid map", 1);
	(*i)++;
	color[2] = ft_atoi(line + (*i));
	while (line[(*i)] >= '0' && line[(*i)] <= '9')
		(*i)++;
	if (color[0] < 0 || color[0] > 255
		|| color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		ft_error_handle("Error\n", "Invalid map", 1);
}

void	ft_select_texture(t_map *cube, char *line, int *i, int select)
{
	(*i) = (*i) + 2;
	if (select == 1)
	{
		ft_skip_spaces(line, i);
		ft_handle_texture(line, *i);
		cube->no = ft_strdup(line + *i);
	}
	else if (select == 2)
	{
		ft_skip_spaces(line, i);
		ft_handle_texture(line, *i);
		cube->so = ft_strdup(line + *i);
	}
	else if (select == 3)
	{
		ft_skip_spaces(line, i);
		ft_handle_texture(line, *i);
		cube->we = ft_strdup(line + *i);
	}
	else if (select == 4)
	{
		ft_skip_spaces(line, i);
		ft_handle_texture(line, *i);
		cube->ea = ft_strdup(line + *i);
	}
}

void	ft_select_color(t_map *cube, char *line, int *i, int select)
{
	(*i)++;
	if (select == 1)
	{
		ft_skip_spaces(line, i);
		ft_check_color(line, i, cube->floor);
	}
	else if (select == 2)
	{
		ft_skip_spaces(line, i);
		ft_check_color(line, i, cube->ceiling);
	}
}	

void	ft_check_texture(t_map *cube, char *line)
{
	int i;

	i = 0;
	ft_skip_spaces(line, &i);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ' && cube->no == NULL)
		ft_select_texture(cube, line, &i, 1);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ' && cube->so == NULL)
		ft_select_texture(cube, line, &i, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ' && cube->we == NULL)
		ft_select_texture(cube, line, &i, 3);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ' && cube->ea == NULL)
		ft_select_texture(cube, line, &i, 4);
	else if (line[i] == 'F' && line[i + 1] == ' ' && cube->floor[0] == -1)
		ft_select_color(cube, line, &i, 1);
	else if (line[i] == 'C' && line[i + 1] == ' ' && cube->ceiling[0] == -1)
		ft_select_color(cube, line, &i, 2);
	else if (line[i] == '\0')
		return ;
	else
		ft_error_handle("Error\n", "Invalid map", 1);
}
