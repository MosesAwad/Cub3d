/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:27:24 by mawad             #+#    #+#             */
/*   Updated: 2024/05/12 01:37:16 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "..//cub3d.h"

char	**mark_map_spawn(t_game *game, char **map)
{
	int		i;
	int		j;
	char	**buffer;

	(void) game;
	i = 0;
	while (map[i])
		i++;
	buffer = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (map[i])
	{
		j = 0;
		buffer[i] = (char *)malloc((ft_strlen(map[i]) + 1));
		while (map[i][j])
			buffer[i][j++] = 'F';
		buffer[i][j] = '\0';
		i++;
	}
	buffer[i] = NULL;
	return (buffer);
}

//Nieghbors arranged in: up, down, left, right
static int	find_neighbors1(t_game *game, t_index pos, t_index *neighbors)
{
	if (pos.x == 0 && pos.y == 0)
		return (neighbors[0] = (t_index){pos.x, pos.y + 1},
				neighbors[1] = (t_index){pos.x + 1, pos.y},
				2);
	else if (pos.x == game->map_width - 1 && pos.y == 0)
		return (neighbors[0] = (t_index){pos.x, pos.y + 1},
				neighbors[1] = (t_index){pos.x - 1, pos.y},
				2);
	else if (pos.x == 0 && pos.y == game->map_height - 1)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x + 1, pos.y},
				2);
	else if (pos.x == game->map_width - 1 && pos.y == game->map_height - 1)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x - 1, pos.y},
				2);
	else if (pos.y == 0)
		return (neighbors[0] = (t_index){pos.x, pos.y + 1},
				neighbors[1] = (t_index){pos.x - 1, pos.y},
				neighbors[2] = (t_index){pos.x + 1, pos.y},
				3);
	return (-1);
}

//Nieghbors arranged in: up, down, left, right
static int	find_neighbors2(t_game *game, t_index pos, t_index *neighbors)
{
	if (pos.y == game->map_height - 1)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x - 1, pos.y},
				neighbors[2] = (t_index){pos.x + 1, pos.y},
				3);
	else if (pos.x == 0)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x, pos.y + 1},
				neighbors[2] = (t_index){pos.x + 1, pos.y},
				3);
	else if (pos.x == game->map_width - 1)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x, pos.y + 1},
				neighbors[2] = (t_index){pos.x - 1, pos.y},
				3);
	else
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x, pos.y + 1},
				neighbors[2] = (t_index){pos.x - 1, pos.y},
				neighbors[3] = (t_index){pos.x + 1, pos.y},
				4);
	return (-1);
}

//Nieghbors arranged in: up, down, left, right
int	find_neighbors(t_game *game, t_index pos, t_index *neighbors)
{
	int	neighbor_count;

	neighbor_count = find_neighbors1(game, pos, neighbors);
	if (neighbor_count == -1)
		neighbor_count = find_neighbors2(game, pos, neighbors);
	return (neighbor_count);
}

void	dfs(t_game *game, char **mark_map, int x, int y)
{
	t_index	neighbors[4];
	int		k;
	int		neighbor_count;
	t_index	pos;

	mark_map[y][x] = 'T';
	k = 0;
	pos = (t_index){x, y};
	neighbor_count = find_neighbors(game, pos, neighbors);
	while (k < neighbor_count)
	{
		x = neighbors[k].x;
		y = neighbors[k].y;
		if (!(game->map[y][x] == '1' || game->map[y][x] == 'X')
				&& mark_map[y][x] == 'F')
			dfs(game, mark_map, x, y);
		k++;
	}
}

void	check_boundary(t_game *game, char **marked_map, int x, int y)
{
	t_index	neighbors[4];
	int		neighbor_count;
	int		k;
	t_index	pos;

	pos.x = x;
	pos.y = y;
	if (pos.x == 0 || pos.x == game->map_width - 1
		|| pos.y == 0 || pos.y == game->map_height - 1)
	{
		destroy_2d_arr(marked_map);
		exit_err(game, NULL, "Map not surrouned by walls");
	}
	k = 0;
	neighbor_count = find_neighbors(game, pos, neighbors);
	while (k < neighbor_count)
	{
		x = neighbors[k].x;
		y = neighbors[k].y;
		if (game->map[y][x] == 'X')
		{
			destroy_2d_arr(marked_map);
			exit_err(game, NULL, "Map not surrouned by walls");
		}
		k++;
	}
}

void	parse_marked_map(t_game *game, char **marked_map)
{
	int	i;
	int	j;

	i = 0;
	while (marked_map[i])
	{
		j = 0;
		while (marked_map[i][j])
		{
			if (marked_map[i][j] == 'T')
				check_boundary(game, marked_map, j, i);
			j++;
		}
		i++;
	}
}
