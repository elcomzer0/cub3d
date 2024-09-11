/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:52:56 by miturk            #+#    #+#             */
/*   Updated: 2024/09/11 10:40:33 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

char	*trim_util(char *s, char *tmp)
{
	if (ft_strncmp(s, "F ", 2) == 0)
	{
		tmp = ft_strtrim(s, "F ");
		if (tmp == NULL)
			return (ft_putstr_fd("Error:\nMalloc\n", 2), NULL);
	}
	else if (ft_strncmp(s, "C ", 2) == 0)
	{
		tmp = ft_strtrim(s, "C ");
		if (tmp == NULL)
			return (ft_putstr_fd("Error:\nMalloc\n", 2), NULL);
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
		tmp = trim_util(s, tmp);
	else
		return (free(s), ft_putstr_fd("Error:\nInvalid texture\n", 2), NULL);
	if (tmp == NULL)
		return (ft_putstr_fd("Error:\nMalloc\n", 2), NULL);
	return (free(s), tmp);
}

int	call_color(t_file *data, char *s)
{
	if (ft_strncmp(s, "F ", 2) == 0 && data->text->f == NULL)
	{
		data->text->f = trim(s, NULL);
		if (data->text->f == NULL)
			return (free(s), ft_putstr_fd("Error:\nMalloc\n", 2), false);
	}
	else if (ft_strncmp(s, "C ", 2) == 0 && data->text->c == NULL)
	{
		data->text->c = trim(s, NULL);
		if (data->text->c == NULL)
			return (free(s), ft_putstr_fd("Error:\nMalloc\n", 2), false);
	}
	else
		return (ft_putstr_fd("Error:\nInvalid texture\n", 2), false);
	return (true);
}

int	call_text(t_file *data, char *s)
{
	if (ft_strncmp(s, "NO ", 3) == 0 && data->text->no == NULL)
	{
		data->text->no = trim(s, NULL);
		if (data->text->no == NULL)
			return (free(s), ft_putstr_fd("Error:\nTexture\n", 2), false);
	}
	else if (ft_strncmp(s, "SO ", 3) == 0 && data->text->so == NULL)
	{
		data->text->so = trim(s, NULL);
		if (data->text->so == NULL)
			return (free(s), ft_putstr_fd("Error:\nTexture\n", 2), false);
	}
	else if (ft_strncmp(s, "WE ", 3) == 0 && data->text->we == NULL)
	{
		data->text->we = trim(s, NULL);
		if (data->text->we == NULL)
			return (free(s), ft_putstr_fd("Error:\nTexture\n", 2), false);
	}
	else if (ft_strncmp(s, "EA ", 3) == 0 && data->text->ea == NULL)
	{
		data->text->ea = trim(s, NULL);
		if (data->text->ea == NULL)
			return (free(s), ft_putstr_fd("Error:\nTexture\n", 2), false);
	}
	else if (data->text->no == NULL || data->text->so == NULL
		|| data->text->we == NULL || data->text->ea == NULL)
		return (ft_putstr_fd("Error:\nMissing texture\n", 2), false);
	else
		return (ft_putstr_fd("Error:\nInvalid texture\n", 2), false);
	return (true);
}
