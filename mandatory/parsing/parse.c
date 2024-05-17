/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:14:23 by mawad             #+#    #+#             */
/*   Updated: 2024/05/17 19:45:10 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	parse_gun_texture(t_game *game)
{
	game->album[4].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
			"mandatory/images/gun.xpm",
			&(game->album[4].tex_width), &(game->album[4].tex_height));
	if (game->album[4].img == NULL)
		exit_err(game, NULL, "Gun image not found");
	game->album[4].img_pixels_ptr = (int *)mlx_get_data_addr(game->album[4].img,
			&(game->album[4].bits_per_pixel), &(game->album[4].line_len),
			&(game->album[4].endian));
}

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
		if (parse_textures(game, trimmed) == 0)
			count += parse_colors(game, trimmed);
		else
			count++;
		free(trimmed);
		if (count != 6)
			line = get_next_line(fd);
	}
	if (count != 6)
		exit_err(game, line, "Missing or incorrect identifier");
	parse_gun_texture(game);
	parse_map(game, fd);
	printf("Parsing successful\n");
}
