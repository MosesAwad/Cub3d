/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:58:22 by mawad             #+#    #+#             */
/*   Updated: 2024/05/11 01:03:22 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_rules1(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[0][j] == '1')
		j++;
	if (game->map[0][j] != '\0')
		exit_err(game, NULL, "map not surrounded by walls");
	while (game->map[i + 1])
		i++;
	j = 0;
	while (game->map[i][j] == '1')
		j++;
	if (game->map[i][j] != '\0')
		exit_err(game, NULL, "map not surrounded by walls");
}
