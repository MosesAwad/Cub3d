/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:46:24 by mawad             #+#    #+#             */
/*   Updated: 2024/05/11 00:30:05 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_map_width(char **map)
{
	int	j;

	j = 0;
	while (map[0][j])
		j++;
	return (j);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

//Fill preceeding and trailing spaces with X's
//Fill intermediate spaces with 0's
char	**ft_realloc_x(t_game *game, char **map)
{
	int		i;
	int		j;
	int		max_len;
	char	**buffer;

	i = 0;
	max_len = -2147483648;
	while (map[i])
		i++;
	buffer = (char **)malloc((i + 1) * (sizeof(char *)));
	game->map_height = i;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max_len)
			max_len = j;
		i++;
	}
	i = 0;
	while (map[i])
		buffer[i++] = (char *)malloc(max_len + 1);
	buffer[i] = NULL;
	game->map_width = max_len;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (is_wspace(map[i][j]))
			buffer[i][j++] = 'X';
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				buffer[i][j] = '0';
			else
				buffer[i][j] = map[i][j];
			j++;
		}
		while (j < max_len)
			buffer[i][j++] = 'X';
		buffer[i][j] = '\0';
		free(map[i]);
		i++;
	}
	free(map);
	return (buffer);
}

// void	handle_spaces(char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (map == NULL)
// 		return ;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (is_wspace(map[i][j]))
// 				map[i][j] = '1';
// 			j++;
// 		}
// 		i++;
// 	}
// }
