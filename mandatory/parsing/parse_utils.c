/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:25:50 by mawad             #+#    #+#             */
/*   Updated: 2024/05/12 18:17:48 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_bool	is_wspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (TRUE);
	return (FALSE);
}

void	whitespace_checker(t_game *game, char *trimmed)
{
	if (trimmed[0] == 'C' || trimmed[0] == 'F')
	{
		if (!is_wspace(trimmed[1]))
			exit_err(game, trimmed, "Identifier and r,g,b values must"
				" be separated by whitespace");
	}
	if ((trimmed[0] == 'N' && trimmed[1] == 'O')
		|| (trimmed[0] == 'S' && trimmed[1] == 'O')
		|| (trimmed[0] == 'E' && trimmed[1] == 'A')
		|| (trimmed[0] == 'W' && trimmed[1] == 'E'))
	{
		if (!is_wspace(trimmed[2]))
			exit_err(game, trimmed, "Identifier and texture path must"
				" be separated by whitespace");
	}
}

t_bool	is_trailing_wspace(char *str, int index)
{
	while (str[index])
	{
		if (!is_wspace(str[index]))
			return (FALSE);
		index++;
	}
	return (TRUE);
}

//.cub
t_bool	valid_file_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i < 4)
		return (FALSE);
	i -= 4;
	if (ft_strncmp(str + i, ".cub", 4) != 0)
		return (FALSE);
	return (TRUE);
}
