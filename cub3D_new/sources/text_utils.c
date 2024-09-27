/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:07:25 by miturk            #+#    #+#             */
/*   Updated: 2024/09/22 16:12:25 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	is_texture(t_file *data, int i, int x)
{
	char	*tmp;

	tmp = ft_strtrim(data->file[i], " ");
	if (tmp == NULL)
		return (false);
	if (tmp[x] == 'N' && tmp[x + 1] == 'O'
		&& tmp[x + 2] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'S' && tmp[x + 1] == 'O'
		&& tmp[x + 2] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'W' && tmp[x + 1] == 'E'
		&& tmp[x + 2] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'E' && tmp[x + 1] == 'A'
		&& data->file[i][x + 2] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'F' && tmp[x + 1] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'C' && tmp[x + 1] == ' ')
		return (free(tmp), true);
	else
		return (free(tmp), false);
}

int	check_filelen(t_file *data)
{
	if ((int)ft_strlen(data->text->no) < 4)
		return (ft_putstr_fd("Error\nInvalid texture\n", 2), false);
	if ((int)ft_strlen(data->text->so) < 4)
		return (ft_putstr_fd("Error\nInvalid texture\n", 2), false);
	if ((int)ft_strlen(data->text->ea) < 4)
		return (ft_putstr_fd("Error\nInvalid texture\n", 2), false);
	if ((int)ft_strlen(data->text->we) < 4)
		return (ft_putstr_fd("Error\nInvalid texture\n", 2), false);
	return (true);
}

int	check_filetype(t_file *data)
{
	int		i;
	char	*sub;

	if (check_filelen(data) == false)
		return (false);
	i = ((int)ft_strlen(data->text->no) - 4);
	sub = ft_substr(data->text->no, i, 4);
	if (ft_strncmp(sub, ".xpm", 4) != 0)
		return (free(sub), ft_putstr_fd("Error\nInvalid text\n", 2), false);
	i = ((int)ft_strlen(data->text->so) - 4);
	(free(sub), sub = ft_substr(data->text->so, i, 4));
	if (ft_strncmp(sub, ".xpm", 4) != 0)
		return (free(sub), ft_putstr_fd("Error\nInvalid text\n", 2), false);
	i = ((int)ft_strlen(data->text->we) - 4);
	(free(sub), sub = ft_substr(data->text->we, i, 4));
	if (ft_strncmp(sub, ".xpm", 4) != 0)
		return (free(sub), ft_putstr_fd("Error\nInvalid text\n", 2), false);
	i = ((int)ft_strlen(data->text->ea) - 4);
	free(sub);
	sub = ft_substr(data->text->ea, i, 4);
	if (ft_strncmp(sub, ".xpm", 4) != 0)
		return (free(sub), ft_putstr_fd("Error\nInvalid text\n", 2), false);
	return (free(sub), true);
}

static int	check_double(char *texture,
	const char *data_texture, char *t1, char *t2)
{
	char	*tmp;

	t2 = ft_strtrim(texture, data_texture);
	if (t2 == NULL)
		return (free(t1), false);
	tmp = ft_strtrim(t2, " ");
	if (tmp == NULL || ft_strlen(tmp) > 2)
		return (free(t2), free(tmp), free(t1),
			ft_putstr_fd("Error\nDuplicate texture\n", 2), false);
	(free(t2), free(tmp));
	return (true);
}

int	double_id(t_file *data, char *t1, char *t2, int i)
{
	int			num_text;
	int			j;
	const char	*prefixes[] = {"NO ", "SO ", "EA ", "WE ", "F ", "C "};
	const char	*text[] = {data->text->no, data->text->so,
		data->text->ea, data->text->we, data->text->f, data->text->c};

	num_text = sizeof(prefixes) / sizeof(prefixes[0]);
	while (i++, data->texture[i] != NULL)
	{
		t1 = ft_strtrim(data->texture[i], " ");
		if (t1 == NULL)
			return (ft_putstr_fd("Error\nMalloc\n", 2), false);
		j = -1;
		while (j++, j < num_text)
		{
			if (ft_strncmp(t1, prefixes[j], ft_strlen(prefixes[j])) == 0)
			{
				if (check_double(data->texture[i], text[j], t1, t2) == false)
					return (false);
				break ;
			}
		}
		free(t1);
	}
	return (true);
}
