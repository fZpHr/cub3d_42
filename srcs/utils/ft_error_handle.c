/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:03:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/28 18:17:39 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_end(t_map *map, int status)
{
	int	i;
	int	j;

	i = -1;
	while (BONUS && ++i < 128)
	{
		j = MAX_FRAME;
		while (map->text[i].no[0] && --j >= 0)
		{
			free(map->text[i].no[j]);
			free(map->text[i].so[j]);
			free(map->text[i].we[j]);
			free(map->text[i].ea[j]);
		}
	}
	free(map->ea);
	free(map->we);
	free(map->so);
	free(map->no);
	if (map->map_array)
		ft_free_array(&map->map_array);
	if (map->map_array_copy)
		ft_free_array(&map->map_array_copy);
	if (status != -42)
		exit(status);
}

void	ft_error_handle(t_map *map, char *error, char *str, int status)
{
	if (str)
		ft_printf_error("%s%s\n", error, str);
	else
		ft_printf_error("%s\n", error);
	ft_free_end(map, status);
}

void	ft_error_handle_color(t_map *map, char *line)
{
	free(line);
	ft_error_handle(map, "Error\n", "Invalid color content", 1);
}
