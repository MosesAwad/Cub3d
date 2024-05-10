/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:51 by mawad             #+#    #+#             */
/*   Updated: 2024/05/10 22:01:03 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_game *game, int x, int y, int color)
{
	int	offset;

	offset = (game->map_width * y) + x;
	*(offset + game->data.img.img_pixels_ptr) = color;
}

// //Draws a square of dimensions (DIM * DIM) starting from the top-left corner
// //of the point specified by co-ordinates(x, y)
// void	draw_square(t_img *img, int x, int y, int color)
// {
// 	int	ylim;
// 	int	xlim;
// 	int	x_og;

// 	ylim = y + DIM - 2;
// 	xlim = x + DIM - 2;
// 	x_og = x + 2;

// 	while (y + 2 < ylim)
// 	{
// 		x = x_og;
// 		while (x < xlim)
// 		{
// 			my_pixel_put(img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_circle(t_img *img, int x, int y, int r)
// {
// 	int	x_inc;
// 	int	y_inc;
// 	int	decision;

// 	x_inc = r;
// 	y_inc = 0;
// 	decision = 1 - r;
// 	while (x_inc >= y_inc)
// 	{
// 		my_pixel_put(img, x + x_inc, y + y_inc, 0xFF0000);
// 		my_pixel_put(img, x + y_inc, y + x_inc, 0xFF0000);
// 		my_pixel_put(img, x - y_inc, y + x_inc, 0xFF0000);
// 		my_pixel_put(img, x - x_inc, y + y_inc, 0xFF0000);
// 		my_pixel_put(img, x - x_inc, y - y_inc, 0xFF0000);
// 		my_pixel_put(img, x - y_inc, y - x_inc, 0xFF0000);
// 		my_pixel_put(img, x + y_inc, y - x_inc, 0xFF0000);
// 		my_pixel_put(img, x + x_inc, y - y_inc, 0xFF0000);

// 		y_inc++;
// 		if (decision <= 0)
// 		{
// 			decision += 2 * y_inc + 1;
// 		}
// 		else
// 		{
// 			x_inc--;
// 			decision += 2 * (y_inc - x_inc) + 1;
// 		}
// 	}
// }

// void draw_line(t_img *img, t_vector start, t_vector end)
// {
// 	// end = (t_vector){(start.x + end.x) * DIM + DIM / 2,
// 		// (start.y + end.y) * DIM + DIM /2};
// 	// start = (t_vector){start.x * DIM + DIM /2, start.y * DIM + DIM /2};

// 	end = (t_vector){(start.x + end.x) * DIM, (start.y + end.y) * DIM};
// 	start = (t_vector){start.x * DIM, start.y * DIM};

// 	// printf("start.x is %f and start.y is %f\n", start.x, start.y);
// 	// printf("end.x is %f and end.y is %f\n", end.x, end.y);
// 	start.x = (int) start.x;
// 	start.y = (int) start.y;
// 	end.x = (int) end.x;
// 	end.y = (int) end.y;
// 	// printf("start.x is %f and start.y is %f\n", start.x, start.y);
// 	// printf("end.x is %f and end.y is %f\n", end.x, end.y);

// 	int dx = fabs(end.x - start.x);
//     int dy = fabs(end.y - start.y);
//     int sx = start.x < end.x ? 1 : -1;
//     int sy = start.y < end.y ? 1 : -1;
//     int err = dx - dy;
//     int e2;

//     while (!(start.x == end.x && start.y == end.y))
//     {
// 		// printf("-----------------------------------\n");
// 		// printf("start.x is %f and start.y is %f\n", start.x, start.y);
// 		// printf("end.x is %f and end.y is %f\n", end.x, end.y);
//         my_pixel_put(img, start.x, start.y, 0x4169E1);
//         e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             start.x += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             start.y += sy;
//         }
//     }
// 	// Ensure end point is drawn
//     my_pixel_put(img, start.x, start.y, 0x4169E1);
// }

// void	draw_walls(t_game game, t_img *img)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (game.map[y])
// 	{
// 		x = 0;
// 		while (game.map[y][x])
// 		{
// 			if (game.map[y][x] == '1')
// 				draw_square(img, x * DIM, y * DIM, 0xff00);
// 			else
// 				draw_square(img, x * DIM, y * DIM, 0xD3D3D3);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	draw_v_line(t_game *game, t_dda dda, int x, int color)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	if (color == game->ceiling_color)
	{
		start = 0;
		end = dda.end;
	}
	else if (color == game->floor_color)
	{
		start = dda.start;
		end = game->map_height - 1;
	}
	while (start < end)
	{
		// if (color == FLOOR_COLOR && start % 4 == 0)
		// 	my_pixel_put(game, x, start, 0x6a6e70);
		// else
			my_pixel_put(game, x, start, color);
		// if (color == CEILING_COLOR)
		// {
		// 	my_pixel_put(game, x, start, color);
		// }
		start++;
	}
}

void	flush(t_game game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game.map_height)
	{
		x = 0;
		while (x < game.map_width)
		{
			my_pixel_put(&game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	rotate_angle(t_game *game, t_vector *vec, int flag)
{
	double	angle;
	double	vec_x_save;

	(void) game;
	vec_x_save = vec->x;
	// angle = game->player_angle;
	if (flag == 1)
		angle = -ROT_SPEED;
	else
		angle = ROT_SPEED;
	// printf("angle is %f\n", angle);
	vec->x = cos(angle) * vec->x - sin(angle) * vec->y;
	vec->y = sin(angle) * vec_x_save + cos(angle) * vec->y;
}

int	get_color(t_game *game, int tex_x, int tex_y)
{
	int	color;
	int	offset;

	color = 0;
	offset = (game->album[0].tex_width * tex_y) + (tex_x);
	color = *(game->album[0].img_pixels_ptr + offset);
	return (color);
}

t_bool	check_valid_move(t_game *game, int flag)
{
	t_vector	target_v;

	target_v.x = game->player_posx;
	target_v.y = game->player_posy;
	if (flag == W_KEY)
	{
		target_v.x += (game->dir.x * (MOVE_SPEED));
		target_v.y += (game->dir.y * (MOVE_SPEED));
	}
	else if (flag == A_KEY)
	{
		target_v.x -= (-game->dir.y * (MOVE_SPEED));
		target_v.y -= (game->dir.x * (MOVE_SPEED));
	}
	else if (flag == S_KEY)
	{
		target_v.x -= (game->dir.x * (MOVE_SPEED));
		target_v.y -= (game->dir.y * (MOVE_SPEED));
	}
	else if (flag == D_KEY)
	{
		target_v.x += (-game->dir.y * (MOVE_SPEED));
		target_v.y += (game->dir.x * (MOVE_SPEED));
	}
	if (game->map[(int) target_v.y][(int) target_v.x] == '1')
		return (FALSE);
	return (TRUE);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == W_KEY)
	{
		if (check_valid_move(game, W_KEY) == TRUE)
		{
			game->player_posx += (game->dir.x * MOVE_SPEED);
			game->player_posy += (game->dir.y * MOVE_SPEED);
		}
		ray_cast(game);
	}
	else if (keycode == A_KEY)
	{
		if (check_valid_move(game, A_KEY) == TRUE)
		{
			game->player_posx -= (-game->dir.y * MOVE_SPEED);
			game->player_posy -= (game->dir.x * MOVE_SPEED);
		}
		ray_cast(game);
	}
	else if (keycode == S_KEY)
	{
		if (check_valid_move(game, S_KEY) == TRUE)
		{
			game->player_posx -= (game->dir.x * MOVE_SPEED);
			game->player_posy -= (game->dir.y * MOVE_SPEED);
		}
		ray_cast(game);
	}
	else if (keycode == D_KEY)
	{
		if (check_valid_move(game, D_KEY) == TRUE)
		{
			game->player_posx += (-game->dir.y * MOVE_SPEED);
			game->player_posy += (game->dir.x * MOVE_SPEED);
		}
		ray_cast(game);
	}
	else if (keycode == L_ARROW)
	{
		rotate_angle(game, &(game->dir), 1);
		rotate_angle(game, &(game->cam_plane), 1);
		ray_cast(game);
	}
	else if (keycode == R_ARROW)
	{
		rotate_angle(game, &(game->dir), 0);
		rotate_angle(game, &(game->cam_plane), 0);
		ray_cast(game);
	}
	return (0);
}

int	key_hook_linux(int keycode, t_game *game)
{
	if (keycode == W_KEY_LINUX)
	{
		if (check_valid_move(game, W_KEY_LINUX) == TRUE)
		{
			game->player_posx += (game->dir.x * 0.10);
			game->player_posy += (game->dir.y * 0.10);
		}
		ray_cast(game);
	}
	else if (keycode == A_KEY_LINUX)
	{
		if (check_valid_move(game, A_KEY_LINUX) == TRUE)
		{
			game->player_posx -= (-game->dir.y * 0.10);
			game->player_posy -= (game->dir.x * 0.10);
		}
		ray_cast(game);
	}
	else if (keycode == S_KEY_LINUX)
	{
		if (check_valid_move(game, S_KEY_LINUX) == TRUE)
		{
			game->player_posx -= (game->dir.x * 0.10);
			game->player_posy -= (game->dir.y * 0.10);
		}
		ray_cast(game);
	}
	else if (keycode == D_KEY_LINUX)
	{
		if (check_valid_move(game, D_KEY_LINUX) == TRUE)
		{
			game->player_posx += (-game->dir.y * 0.10);
			game->player_posy += (game->dir.x * 0.10);
		}
		ray_cast(game);
	}
	else if (keycode == L_ARROW_LINUX)
	{
		rotate_angle(game, &(game->dir), 1);
		rotate_angle(game, &(game->cam_plane), 1);
		ray_cast(game);
	}
	else if (keycode == R_ARROW_LINUX)
	{
		rotate_angle(game, &(game->dir), 0);
		rotate_angle(game, &(game->cam_plane), 0);
		ray_cast(game);
	}
	return (0);
}

// int main()
// {
// 	t_game	game;	
// 	int		fd;

// 	fd = open("maps/map.cub", O_RDONLY, 0777);
// 	if (fd == -1)
// 	{
// 		printf("error opening file\n");
// 		return (1);
// 	}

// 	game.map = get_map(fd);
// 	game.map_height = MAP_HEIGHT;
// 	game.map_width = MAP_WIDTH;

// 	printf("map height %d and map width %d\n", game.map_height, game.map_width);

//     game.data.mlx_ptr = mlx_init();

//     game.data.win_ptr = mlx_new_window(game.data.mlx_ptr, game.map_width , game.map_height, "Yay");

// 	game.data.img.img_ptr = mlx_new_image(game.data.mlx_ptr, game.map_width, game.map_height);
// 	if (game.data.img.img_ptr == NULL)
// 	{
// 		printf("error : img ptr\n");
// 		return (1);
// 	}

// 	game.data.img.img_pixels_ptr = (int *) mlx_get_data_addr(game.data.img.img_ptr,
// 												&(game.data.img.bits_per_pixel),
// 												&(game.data.img.line_len),
// 												&(game.data.img.endian));
// 	if (game.data.img.img_pixels_ptr == NULL)
// 	{
// 		printf("error : img pxl ptr\n");
// 		return (1);
// 	}

// 	set_up_player(&game);
// 	game.player_angle = 0;

// 	set_up_images(&game);

// 	ray_cast(&game);
// 	mlx_put_image_to_window(game.data.mlx_ptr, game.data.win_ptr, game.data.img.img_ptr, 0, 0);

// 	// mlx_key_hook(game.data.win_ptr, key_hook, &game);
// 	// mlx_key_hook(game.data.win_ptr, key_hook_linux, &game);

// 	mlx_hook(game.data.win_ptr, 2, 1L << 0, key_hook, &game);
// 	// mlx_hook(game.data.win_ptr, 2, 1L << 0, key_hook_linux, &game);

//     mlx_loop(game.data.mlx_ptr);
//     return (0);
// }

int main()
{
	t_game	game;	
	int		fd;

	fd = open("maps/sample.cub", O_RDONLY, 0777);
	if (fd == -1)
	{
		printf("error opening file\n");
		return (1);
	}
	game.data.mlx_ptr = mlx_init();
	game.map_height = MAP_HEIGHT;
	game.map_width = MAP_WIDTH;
	game.data.win_ptr = mlx_new_window(game.data.mlx_ptr, game.map_width , game.map_height, "Yay");

	game.map = NULL;

	parse_elements(&game, fd);
	// game.map = get_map(fd);
	//mlx_loop(game.data.mlx_ptr);
	return (0);
}
