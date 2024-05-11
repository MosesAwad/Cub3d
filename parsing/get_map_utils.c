/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:58:22 by mawad             #+#    #+#             */
/*   Updated: 2024/05/12 00:41:17 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_map_alloc_clean(char **map, char *line, int y)
{
	int	i;

	i = 0;
	free(line);
	if (y != -1)
	{
		while (i < y)
			free(map[i++]);
	}
	free(map);
	printf("Invalid map line\n");
	exit(1);
}

t_bool	valid_line(char *line)
{
	char	*set;
	int		i;

	i = 0;
	set = "01NSEW ";
	while (line[i])
	{
		if (!ft_strchr(set, line[i]))
		{
			printf("char that fucked us is -%c-\n", line[i]);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	parse_map_lines(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\0')
			exit_err(game, NULL, "Empty line not allowed"
				" in map content");
		if (valid_line(map[i]) == FALSE)
			exit_err(game, NULL, "Invalid map line");
		i++;
	}
}
