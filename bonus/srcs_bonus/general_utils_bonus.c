/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:07:29 by mawad             #+#    #+#             */
/*   Updated: 2024/05/12 22:52:58 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	destroy_2d_arr(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	if (map[0] == NULL)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

//Check later, naybe there is no need to even destroy mlx
//or game because by that point, we might not even have
//a map or initialized the mlx window yet.
void	exit_err(t_game *game, char *line, char *message)
{
	printf(RED"⚠️ Error ⚠️\n%s\n"OG, message);
	free(line);
	destroy_2d_arr(game->map);
	close(game->fd);
	exit(1);
}
