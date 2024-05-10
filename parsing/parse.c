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

	handle_spaces(game->map);
	if (game->map)
	{
		for (int i = 0; game->map[i] != NULL; i++) {
			printf("%s\n", game->map[i]);
		}
	}
	map_rules1(game);
	printf("Parsing successful\n");
}
