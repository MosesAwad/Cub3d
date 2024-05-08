/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:14:23 by mawad             #+#    #+#             */
/*   Updated: 2024/05/09 00:31:20 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_tex_path(char *line)
{
	int	i;

	i = 0;
	while (line[i + 1])
	{
		if (line[i] == '.' && line[i + 1] == '/')
			break ;
		i++;
	}
	free(line);
}

void	get_path(t_game *game, char *str, int index)
{
	int			i;

	i = 0;
	while (str[i] && is_wspace(str[i]))
	{
		i++;
	}
	if (!str[i])
		printf("Error\nA texture missing a file name\n");
	game->album[index].img = mlx_xpm_file_to_image(game->data.mlx_ptr, str + i,
			&(game->album[index].tex_width), &(game->album[index].tex_height));
	if (game->album[index].img == NULL)
		printf("Error\nFile path -> [%s] not found\n", str + i);
	else
		printf("Success! Image -> [%s] loaded\n", str + i);
}

static int	get_tex_index(char *trimmed)
{
	int	index;

	index = 0;
	if (trimmed[0] == 'N')
		index = 0;
	else if (trimmed[0] == 'S')
		index = 1;
	else if (trimmed[0] == 'E')
		index = 2;
	else if (trimmed[0] == 'W')
		index = 3;
	return (index);
}

void	parse_textures(t_game *game, int fd)
{
	int		i;
	char	*line;
	char	*trimmed;
	int		count;

	i = 0;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n\v\f\r");
		if ((trimmed[0] == 'N' && trimmed[1] == 'O')
			|| (trimmed[0] == 'S' && trimmed[1] == 'O')
			|| (trimmed[0] == 'E' && trimmed[1] == 'A')
			|| (trimmed[0] == 'W' && trimmed[1] == 'E'))
		{
			get_path(game, trimmed + 2, get_tex_index(trimmed));
			count++;
		}
		line = get_next_line(fd);
		i++;
	}
	if (count != 4)
		printf("Error\nMissing wall texture or incorrect texture format\n");
}
