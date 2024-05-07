/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:01:02 by mawad             #+#    #+#             */
/*   Updated: 2024/05/07 22:46:48 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_dir(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'N')
	{
		game->dir = (t_vector){0, -1};
		game->cam_plane = (t_vector){0.66, 0};
	}
	else if (game->map[y][x] == 'S')
	{
		game->dir = (t_vector){0, 1};
		game->cam_plane = (t_vector){-0.66, 0};
	}
	else if (game->map[y][x] == 'E')
	{
		game->dir = (t_vector){1, 0};
		game->cam_plane = (t_vector){0, 0.66};
	}
	else if (game->map[y][x] == 'W')
	{
		game->dir = (t_vector){-1, 0};
		game->cam_plane = (t_vector){0, -0.66};
	}
}

void	set_player_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				set_player_dir(game, x, y);
				game->player_posx = x;
				game->player_posy = y;
				return ;
			}
			x++;
		}
		y++;
	}
	ft_destroy(game);
	printf("Error: no player on map\n");
	exit(1);
}
