/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:07:29 by mawad             #+#    #+#             */
/*   Updated: 2024/05/10 22:01:53 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_destroy(t_game *game)
{
	int	i;

	i = 0;
	if (game->map == NULL)
		return ;
	if (game->map[0] == NULL)
		return ;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
}

//Check later, naybe there is no need to even destroy mlx
//or game because by that point, we might not even have
//a map or initialized the mlx window yet.
void	exit_err(t_game *game, char *line, char *message)
{
	printf(RED"⚠️ Error ⚠️\n%s\n"OG, message);
	free(line);
	ft_destroy(game);
	exit(1);
}
