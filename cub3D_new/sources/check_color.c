/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:49:23 by miturk            #+#    #+#             */
/*   Updated: 2024/09/22 16:10:20 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	check_color(t_file *data)
{
	if (color_f(data, data->text->f, NULL, 0) == false)
		return (ft_putstr_fd("Error\nInvalid color\n", 2), false);
	if (color_c(data, data->text->c, NULL, 0) == false)
		return (ft_putstr_fd("Error\nInvalid color\n", 2), false);
	if (color_num(data->text->colorf) == false)
		return (ft_putstr_fd("Error\nInvalid color\n", 2), false);
	if (color_num(data->text->colorc) == false)
		return (ft_putstr_fd("Error\nInvalid color\n", 2), false);
	data->text->fr = ft_atoi(data->text->colorf[0]);
	data->text->fg = ft_atoi(data->text->colorf[1]);
	data->text->fb = ft_atoi(data->text->colorf[2]);
	data->text->cr = ft_atoi(data->text->colorc[0]);
	data->text->cg = ft_atoi(data->text->colorc[1]);
	data->text->cb = ft_atoi(data->text->colorc[2]);
	return (true);
}

static int	count_comma(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s)
		return (false);
	while (s[i] != '\0')
	{
		if (s[i] == ',')
			j++;
		i++;
	}
	return (j);
}

int	color_f(t_file *data, char *s, char *tmp, int i)
{
	int	j;

	j = count_comma(s);
	if (j != 2)
		return (false);
	data->text->colorf = ft_split(s, ',');
	if (data->text->colorf == NULL)
		return (false);
	while (data->text->colorf[i])
		i++;
	if (i != 3)
		return (false);
	i = -1;
	while (i++, data->text->colorf[i] != NULL && i < 3)
	{
		tmp = ft_strtrim(data->text->colorf[i], " ");
		if (tmp == NULL)
			return (ft_putstr_fd("Error\nMalloc\n", 2), false);
		(free(data->text->colorf[i]), data->text->colorf[i] = ft_strdup(tmp));
		if (data->text->colorf[i] == NULL)
			return (free(tmp), from_bot(data->text->colorf), false);
		free(tmp);
	}
	return (true);
}

int	color_c(t_file *data, char *s, char *tmp, int i)
{
	int	j;

	j = count_comma(s);
	if (j != 2)
		return (false);
	data->text->colorc = ft_split(s, ',');
	if (data->text->colorc == NULL)
		return (false);
	while (data->text->colorc[i])
		i++;
	if (i != 3)
		return (false);
	i = -1;
	while (i++, data->text->colorc[i] != NULL)
	{
		tmp = ft_strtrim(data->text->colorc[i], " ");
		if (tmp == NULL)
			return (ft_putstr_fd("Error\nMalloc\n", 2), false);
		(free(data->text->colorc[i]), data->text->colorc[i] = ft_strdup(tmp));
		if (data->text->colorc[i] == NULL)
			return (free(tmp), from_bot(data->text->colorc), false);
		free(tmp);
	}
	return (true);
}

int	color_num(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != NULL)
	{
		if (ft_strlen(s[i]) > 3 || ft_strlen(s[i]) < 1)
			return (false);
		j = 0;
		while (s[i][j] != '\0')
		{
			if (ft_isdigit(s[i][j]) == 0 && ft_isdigit(s[i][j + 1]) == 0)
				return (false);
			if (ft_atoi(s[i]) > 255 || ft_atoi(s[i]) < 0)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
