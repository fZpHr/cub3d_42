/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:47:27 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/14 11:18:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include "mlx.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

# define PI			3.14159265358979323846
# define PI_2		1.57079632679489661923
# define PI_3		1.04719755119659774615
# define PI_4		0.78539816339744830962
# define PI_6		0.52359877559829887308
# define PI_12		0.26179938779914943654

# ifndef BONUS
/**
 * @brief Bonus mode (`0`: off, `1`: on)
 * 
 * @note	If `BONUS` is `0`, the program will be ignoring bonus adds
 * 			(like collisions, or advanced maps).
*/
#  define BONUS		0
# endif

# ifndef HIDE_MOUSE
/**
 * @brief Hide mouse (`0`: off, `1`: on)
 * 
 * @note	- The hide function of the MLX LEAKS !
 * 			And there is no possibility to either
 * 			free the memory, or to hide the mouse without using it.
 * 
 * @note	---
 * 
 * @note	- By default, the mouse is not hidden. (Valgrind is happy !)
 * 
 * @note	- And when `HIDE_MOUSE` is `1`, the mouse IS hidden.
 * 			(But valgrind is not happy...)
*/
#  define HIDE_MOUSE		0
# endif

/**
 * @brief Name of the window
*/
# define NAME			"Cub3D"

/**
 * @brief Height of the window (in px)
*/
# define HEIGHT			900

/**
 * @brief Width of the window (in px)
*/
# define WIDTH			1200

/**
 * @brief Field of view (in rad)
*/
# define FOV			PI_3

/**
 * @brief Number of rays
*/
# define RAYS			600

/**
 * @brief Walking speed (in px/frame)
*/
# define WALK_SPEED		0.05

/**
 * @brief Rotation speed (in rad/frame)
 * 
 * @brief	- Using KEYS
 * 
 * @note	`PI_12 / 9` is `0.02908882086641849395`.
*/
# define ROT_SPEED		0.02908882086641849395

/**
 * @brief Rotation speed (in rad/frame)
 * 
 * @brief	- Using MOUSE
*/
# define ROT_SPEED_MOUSE	0.00175

typedef unsigned long long	t_ull;

/**
 * @brief Direction type (`NORTH`, `SOUTH`, `WEST`, `EAST`)
*/
typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_direction;

/**
 * @brief Boolean type (`FALSE`: 0, `TRUE`: 1)
*/
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/**
 * @brief Position type (float, float)
*/
typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

/**
 * @brief Integer position type (int, int)
*/
typedef struct s_ipos
{
	int	x;
	int	y;
}	t_ipos;

/**
 * @brief Integer vector3 type (int, int, int)
*/
typedef struct s_ivec3
{
	int	x;
	int	y;
	int	z;
}	t_ivec3;

/**
 * @brief Frame type
 * 
 * @param img 				Pointer to the image
 * @param addr 				Pointer to the address of the content of the image
 * @param bits_per_pixel 	Number of bits per pixel
 * @param line_size 		Number of bytes per line
 * @param width 			Width of the image (in px)
 * @param height 			Height of the image (in px)
 * @param endian 			Endian of the image (0: little, 1: big)
*/
typedef struct s_frame {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		width;
	int		height;
	int		endian;
}	t_frame;

/**
 * @brief Structure for the texture
 * 
 * @param no 			Array of the north texture animation (NULL: transparent)
 * @param so 			Array of the south texture animation (NULL: transparent)
 * @param we 			Array of the west texture animation (NULL: transparent)
 * @param ea 			Array of the east texture animation (NULL: transparent)
 * 
 * @param no_anim_count 		Number of frames of the north texture animation
 * @param so_anim_count 		Number of frames of the south texture animation
 * @param we_anim_count 		Number of frames of the west texture animation
 * @param ea_anim_count 		Number of frames of the east texture animation
 * 
 * @param anim_delay 	Delay between each frame (in frame) (0: no animation)
 * 
 * @param map_color 	Color of the texture on the map (in ARGB format)
 * 						(`0`: transparent)
*/
typedef struct s_texture
{
	t_bool	empty;

	t_frame	*no;
	t_ull	no_anim_count;
	t_ull	no_anim_num;
	t_bool	no_anim;

	t_frame	*so;
	t_ull	so_anim_count;
	t_ull	so_anim_num;
	t_bool	so_anim;

	t_frame	*we;
	t_ull	we_anim_count;
	t_ull	we_anim_num;
	t_bool	we_anim;

	t_frame	*ea;
	t_ull	ea_anim_count;
	t_ull	ea_anim_num;
	t_bool	ea_anim;

	t_ull	anim_delay;
	t_ull	anim_counter;

	int		map_color;
}	t_texture;

/**
 * @brief Structure for the keys
 * 
 * @param forward 		Is the player pressing a forward key ?
 * @param backward 		Is the player pressing a backward key ?
 * @param rot_left 		Is the player pressing a left rotation key ?
 * @param rot_right 	Is the player pressing a right rotation key ?
*/
typedef struct s_keys
{
	t_bool	forward;
	t_bool	backward;
	t_bool	rot_left;
	t_bool	rot_right;
}	t_keys;

typedef struct s_tile
{
	char	type;
	t_bool	is_solid;
}	t_tile;

/**
 * @brief Structure for the game
 * 
 * @param mlx 			Pointer to the mlx instance
 * @param mlx_win 		Pointer to the mlx window
 * @param frame 		Canvas of the game (for optimization purpose)
 * 
 * @param map_array 	2D array of the map (see t_tile)
 * @param map_size 		Size of the map (int, int)
 * 
 * @param border_c 		Color of the border of the minimap (in ARGB format)
 * 						(`0` for no border)
 * @param floor_c 		Color of the floor (in ARGB format)
 * @param ceiling_c 	Color of the ceiling (in ARGB format)
 * @param textures 		All the textures of the game (sorted by char)
 * 
 * @param orientation 	Orientation of the player (in rad)
 * @param position 		Position of the player (float, float)
 * @param keys 			Keys pressed by the player
 * 
 * @param frames 		Number of frames
*/
typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;
	t_frame		frame;

	t_tile		**map_array;
	t_ipos		map_size;

	int			border_c;
	int			floor_c;
	int			ceiling_c;
	t_texture	textures[128];

	float		orientation;
	t_pos		position;
	t_keys		keys;
	t_bool		minimap;
	t_bool		info;

	t_ull		frames;
}	t_cub;

void	ft_assign_to_cube(t_cub *cub, t_map *map);
void	ft_parse_checker(t_cub *cub, int ac, char **av);
void	ft_rendering(t_cub *cub);

// UTILS

void	ft_init(t_map *map);
void	ft_error_handle(t_map *map, char *error, char *str, int status);
void	ft_error_handle_color(t_map *map, char *line);
void	ft_skip_spaces(char *line, int *i, int *count);
void	ft_cut_extra_char(char *str);
void	ft_fill_line(char *line, int size);
int		ft_error(char *str);
char	*ft_lli_to_str(long long n, int lenght);
int		ft_numlen(int n);
char	*ft_ftoa(float n, int length);
t_frame	ft_load_texture(t_cub *cub, char *path);

// DATA

void	ft_cp_array(t_map *map);
void	ft_map_into_array(t_map *map, char *map_file);

#endif