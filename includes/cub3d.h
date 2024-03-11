/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/03/11 16:47:27 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/11 16:47:27 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../MacroLibX/includes/mlx.h>
# include <../libft/libft.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_map
{
	int count_x;
	int count_y;
	char **map_array;
	int check_c;
	int check_e;
} t_map;

// PARSES

void	ft_check_args(int ac);
void	ft_check_map(char *map);

// UTILS

void	ft_error_handle(char *error, char *str, int status);

// DATA

void	map_into_array(t_map *cube);

#endif