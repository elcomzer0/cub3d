/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:59:42 by miturk            #+#    #+#             */
/*   Updated: 2024/09/08 14:01:54 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

char	**list_map(t_file *data)
{
	int	i;
	int	j;

	i = skip_textures(data);
	j = 0;
	data->map = (char **)malloc(sizeof(char *) * ((data->i - i) + 1));
	if (data->map == NULL)
		return (ft_putstr_fd("Error: Malloc failed\n", 2), NULL);
	while (data->file[i] != NULL)
	{
		data->map[j] = ft_strdup(data->file[i]);
		if (data->map[j] == NULL)
			return (NULL);
		i++;
		j++;
	}
	data->map[j] = NULL;
	return (data->map);
}

int	check_map(t_file *data, char *tmp, int i, int j)
{
	map_width(data);
	while (data->map[i] != NULL)
	{
		tmp = ft_strtrim(data->map[i], " ");
		if (tmp == NULL)
			return (ft_putstr_fd("Error: Malloc failed\n", 2), false);
		if (tmp[0] == '\n' && data->map[i][0] == ' '
			&& ft_strchr(data->map[i], '1') == NULL)
			return (free(tmp),
				ft_putstr_fd("Error: Invalid map: newline\n", 2), false);
		(free(tmp), j = -1);
		while (j++, data->map[i][j] != '\0')
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& is_player(data->map[i][j]) == false
				&& data->map[i][j] != ' ' && data->map[i][j] != '\n')
				return (ft_putstr_fd("Error: Invalid map: Ply\n", 2), false);
		}
		if (data->map[i + 1] != NULL \
			&& data->map[i + 1][0] == ' ' && data->map[i][0] == '\0')
			return (ft_putstr_fd("Error: Invalid map: last line\n", 2), false);
		i++;
	}
	return (true);
}

int	square_map(t_file *data, int i, int j, int extra)
{
	char	*new;
	char	*tmp;

	while (i++, data->map[i] != NULL)
	{
		extra = (int)ft_strlen(data->map[i]);
		if (extra < data->line_len)
		{
			j = -1;
			tmp = (char *)malloc(sizeof(char) * (data->line_len - extra + 1));
			if (tmp == NULL)
				return (ft_putstr_fd("Error\nMalloc failed\n", 2), false);
			while (j++, j < (data->line_len - extra))
				tmp[j] = ' ';
			tmp[data->line_len - extra] = '\0';
			new = ft_strjoin(data->map[i], tmp);
			if (new == NULL)
				return (ft_putstr_fd("Error\nMalloc failed\n", 2), false);
			(free(data->map[i]), data->map[i] = ft_strdup(new));
			if (data->map[i] == NULL)
				return (free(new), ft_putstr_fd("Error\nMalloc failed\n", 2), false);
			(free(new), free(tmp));
		}
	}
	return (true);
}

void	remove_newline(t_file *data)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		tmp = (char *)malloc(sizeof(char) * (ft_strlen(data->map[i]) + 1));
		if (tmp == NULL)
			return (ft_putstr_fd("Error\nMalloc failed\n", 2));
		while (data->map[i][j] != '\n' && data->map[i][j] != '\0')
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = ' ';
			j++;
		}
		(ft_strncpy(tmp, data->map[i], j), free(data->map[i]));
		data->map[i] = ft_strdup(tmp);
		if (data->map[i] == NULL && i < data->line_hei - 1)
			return (ft_putstr_fd("Error\nMalloc failed\n", 2));
		(free(tmp), i++);
	}
}

int	valid_map(t_file *data, int i, int j)
{
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (ft_strchr(data->map[data->line_hei - 1], '0') != NULL)
				return (ft_putstr_fd("Error: Map: last line\n", 2), false);
			if (data->map[i][0] == '0' || is_player(data->map[i][0]) == true)
				return (ft_putstr_fd("Error: Map: Wrong border\n", 2), false);
			if (data->map[0][j] == '0' || is_player(data->map[0][j]) == true)
				return (ft_putstr_fd("Error: Map: Wrong border\n", 2), false);
			if (data->map[i][j] == '0')
				if (short_check(data, i, j) == true || data->line_hei == i)
					return (ft_putstr_fd("Error: Map: space around 0\n", 2),
						false);
			if (is_player(data->map[i][j]) == true)
				if (short_check(data, i, j) == true)
					return (ft_putstr_fd("Error: Map: space P\n", 2), false);
			j++;
		}
		i++;
	}
	return (true);
}
