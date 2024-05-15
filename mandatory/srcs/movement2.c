/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:09:14 by mawad             #+#    #+#             */
/*   Updated: 2024/05/15 14:48:58 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_game *game)
{
	rotate_angle(&(game->dir), 1);
	rotate_angle(&(game->cam_plane), 1);
	ray_cast(game);
}

void	rotate_right(t_game *game)
{
	rotate_angle(&(game->dir), 0);
	rotate_angle(&(game->cam_plane), 0);
	ray_cast(game);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		move_up(game);
	else if (keycode == A_KEY)
		move_left(game);
	else if (keycode == S_KEY)
		move_down(game);
	else if (keycode == D_KEY)
		move_right(game);
	else if (keycode == L_ARROW)
		rotate_left(game);
	else if (keycode == R_ARROW)
		rotate_right(game);
	return (0);
}

// int	key_hook_linux(int keycode, t_game *game)
// {
// 	if (keycode == W_KEY_LINUX)
// 	{
// 		if (check_valid_move(game, W_KEY_LINUX) == TRUE)
// 		{
// 			game->player_posx += (game->dir.x * 0.10);
// 			game->player_posy += (game->dir.y * 0.10);
// 		}
// 		ray_cast(game);
// 	}
// 	else if (keycode == A_KEY_LINUX)
// 	{
// 		if (check_valid_move(game, A_KEY_LINUX) == TRUE)
// 		{
// 			game->player_posx -= (-game->dir.y * 0.10);
// 			game->player_posy -= (game->dir.x * 0.10);
// 		}
// 		ray_cast(game);
// 	}
// 	else if (keycode == S_KEY_LINUX)
// 	{
// 		if (check_valid_move(game, S_KEY_LINUX) == TRUE)
// 		{
// 			game->player_posx -= (game->dir.x * 0.10);
// 			game->player_posy -= (game->dir.y * 0.10);
// 		}
// 		ray_cast(game);
// 	}
// 	else if (keycode == D_KEY_LINUX)
// 	{
// 		if (check_valid_move(game, D_KEY_LINUX) == TRUE)
// 		{
// 			game->player_posx += (-game->dir.y * 0.10);
// 			game->player_posy += (game->dir.x * 0.10);
// 		}
// 		ray_cast(game);
// 	}
// 	else if (keycode == L_ARROW_LINUX)
// 	{
// 		rotate_angle(game, &(game->dir), 1);
// 		rotate_angle(game, &(game->cam_plane), 1);
// 		ray_cast(game);
// 	}
// 	else if (keycode == R_ARROW_LINUX)
// 	{
// 		rotate_angle(game, &(game->dir), 0);
// 		rotate_angle(game, &(game->cam_plane), 0);
// 		ray_cast(game);
// 	}
// 	return (0);
// }