/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:02:50 by mawad             #+#    #+#             */
/*   Updated: 2024/05/15 14:25:40 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_up(t_game *game)
{
	if (check_valid_move(game, W_KEY) == TRUE)
	{
		game->player_posx += (game->dir.x * MOVE_SPEED);
		game->player_posy += (game->dir.y * MOVE_SPEED);
	}
	ray_cast(game);
}

void	move_down(t_game *game)
{
	if (check_valid_move(game, S_KEY) == TRUE)
	{
		game->player_posx -= (game->dir.x * MOVE_SPEED);
		game->player_posy -= (game->dir.y * MOVE_SPEED);
	}
	ray_cast(game);
}

void	move_left(t_game *game)
{
	if (check_valid_move(game, A_KEY) == TRUE)
	{
		game->player_posx -= (-game->dir.y * MOVE_SPEED);
		game->player_posy -= (game->dir.x * MOVE_SPEED);
	}
	ray_cast(game);
}

void	move_right(t_game *game)
{
	if (check_valid_move(game, D_KEY) == TRUE)
	{
		game->player_posx += (-game->dir.y * MOVE_SPEED);
		game->player_posy += (game->dir.x * MOVE_SPEED);
	}
	ray_cast(game);
}
