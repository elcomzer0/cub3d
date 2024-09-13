/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:04:46 by miturk            #+#    #+#             */
/*   Updated: 2024/09/11 09:50:30 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

int	smallcheck(char c)
{
	if (c == ' ' || c == '\0')
		return (true);
	return (false);
}

int	short_check(t_file *data, int i, int j)
{
	if (smallcheck(data->map[i][j + 1]) == true
		|| smallcheck(data->map[i][j - 1]) == true
		|| smallcheck(data->map[i + 1][j]) == true
		|| smallcheck(data->map[i - 1][j]) == true)
		return (true);
	return (false);
}

void	map_width(t_file *data)
{
	int	i;

	i = 0;
	data->line_len = 0;
	while (data->map[i] != NULL)
	{
		if ((int)ft_strlen(data->map[i]) > data->line_len)
			data->line_len = (int)ft_strlen(data->map[i]);
		i++;
	}
	while (data->map[data->line_hei] != NULL)
		data->line_hei++;
}

int	change_value(int c)
{
	if (c == -16)
		c = c + 48;
	if (c == 30)
		c = c - 30;
	if (c == 35)
		c = c - 35;
	if (c == 39)
		c = c - 39;
	if (c == 21)
		c = c - 21;
	return (c);
}
