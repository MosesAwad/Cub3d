/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:25:50 by mawad             #+#    #+#             */
/*   Updated: 2024/05/10 23:24:55 by mawad            ###   ########.fr       */
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
