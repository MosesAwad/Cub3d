/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:02:50 by mawad             #+#    #+#             */
/*   Updated: 2024/05/15 23:50:21 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_up(t_game *game)
{
	if (game->move_up == FALSE)
		return ;
	if (check_valid_move(game, W_KEY) == TRUE)
	{
		game->player_posx += (game->dir.x * MOVE_SPEED);
		game->player_posy += (game->dir.y * MOVE_SPEED);
	}
}

void	move_down(t_game *game)
{
	if (game->move_down == FALSE)
		return ;
	if (check_valid_move(game, S_KEY) == TRUE)
	{
		game->player_posx -= (game->dir.x * MOVE_SPEED);
		game->player_posy -= (game->dir.y * MOVE_SPEED);
	}
}

void	move_left(t_game *game)
{
	if (game->move_left == FALSE)
		return ;
	if (check_valid_move(game, A_KEY) == TRUE)
	{
		game->player_posx -= (-game->dir.y * MOVE_SPEED);
		game->player_posy -= (game->dir.x * MOVE_SPEED);
	}
}

void	move_right(t_game *game)
{
	if (game->move_right == FALSE)
		return ;
	if (check_valid_move(game, D_KEY) == TRUE)
	{
		game->player_posx += (-game->dir.y * MOVE_SPEED);
		game->player_posy += (game->dir.x * MOVE_SPEED);
	}
}

void	movement(t_game *game)
{
	move_up(game);
	move_down(game);
	move_left(game);
	move_right(game);
	rotate_left(game);
	rotate_right(game);
}
