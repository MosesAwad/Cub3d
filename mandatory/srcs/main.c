/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:51 by mawad             #+#    #+#             */
/*   Updated: 2024/05/17 00:29:15 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
// 	game.screen_height = screen_height;
// 	game.screen_width = screen_width;

// 	printf("map height %d and map width %d\n", game.screen_height, game.screen_width);

//     game.data.mlx_ptr = mlx_init();

//     game.data.win_ptr = mlx_new_window(game.data.mlx_ptr, game.screen_width , game.screen_height, "Yay");

// 	game.data.img.img_ptr = mlx_new_image(game.data.mlx_ptr, game.screen_width, game.screen_height);
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

void	init_params(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
		game->album[i++].img = NULL;
	game->data.img.img_ptr = NULL;
	game->data.mlx_ptr = mlx_init();
	game->screen_height = SCREEN_HEIGHT;
	game->screen_width = SCREEN_WIDTH;
	game->data.win_ptr = mlx_new_window(game->data.mlx_ptr,
			game->screen_width, game->screen_height, "cub3D");
	game->map = NULL;
	game->ceiling_color = -1;
	game->floor_color = -1;
	game->map_ind_height = 0;
	game->map_ind_width = 0;
	game->player_angle = 0;
	game->move_up = FALSE;
	game->move_down = FALSE;
	game->move_right = FALSE;
	game->move_left = FALSE;
	game->rot_left = FALSE;
	game->rot_right = FALSE;
}

int main(int argc, char *argv[])
{
	t_game	game;	

	if (argc != 2)
		return (printf("Must use strictly 2 arguments\n"), 1);
	if (valid_file_name(argv[1]) == FALSE)
		return (printf("Map must be in .cub format\n"), 1);
	game.fd = open(argv[1], O_RDONLY, 0777);
	if (game.fd == -1)
		return (printf("Error opening file\n"), 1);
	init_params(&game);

	parse_elements(&game, game.fd);

	game.data.img.img_ptr = mlx_new_image(game.data.mlx_ptr, game.screen_width, game.screen_height);
	if (game.data.img.img_ptr == NULL)
	{
		printf("error : img ptr\n");
		return (1);
	}

	game.data.img.img_pixels_ptr = (int *) mlx_get_data_addr(game.data.img.img_ptr,
												&(game.data.img.bits_per_pixel),
												&(game.data.img.line_len),
												&(game.data.img.endian));
	if (game.data.img.img_pixels_ptr == NULL)
	{
		printf("error : img pxl ptr\n");
		return (1);
	}

	// set_up_player(&game);


	// set_up_images(&game);

	// ray_cast(&game);

	// // mlx_key_hook(game.data.win_ptr, key_hook, &game);
	// // mlx_key_hook(game.data.win_ptr, key_hook_linux, &game);

	// mlx_hook(game.data.win_ptr, 2, 1L << 0, key_hook, &game);
	// // mlx_hook(game.data.win_ptr, 2, 1L << 0, key_hook_linux, &game);

	mlx_hook(game.data.win_ptr, 2, 0, key_press, &game);
	mlx_hook(game.data.win_ptr, 3, 0, key_release, &game);
	mlx_loop_hook(game.data.mlx_ptr, ray_cast, &game);

    mlx_loop(game.data.mlx_ptr);

	return (0);
}
