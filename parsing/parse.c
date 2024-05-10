/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:14:23 by mawad             #+#    #+#             */
/*   Updated: 2024/05/10 23:09:38 by mawad            ###   ########.fr       */
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
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n\v\f\r");
		count += parse_textures(game, trimmed);
		count += parse_colors(game, trimmed);
		line = get_next_line(fd);
	}
	if (count != 6)
		printf("Error\nMissing or incorrect identifier\n");
	printf("Parsing successful\n");
}
