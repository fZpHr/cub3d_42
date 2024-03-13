/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:03:58 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/13 16:53:17 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_end(t_map *cube, int status)
{
	int	i;

	i = 3;
	if (cube->ea)
		free(cube->ea);
	if (cube->we)
		free(cube->we);
	if (cube->so)
		free(cube->so);
	if (cube->no)
		free(cube->no);
	if (cube->map_array)
		ft_free_array(cube->map_array);
	if (cube->map_array_copy)
		ft_free_array(cube->map_array_copy);
	while (i <= 1023)
		close(i++);
	exit(status);
}

void	ft_error_handle(t_map *cube, char *error, char *str, int status)
{
	if (str)
		ft_printf_error("%s%s\n", error, str);
	else
		ft_printf_error("%s\n", error);
	ft_free_end(cube, status);
}

void	ft_error_handle_color(t_map *cube, char *line)
{
	free(line);
	ft_error_handle(cube, "Error\n", "Invalid color content", 1);
}
