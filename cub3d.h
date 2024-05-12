/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:39 by mawad             #+#    #+#             */
/*   Updated: 2024/05/12 22:17:47 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "mlx-linux/mlx.h"
# include "mlx/mlx.h"
# include "Libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

# define MAP_WIDTH 1280
# define MAP_HEIGHT 720

// # define FLOOR_COLOR 0xebf2f9
// # define CEILING_COLOR 0x737a84

// # define MAP_WIDTH 1284
// # define MAP_HEIGHT 960

# define MOVE_SPEED 0.15
# define ROT_SPEED	0.15

# define DIM 64

# define OG		"\033[0m"
# define RED	"\033[1;31m"
# define GRN	"\033[1;32m"
# define YLW	"\033[1;33m"
# define BLU	"\033[1;34m"
# define PRL	"\033[0;35m"

# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC_KEY 53
# define L_ARROW 123
# define R_ARROW 124

# define W_KEY_LINUX 119
# define A_KEY_LINUX 97
# define S_KEY_LINUX 115
# define D_KEY_LINUX 100
# define ESC_KEY_LINUX 65307
# define L_ARROW_LINUX 65361
# define R_ARROW_LINUX 65363

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef enum s_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_index{
	int	x;
	int	y;
}	t_index;

typedef struct s_vector {
	double	x;
	double	y;
}	t_vector;

typedef struct s_img {
	void	*img_ptr;
	int		*img_pixels_ptr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_tex {
	void	*img;
	int		*img_pixels_ptr;
	int		tex_width;
	int		tex_height;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
}				t_tex;

typedef struct s_dda {
	double		camera_x;
	t_vector	ray_dir;
	t_vector	map;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	t_bool		hit;
	int			side;
	int			line_height;
	int			start;
	int			end;
}				t_dda;

typedef struct s_var {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_var;

typedef struct s_game {
	char		**map;
	int			fd;
	int			map_height;
	int			map_width;
	int			map_ind_height;
	int			map_ind_width;
	int			floor_color;
	int			ceiling_color;
	double		player_posx;
	double		player_posy;
	double		player_angle;
	t_vector	dir;
	t_vector	cam_plane;
	t_var		data;
	t_tex		album[8];
}	t_game;


//	---- START OF PARSING DIRECTORY SECTION ---- //

//parsing/map_dfs.c
char	**mark_map_spawn(t_game *game, char **map);
void	dfs(t_game *game, char **mark_map, int x, int y);
void	parse_marked_map(t_game *game, char **marked_map);

//parsing/get_map.c
char	**get_map(int fd);
void	parse_map_lines(t_game *game, char **map);

//parsing/get_map_utils.c
void	ft_map_alloc_clean(char **map, char *line, int y);
t_bool	valid_line(char *line);
void	parse_map_lines(t_game *game, char **map);

//parsing/map_utils2.c
int		get_map_width(char **map);
int		get_map_height(char **map);
void	handle_spaces(char **map);

char	**ft_realloc_x(t_game *game, char **map);

//parsing/parse_textures.c
int		parse_textures(t_game *game, char *trimmed);

//parsing/parse_colors.c
int		parse_colors(t_game *game, char *trimmed);

//parsing/parse_colors_utils.c
void	check_rgb_syntax(t_game *game, char *full, char *str);

//parsing/parse.c
void	parse_elements(t_game *game, int fd);

//parsing/get_next_line.c
char	*get_next_line(int fd);

//parsing/parse_utils.c
t_bool	is_wspace(char c);
void	whitespace_checker(t_game *game, char *trimmed);
t_bool	is_trailing_wspace(char *str, int index);
t_bool	valid_file_name(char *str);

//parsing/parse_map.c
void	parse_map(t_game *game, int fd);

//	---- END OF PARSING DIRECTORY SECTION ---- //


//main.c
void	flush(t_game game);
void	draw_v_line(t_game *game, t_dda dda, int x, int color);
int		get_color(t_game *game, int index, int tex_x, int tex_y);
void	my_pixel_put(t_game *game, int x, int y, int color);

//player_utils.c
void	set_up_player(t_game *game);

//set_up_images.c
void	set_up_images(t_game *game);

//raycast.c
void	ray_cast(t_game *game);

//raycast_utils.c
void	set_up_start_end(t_game *game, t_dda *dda);
void	set_up_tex_x(t_game *game, t_dda dda, t_tex *tex);
void	texture_loop(t_game *game, t_tex *tex, t_dda dda, double x);
void	draw_ceiling_and_floor(t_game *game, t_dda dda, double x);

//general_utils.c
void	destroy_2d_arr(char **map);
void	exit_err(t_game *game, char *line, char *message);

#endif