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

int	convert_rgb(long long int *rgb)
{
	int	color;
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("rgb[%d]: %lld\n", i, rgb[i]);
		if (rgb[i] > 255 || rgb[i] < 0)
			printf("Error\nr, g, b values outside of 0-255 range\n");
		i++;
	}
	color = rgb[0] * (pow(256, 2)) + (rgb[1] * 256) + rgb[2];
	return (color);
}

t_bool	com_trail_valid(int index, char *str)
{
	int		digit_count;

	digit_count = 0;
	index++;
	while (str[index] && str[index] != ',')
	{
		while (str[index] && is_wspace(str[index]))
			index++;
		if (ft_isdigit(str[index]))
			digit_count++;
		while (str[index] && ft_isdigit(str[index]))
			index++;
		if (str[index] && str[index] != ',' && !ft_isdigit(str[index]) && !is_wspace(str[index]))
			return (FALSE);
	}
	if (digit_count == 1)
		return (TRUE);
	return (FALSE);
}

//I am using index >= 1 and not index >= because I am sending
//trimmed + 1 to the check_syntax function. So I don't want to
//include that C in the beginning
t_bool	com_prec_valid(int index, char *str)
{
	int		digit_count;

	digit_count = 0;
	index--;
	while (index >= 1 && str[index] != ',')
	{
		while (index >= 1 && is_wspace(str[index]))
			index--;
		if (ft_isdigit(str[index]))
			digit_count++;
		while (index >= 1 && ft_isdigit(str[index]))
			index--;
		if (str[index] != ',' && !ft_isdigit(str[index]) && !is_wspace(str[index]))
			return (FALSE);
	}
	if (digit_count == 1)
		return (TRUE);
	return (FALSE);
}

//Logic is simply:
//-1.
//--All ',' characters can only be preceded by digits (whitespace
//--trail allowed)
//-2
//--Implement a counter to make sure tbat there has to be a total
//--of only 2 of these ',' characters that are preceeded by digits
//--(whitespace trail allowed).
//-3
//--Lastly, we also have to check if a ',' is strictly followed by
//--a number via the com_trail_valid function. While this may seem
//--redundant, it is a necessary step to handle [C  242,  23  0,] as
//--in this scenario, there are only 2 ',' characters and each one
//--is in fact preceeded by only digits but clearly it is wrong.
//--So instead of checking for whether there is only one digit
//--before and after a ',', I decided to look the other way
//-4.
//--All characters besides ',', digits, and whitespaces
//--are rejected.
// void	check_syntax(char *str)
// {
// 	int	i;
// 	int	j;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && is_wspace(str[i]))
// 			i++;
// 		if (str[i] == ',')
// 		{
// 			j = -1;
// 			while (i + j >= 0 && is_wspace(str[i + j]))
// 				j--;
// 			if ((i + j != 0) && !ft_isdigit(str[i + j]))
// 				break ;
// 			if (com_trail_valid(i, str) == FALSE)
// 				break ;
// 			count++;
// 			i++;		
// 		}
// 		else if (str[i] && (!is_wspace(str[i]) && !ft_isdigit(str[i])))
// 			break ;
// 		while (str[i] && ft_isdigit(str[i]))
// 			i++;
// 	}
// 	if (count != 2 || str[i] != '\0')
// 		printf("Error\nIncorrect r, g, b syntax\n");
// }
void	check_syntax(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_wspace(str[i]))
			i++;
		if (str[i] == ',')
		{
			if (com_prec_valid(i, str) && com_trail_valid(i, str))
				count++;
			else
				break ;
			i++;
		}
		else if (str[i] && (!is_wspace(str[i]) && !ft_isdigit(str[i])))
			break ;
		while (str[i] && ft_isdigit(str[i]))
			i++;
	}
	printf("count %d\n", count);
	if (count != 2 || str[i] != '\0')
		printf("Error\nIncorrect r, g, b syntax\n");
}


//This line:
//		if (str[i] == ',' && rgb[0] != -1)
// 			i++;
//was added to ensure that a ',' shall not be accepted the first
//value (the r (red) value), only after the first, or second value.
//So something like C ,242, 30, 0 is handled by that line.
void	set_color(char *str)
{
	int				i;
	int				j;
	int				k;
	long long int	rgb[3];
	int				color;

	i = 0;
	k = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (ft_isdigit(str[i + j]))
			j++;
		if (j != 0)
		{
			rgb[k++] = ft_atol(str + i);
			i = i + j;
		}
		else
			i++;
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
		{
			check_syntax(trimmed + 1);
			set_color(trimmed + 1);
		}
		line = get_next_line(fd);
		i++;
	}
	if (count != 4)
		printf("Error\nMissing or incorrect identifier\n");
}
