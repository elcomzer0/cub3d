/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:04:46 by miturk            #+#    #+#             */
/*   Updated: 2024/09/10 15:40:56 by miturk           ###   ########.fr       */
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

void	free_z_values(t_data *data)
{
	int	i;

	i = -1;
	while (i++, i < data->file->line_hei)
	{
		free(data->z_values[i]);
	}
	free(data->z_values);
}

int	map_conversion(t_data *data, int i)
{
	int	j;

	data->z_values = (int **)malloc(sizeof(int *)
			* (data->file->line_hei));
	if (data->z_values == NULL)
		return (ft_putstr_fd("Error:\nMalloc\n", 2), false);
	while (data->file->map[i] != NULL)
	{
		data->z_values[i] = (int *)malloc(sizeof(int)
				* (data->file->line_len));
		if (data->z_values[i] == NULL)
			return (free_z_values(data),
				ft_putstr_fd("Error:\nMalloc\n", 2), false);
		j = 0;
		while (data->file->map[i][j] != '\0')
		{
			data->z_values[i][j] = change_value(data->file->map[i][j] - '0');
			j++;
		}
		i++;
	}
	return (true);
}
