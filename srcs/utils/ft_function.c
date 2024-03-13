/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:24:55 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/13 17:06:06 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_skip_spaces(char *line, int *i, int *count)
{
	if (count == NULL)
	{
		while (line[*i] == ' ')
			(*i)++;
	}
	else
	{
		while (line[*i] == ' ')
		{
			(*i)++;
			(*count)++;
		}
	}
}

void	cut_extra_char(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == '\n')
		str[i - 1] = '\0';
}

void	ft_fill_line(char *line, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		line[i] = 'A';
		i++;
	}
	line[i] = '\0';
}

void	ft_init_array(t_map *cube, int l)
{
	int	j;

	j = 0;
	while (j < l)
	{
		cube->map_array_copy[j] = (char *)malloc(sizeof(char)
				* (cube->map_size_x + 1));
		if (!cube->map_array[j])
		{
			while (j >= 0)
			{
				free(cube->map_array[j]);
				j--;
			}
			free(cube->map_array);
			ft_error_handle(cube, "Error\n", "Malloc failed", 1);
		}
		j++;
	}
}

void	ft_cp_array(t_map *cube)
{
	int	i;
	int	j;
	int	l;

	l = cube->map_size_y;
	j = 0;
	i = 0;
	cube->map_array_copy = (char **)ft_malloc(sizeof(char *) * (l + 1));
	ft_init_array(cube, l);
	while (j < cube->map_size_y)
	{
		i = 0;
		while (cube->map_array[j][i])
		{
			cube->map_array_copy[j][i] = cube->map_array[j][i];
			i++;
		}
		cube->map_array_copy[j][i] = '\0';
		j++;
	}
	cube->map_array_copy[j] = NULL;
}
