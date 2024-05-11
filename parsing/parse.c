/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:14:23 by mawad             #+#    #+#             */
/*   Updated: 2024/05/11 01:04:27 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//check what happens if no spaces after identifiers
//check what happens if no lines given in map.cub
void	parse_elements(t_game *game, int fd)
{
	char	*line;
	char	*trimmed;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line && count != 6)
	{
		trimmed = ft_strtrim(line, " \t\n\v\f\r");
		count += parse_textures(game, trimmed);
		count += parse_colors(game, trimmed);
		free(trimmed);
		line = get_next_line(fd);
	}
	if (count != 6)
		exit_err(game, line, "Missing or incorrect identifier");
	game->map = get_map(fd);

	if (game->map)
	{
		for (int i = 0; game->map[i] != NULL; i++) {
			printf("%s\n", game->map[i]);
		}
	}

	printf("\n");

	game->map = ft_realloc_x(game, game->map);
	for (int i = 0; game->map[i] != NULL; i++) {
		printf("%s\n", game->map[i]);
	}


	printf("game height is %d and game width is %d\n", game->map_height, game->map_width);
	printf("\n");

	char **mark_map = mark_map_spawn(game, game->map);
	for (int i = 0; mark_map[i] != NULL; i++) {
		printf("%s\n", mark_map[i]);
	}

	printf("\n");
	set_up_player(game);

	printf("player pos is at %d and %d\n", (int) game->player_posx, (int) game->player_posy);

	dfs(game, mark_map, (int) game->player_posx, (int) game->player_posy);
	for (int i = 0; mark_map[i] != NULL; i++) {
		for (int j = 0; mark_map[i][j]; j++)
		{
			if (mark_map[i][j] == 'T')
				printf(GRN"%c"OG, mark_map[i][j]);
			else
				printf("%c", mark_map[i][j]);
		}
		printf("\n");
	}
	parse_marked_map(game, mark_map);
	printf("\n");

	printf("Parsing successful\n");
}
