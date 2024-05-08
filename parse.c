/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:14:23 by mawad             #+#    #+#             */
/*   Updated: 2024/05/09 03:00:41 by mawad            ###   ########.fr       */
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

int	convert_rgb(int *rgb)
{
	int	color;
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("rgb[%d]: %d\n", i, rgb[i]);
		if (rgb[i] > 255 || rgb[i] < 0)
		{
			printf("Error\nr, g, b values outside of 0-255 range"
				" OR invalid character usage\n""Please ensure format"
				" is strictly as follows:\n"
				"Identifier r, g, b\n");
		}
		i++;
	}
	color = rgb[0] * (pow(256, 2)) + (rgb[1] * 256) + rgb[2];
	return (color);
}

//This line:
//		if (str[i] == ',' && rgb[0] != -1)
// 			i++;
//was added to ensure that a ',' shall not be accepted the first
//value (the r (red) value), only after the first, or second value.
//So something like C ,242, 30, 0 is handled by that line.
void	set_color(char *str)
{
	int	i;
	int	j;
	int	k;
	int	rgb[3];
	int	color;

	i = 0;
	k = 0;
	rgb[0] = -1;
	rgb[1] = -1;
	rgb[2] = -1;
	while (str[i] && is_wspace(str[i]))
		i++;
	if (!str[i])
		printf("Error\nPlease enter an r, g, b value\n");
	while (str[i])
	{
		j = 0;
		while (str[i] && (is_wspace(str[i])) && str[i] != ',')
			i++;
		if (str[i] == ',')
		{
			if (rgb[0] == -1 || rgb[2] != -1)
				printf("Error\nWrong ',' character placement\n");
			else if (!is_wspace(str[i + 1]) && !ft_isdigit(str[i + 1]))
				printf("Error\nWrong ',' character placement\n");
			i++;
		}
		while (str[i + j] && ft_isdigit(str[i + j]))
			j++;
		if (j != 0)
		{
			rgb[k++] = ft_atoi(str + i);
			i = i + j;
		}
		while (str[i] && !(is_wspace(str[i])) && str[i] != ',')
			i++;
		if (str[i] == ',')
		{
			if (rgb[0] == -1 || rgb[2] != -1)
				printf("Error\nWrong ',' character placement\n");
			else if (!is_wspace(str[i + 1]) && !ft_isdigit(str[i + 1]))
				printf("Error\nWrong ',' character placement\n");
			i++;
		}
	}
	color = convert_rgb(rgb);
	printf("%x\n", color);
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
		else if (trimmed[0] == 'C')
			set_color(trimmed + 1);
		line = get_next_line(fd);
		i++;
	}
	if (count != 4)
		printf("Error\nMissing wall texture or incorrect texture identifier\n");
}
