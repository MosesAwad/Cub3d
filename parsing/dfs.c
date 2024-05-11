
#include "..//cub3d.h"

typedef struct s_index{
    int x;
    int y;
}   t_index;

char    **mark_map_spawn(t_game *game, char **map)
{
    int     i;
    int     j;
    char    **buffer;

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

//up, down, left, right
void	find_neighbors(t_game *game, t_index pos, int *neighbor_count, t_index *neighbors)
{
    if (pos.x == 0 && pos.y == 0)
    {
        neighbors[0] = (t_index){pos.x, pos.y + 1};
        neighbors[1] = (t_index){pos.x + 1, pos.y};
        *neighbor_count = 2;
    }
    else if (pos.x == game->map_width - 1 && pos.y == 0)
    {
        neighbors[0] = (t_index){pos.x, pos.y + 1};
        neighbors[1] = (t_index){pos.x - 1, pos.y};
        *neighbor_count = 2;
    }
    else if (pos.x == 0 && pos.y == game->map_height - 1)
    {
        neighbors[0] = (t_index){pos.x, pos.y - 1};
        neighbors[1] = (t_index){pos.x + 1, pos.y};
        *neighbor_count = 2;
    }
    else if (pos.x == game->map_width - 1 && pos.y == game->map_height - 1)
    {
        neighbors[0] = (t_index){pos.x, pos.y - 1};
        neighbors[1] = (t_index){pos.x - 1, pos.y};
        *neighbor_count = 2;
    }
    else if (pos.y == 0)
    {
        neighbors[0] = (t_index){pos.x, pos.y + 1};
        neighbors[1] = (t_index){pos.x - 1, pos.y};
        neighbors[2] = (t_index){pos.x + 1, pos.y};
        *neighbor_count = 3;
    }
    else if (pos.y == game->map_height - 1)
    {
        neighbors[0] = (t_index){pos.x, pos.y - 1};
        neighbors[1] = (t_index){pos.x - 1, pos.y};
        neighbors[2] = (t_index){pos.x + 1, pos.y};
        *neighbor_count = 3;
    }
    else if (pos.x == 0)
    {
        neighbors[0] = (t_index){pos.x, pos.y - 1};
        neighbors[1] = (t_index){pos.x, pos.y + 1};
        neighbors[2] = (t_index){pos.x + 1, pos.y};
        *neighbor_count = 3;
    }
    else if (pos.x == game->map_width - 1)
    {
        neighbors[0] = (t_index){pos.x, pos.y - 1};
        neighbors[1] = (t_index){pos.x, pos.y + 1};
        neighbors[2] = (t_index){pos.x - 1, pos.y};
        *neighbor_count = 3;
    }
    else
    {
        neighbors[0] = (t_index){pos.x, pos.y - 1};
        neighbors[1] = (t_index){pos.x, pos.y + 1};
        neighbors[2] = (t_index){pos.x - 1, pos.y};
        neighbors[3] = (t_index){pos.x + 1, pos.y};
        *neighbor_count = 4;
    }
}

// void	dfs(t_game *game, char **mark_map, int j, int i)
// {
// 	t_index			neighbors[4];
// 	int				k;

// 	mark_map[i][j] = 'T';
// 	if (game->map[i][j] == 'C')
// 		game->dfs_coincount++;
// 	k = 0;
// 	find_neighbors(j, i, neighbors);
// 	while (k < 4)
// 	{
// 		i = neighbors[k].i;
// 		j = neighbors[k].j;
// 		if (!(game->map[i][j] == '1' || game->map[i][j] == 'E')
// 			&& mark_map[i][j] == 'F')
// 		{
// 			dfs(game, mark_map, j, i);
// 		}
// 		k++;
// 	}
// }

void    dfs(t_game *game, char **mark_map, int x, int y)
{
    t_index        neighbors[4];
    int             k;
    int             neighbor_count;
    t_index         pos;

    mark_map[y][x] = 'T';
    k = 0;
    pos = (t_index){x, y};
    neighbor_count = 0;
    find_neighbors(game, pos, &neighbor_count, neighbors);
    while (k < neighbor_count)
    {
        // for (int i = 0; mark_map[i] != NULL; i++) {
        //     printf("%s\n", mark_map[i]);
        // }
        // printf("\n");
        x = neighbors[k].x;
        y = neighbors[k].y;
        if (!(game->map[y][x] == '1' || game->map[y][x] == 'X')
                && mark_map[y][x] == 'F')
            dfs(game, mark_map, x, y);
        k++;
    }
}

void  check_boundary(t_game *game, int x, int y)
{
    t_index neighbors[4];
    int     neighbor_count;
    int     k;
    t_index pos;

    pos.x = x;
    pos.y = y;
    if (pos.x == 0 || pos.x == game->map_width - 1
        || pos.y == 0 || pos.y == game->map_height - 1)
    {
        // free_2d_arr(marked_map);
        exit_err(game, NULL, "Map not surrouned by walls");
    }
    neighbor_count = 0;
    k = 0;
    find_neighbors(game, pos, &neighbor_count, neighbors);
    while (k < neighbor_count)
    {
        x = neighbors[k].x;
        y = neighbors[k].y;
        if (game->map[y][x] == 'X')
        {
            // free_2d_arr(marked_map);
            exit_err(game, NULL, "Map not surrouned by walls");
        }
        k++;
    }
}

void    parse_marked_map(t_game *game, char **marked_map)
{
    int i;
    int j;

    i = 0;
    while (marked_map[i])
    {
        j = 0;
        while (marked_map[i][j])
        {
            if (marked_map[i][j] == 'T')
                check_boundary(game, j, i);
            j++;
        }
        i++;
    }
}
