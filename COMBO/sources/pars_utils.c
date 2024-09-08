/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:16:53 by miturk            #+#    #+#             */
/*   Updated: 2024/09/08 14:02:09 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	init_file(t_file *data)
{
	data->text->colorf = NULL;
	data->text->colorc = NULL;
	data->text->no = NULL;
	data->text->so = NULL;
	data->text->we = NULL;
	data->text->ea = NULL;
	data->text->f = NULL;
	data->text->c = NULL;
	data->texture = NULL;
	data->file = NULL;
	data->map = NULL;
	data->line_len = 0;
	data->line_hei = 0;
	data->p_flag = 0;
	data->pos[0] = 0;
	data->pos[1] = 0;
	data->i = 0;
}

void	ft_free(t_file *data)
{
	if (data->file != NULL)
		free_array(data->file);
	if (data->texture != NULL)
		free_array(data->texture);
	if (data->map != NULL)
		free_array(data->map);
	if (data->text->no != NULL)
		free(data->text->no);
	if (data->text->so != NULL)
		free(data->text->so);
	if (data->text->we != NULL)
		free(data->text->we);
	if (data->text->ea != NULL)
		free(data->text->ea);
	if (data->text->f != NULL)
		free(data->text->f);
	if (data->text->c != NULL)
		free(data->text->c);
	if (data->text->colorf != NULL)
		free_array(data->text->colorf);
	if (data->text->colorc != NULL)
		free_array(data->text->colorc);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;	
		i++;
	}
	(free(array), array = NULL);
}

int	*player_pos(t_file *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (is_player(data->map[i][j]) && data->p_flag == 0
				&& i < data->line_hei - 1)
			{
				data->pos[0] = i;
				data->pos[1] = j;
				data->player_direction = data->map[i][j];
				data->p_flag = 1;
			}
			else if (data->p_flag == 1 && (is_player(data->map[i][j])))
				return (ft_putstr_fd("Error: Invalid map: player count\n", 2),
					NULL);
			j++;
		}
		i++;
	}
	return (data->p_flag = 0, data->pos);
}

int	file_check(t_file *data, int i, char *tmp)
{
	while (i++, data->file[i] != NULL)
	{
		if (skip_textures(data) == data->i || skip_textures(data) == i
			|| ft_strchr(data->file[i], '\t') != NULL)
			return (ft_putstr_fd("Error: Invalid file: File\n", 2), false);
		while (is_texture(data, i, 0) == true || data->file[i][0] == '\n')
			i++;
		if (data->file[i][0] == ' ' || ft_isalnum(data->file[i][0]) != 0)
		{
			tmp = ft_strtrim(data->file[i], " ");
			if (tmp == NULL)
				return (ft_putstr_fd("Error: Malloc failed\n", 2), false);
			if ((ft_isalnum(tmp[0]) != 0 && data->file[i][0] != '\n')
				|| is_texture(data, i, 0) != true)
			{
				if (ft_strchr(tmp, '1') == NULL)
					return (free(tmp),
						ft_putstr_fd("Error: Invalid file: Line\n", 2), false);
			}
			else if (tmp[0] == '\n' && data->file[i][0] == ' ')
				return (free(tmp),
					ft_putstr_fd("Error: Invalid file: Line\n", 2), false);
			free(tmp);
		}
		else
			return (ft_putstr_fd("Error: Invalid file: Line\n", 2), false);
	}
	return (true);
}
