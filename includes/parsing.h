/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:00:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/03/14 15:02:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef struct s_map
{
	char		**map_array;
	char		**map_array_copy;
	int			map_position;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor_c[3];
	int			ceiling_c[3];
	float		player_direction;
	t_pos		player_position;
	t_ipos		map_size;
	int			map_position;
}	t_map;

void	ft_acces_texture(t_map *cube, char *line, int i);
void	ft_check_wall(t_map *cube, int x, int y);
void	ft_find_player_position(t_map *cube);
void	ft_check_args(int ac);
void	ft_check_map_file(t_map *cube, char *map);
int		ft_check_texture(t_map *cube, char *line);
void	ft_check_map_content(t_map *cube, int fd);

#endif
