/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:00:54 by miturk            #+#    #+#             */
/*   Updated: 2024/09/24 16:39:04 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	help(t_file *data, int i, int j, char *tmp)
{
	tmp = ft_strtrim(data->file[i], " ");
	if (tmp == NULL)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), false);
	if (tmp[0] == '\n' && data->file[i][0] == ' ')
		return (data->texture[j] = NULL, free(tmp),
			ft_putstr_fd("Error\nInvalid texture\n", 2), false);
	(free(data->file[i]), data->file[i] = tmp);
	return (true);
}

char	**list_textures(t_file *data, int i, int j, char *tmp)
{
	data->texture = (char **)malloc(sizeof(char *) * (6 + 1));
	if (data->texture == NULL)
		return (ft_putstr_fd("Error\nMalloc fail\n", 2), NULL);
	while (i++, j < 6)
	{
		if (data->file[i][0] == ' ')
		{
			if (help(data, i, j, tmp) == false)
				return (NULL);
		}
		else if (data->file[i][0] == '\n')
			continue ;
		if (is_texture(data, i, 0) == false && data->file[i][0] != '\n')
			return (data->texture[j] = NULL,
				ft_putstr_fd("Error\nInvalid texture\n", 2), NULL);
		if (is_texture(data, i, 0) == false && j < 6)
			return (data->texture[j] = NULL,
				ft_putstr_fd("Error\nInvalid file\n", 2), NULL);
		data->texture[j] = ft_strdup(data->file[i]);
		if (data->texture[j] == NULL)
			return (ft_putstr_fd("Error\nMalloc\n", 2), NULL);
		data->texture[j][(int)ft_strlen(data->texture[j]) - 1] = '\0';
		j++;
	}
	return (data->texture[j] = NULL, data->texture);
}

int	text_check(t_file *data)
{
	int	i;

	i = false;
	if ((data->text->no[0] == '.' || ft_isalnum(data->text->no[0]) != 0)
		&& (data->text->so[0] == '.' || ft_isalnum(data->text->so[0]) != 0)
		&& (data->text->we[0] == '.' || ft_isalnum(data->text->we[0]) != 0)
		&& (data->text->ea[0] == '.' || ft_isalnum(data->text->ea[0]) != 0))
		i = true;
	if (i == false)
		return (ft_putstr_fd("Error\nMissing texture\n", 2), false);
	return (true);
}

int	check_textures(t_file *data, int i, char *s)
{
	while (i++, data->texture[i] != NULL)
	{
		s = ft_strtrim(data->texture[i], " ");
		if (s == NULL)
			return (ft_putstr_fd("Error\nMalloc failed\n", 2), false);
		if (ft_strncmp(s, "NO ", 3) == 0 || ft_strncmp(s, "SO ", 3) == 0
			|| ft_strncmp(s, "WE ", 3) == 0 || ft_strncmp(s, "EA ", 3) == 0)
		{
			if (call_text(data, s) == false)
				return (free(s), false);
		}
		else if (ft_strncmp(s, "F ", 2) == 0 || ft_strncmp(s, "C ", 2) == 0)
		{
			if (call_color(data, s) == false)
				return (free(s), false);
		}
		else
			return (ft_putstr_fd("Error\nInvalid texture\n", 2), free(s),
				false);
		free(s);
	}
	if (text_check(data) == false
		|| check_filetype(data) == false)
		return (false);
	return (true);
}

int	skip_textures(t_file *data)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (data->file[i] != NULL)
	{
		if (is_texture(data, i, 0) == true)
			x++;
		if ((is_texture(data, i, 0) == false) && data->file[i][0] != '\n')
			break ;
		i++;
	}
	if (i < 6 || x != 6)
		return (false);
	return (i);
}
