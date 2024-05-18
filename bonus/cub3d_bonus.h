/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:39 by mawad             #+#    #+#             */
/*   Updated: 2024/05/19 00:41:46 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

// # include "../mlx-linux/mlx.h"
# include "../mlx/mlx.h"
# include "../Libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

# define MIN_MAP_SCALE 32

# define MOVE_SPEED 0.08
# define ROT_SPEED	0.05

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

typedef struct s_minimap {
	int	x_draw;
	int	y_draw;
}	t_minimap;

typedef struct s_game {
	char		**map;
	t_minimap	minimap;
	int			fd;
	t_bool		move_up;
	t_bool		move_down;
	t_bool		move_right;
	t_bool		move_left;
	t_bool		rot_right;
	t_bool		rot_left;
	int			store_mouse_x;
	int			screen_height;
	int			screen_width;
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
	t_tex		album[5];
}	t_game;

//	---- START OF PARSING DIRECTORY SECTION ---- //

//parsing/map_dfs_utils_bonus.c
int		find_neighbors(t_game *game, t_index pos, t_index *neighbors);

//parsing/map_dfs_bonus.c
char	**mark_map_spawn(t_game *game, char **map);
void	dfs(t_game *game, char **mark_map, int x, int y);
void	parse_marked_map(t_game *game, char **marked_map);

//parsing/get_map_bonus.c
char	**get_map(t_game *game, int fd);
void	parse_map_lines(t_game *game, char **map);

//parsing/get_map_utils_bonus.c
void	ft_map_alloc_clean(char **map, char *line, int y);
t_bool	valid_line(char *line);
void	parse_map_lines(t_game *game, char **map);

//parsing/map_utils2_bonus.c
int		get_map_width(char **map);
int		get_map_height(char **map);
void	handle_spaces(char **map);

char	**ft_realloc_x(t_game *game, char **map);

//parsing/parse_textures_bonus.c
int		parse_textures(t_game *game, char *trimmed);

//parsing/parse_colors_bonus.c
int		parse_colors(t_game *game, char *trimmed);

//parsing/parse_colors_utils_bonus.c
void	check_rgb_syntax(t_game *game, char *full, char *str);

//parsing/parse_bonus.c
void	parse_elements(t_game *game, int fd);

//parsing/get_next_line_bonus.c
char	*get_next_line(int fd);

//parsing/parse_utils_bonus.c
t_bool	is_wspace(char c);
void	whitespace_checker(t_game *game, char *trimmed);
t_bool	is_trailing_wspace(char *str, int index);
t_bool	valid_file_name(char *str);

//parsing/parse_map_bonus.c
void	parse_map(t_game *game, int fd);

//	---- END OF PARSING DIRECTORY SECTION ---- //

//srcs/main_bonus.c
void	flush(t_game game);
void	draw_v_line(t_game *game, t_dda dda, int x, int color);
int		get_color(t_game *game, int index, int tex_x, int tex_y);
void	my_pixel_put(t_game *game, int x, int y, int color);

//srcs/minimap_bonus.c
void	ft_minimap(t_game *game);

//srcs/player_utils_bonus.c
void	set_up_player(t_game *game);

//srcs/set_up_images_bonus.c
void	set_up_images(t_game *game);

//srcs/raycast_bonus.c
void	set_up_delta_dist(t_dda *dda);
void	set_up_side_dist(t_vector *pos, t_dda *dda);
void	dda_loop(t_game *game, t_dda *dda);
int		ray_cast(void *param);

//srcs/raycast_utils_bonus.c
void	init_params_and_vectors(t_game *game, t_dda *dda,
			t_vector *ray_dir, double x);
void	set_up_start_end(t_game *game, t_dda *dda);
void	set_up_tex_x(t_game *game, t_dda dda, t_tex *tex);
void	texture_loop(t_game *game, t_tex *tex, t_dda dda, double x);
void	draw_ceiling_and_floor(t_game *game, t_dda dda, double x);

//srcs/general_utils_bonus.c
int		ft_destroy(t_game *game);
void	destroy_2d_arr(char **map);
void	exit_err(t_game *game, char *line, char *message);

//srcs/movement1_bonus.c
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	movement(t_game *game);

//srcs/movement2_bonus.c
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
int		mouse_hook(int x, int y, t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);

//srcs/movement_utils_bonus.c
void	rotate_angle(t_game *game, t_vector *vec, int flag);
t_bool	check_valid_move(t_game *game, int flag);

//srcs/drawing1_bonus.c
void	flush(t_game game);
int		get_color(t_game *game, int index, int tex_x, int tex_y);
void	draw_v_line(t_game *game, t_dda dda, int x, int color);
void	my_pixel_put(t_game *game, int x, int y, int color);

//srcs/drawing2_bonus.c
void	draw_gun_sprite(t_game *game);

//srcs/wall_collisions1_bonus.c
void	check_wc_up(t_game *game);
void	check_wc_down(t_game *game);
void	check_wc_left(t_game *game);
void	check_wc_right(t_game *game);

//srcs/wall_collisions2_bonus.c
void	check_wc_right(t_game *game);
void	check_wc_left(t_game *game);

//srcs/wall_collisions_utils_bonus.c
void	set_angle(t_vector *vec, double angle);
int		mini_cast(t_game *game, int key);
t_bool	check_valid_slide(t_game *game, t_vector target, int side);
t_bool	check_right_of_vertical(t_game *game);
t_bool	check_right_of_horizontal(t_game *game);

#endif