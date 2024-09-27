/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:52:56 by miturk            #+#    #+#             */
/*   Updated: 2024/09/22 16:12:44 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

char	*trim_util(char *s, char *tmp)
{
	if (ft_strncmp(s, "F ", 2) == 0)
	{
		tmp = ft_strtrim(s, "F ");
		if (tmp == NULL)
			return (ft_putstr_fd("Error\nMalloc\n", 2), NULL);
	}
	else if (ft_strncmp(s, "C ", 2) == 0)
	{
		tmp = ft_strtrim(s, "C ");
		if (tmp == NULL)
			return (ft_putstr_fd("Error\nMalloc\n", 2), NULL);
	}
	return (tmp);
}

char	*trim(char *s, char *tmp)
{
	if (ft_strncmp(s, "NO ", 3) == 0)
		tmp = ft_strtrim(s, "NO ");
	else if (ft_strncmp(s, "SO ", 3) == 0)
		tmp = ft_strtrim(s, "SO ");
	else if (ft_strncmp(s, "EA ", 3) == 0)
		tmp = ft_strtrim(s, "EA ");
	else if (ft_strncmp(s, "WE ", 3) == 0)
		tmp = ft_strtrim(s, "WE ");
	else if (ft_strncmp(s, "F ", 2) == 0 || ft_strncmp(s, "C ", 2) == 0)
		tmp = trim_util(s, NULL);
	else
		return (ft_putstr_fd("Error\nInvalid texture\n", 2), NULL);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

int	call_color(t_file *data, char *s)
{
	if (ft_strncmp(s, "F ", 2) == 0 && data->text->f == NULL)
	{
		data->text->f = trim(s, NULL);
		if (data->text->f == NULL)
			return (ft_putstr_fd("Error\nMalloc\n", 2), false);
	}
	else if (ft_strncmp(s, "C ", 2) == 0 && data->text->c == NULL)
	{
		data->text->c = trim(s, NULL);
		if (data->text->c == NULL)
			return (ft_putstr_fd("Error\nMalloc\n", 2), false);
	}
	else
		return (ft_putstr_fd("Error\nInvalid color\n", 2), false);
	return (true);
}

int	store_texture(char **texture, char *s, const char *path)
{
	if (ft_strncmp(s, path, ft_strlen(path)) == 0 && *texture == NULL)
	{
		*texture = trim(s, NULL);
		if (*texture == NULL)
			return (ft_putstr_fd("Error\nTexture\n", 2), false);
		return (true);
	}
	return (false);
}

int	call_text(t_file *data, char *s)
{
	if (store_texture(&data->text->no, s, "NO") == true)
		return (true);
	else if (store_texture(&data->text->so, s, "SO") == true)
		return (true);
	else if (store_texture(&data->text->we, s, "WE") == true)
		return (true);
	else if (store_texture(&data->text->ea, s, "EA") == true)
		return (true);
	else if (data->text->no == NULL || data->text->so == NULL
		|| data->text->we == NULL || data->text->ea == NULL)
		return (ft_putstr_fd("Error\nMissing texture_\n", 2), false);
	else
		return (ft_putstr_fd("Error\nInvalid texture\n", 2), false);
}
