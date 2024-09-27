/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:31 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/25 16:36:36 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	m_free(t_data *data)
{
	ft_free(data->file);
	ft_clean(data);
	if (data->file->text != NULL)
		free(data->file->text);
	if (data->file != NULL)
		free(data->file);
	if (data->player != NULL)
		free(data->player);
	if (data != NULL)
		free(data);
}

int	the_start(t_data *data, char **av)
{
	t_text	*text;

	text = ft_calloc(1, sizeof(t_text));
	if (text == NULL)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2),
			free(data->file), free(data->player), free(data), false);
	data->file->text = text;
	if (data->file->text == NULL)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2),
			free(text), free(data->file), free(data->player),
			free(data), false);
	if (work_split(data, data->file, av) == false)
		return (free(data->player), free(text),
			free(data->file), free(data), false);
	data->z_values = NULL;
	if (map_conversion(data, 0) == false)
		return (free(text), free(data->file),
			free(data->player), free(data), false);
	if (the_handover(data), ft_init(data, -1) == false)
		return (ft_free(data->file), free_z_values(data),
			free(text), free(data->player),
			free(data->file), free(data), false);
	return (true);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_file		*file;
	t_player	*player;

	if (ac == 2)
	{
		data = ft_calloc(1, sizeof(t_data));
		if (data == NULL)
			(ft_putstr_fd("Error\nMalloc failed\n", 2), exit(1));
		file = ft_calloc(1, sizeof(t_file));
		if (file == NULL)
			(ft_putstr_fd("Error\nMalloc failed\n", 2), free(data), exit(1));
		player = ft_calloc(1, sizeof(t_player));
		if (player == NULL)
			(ft_putstr_fd("Error\nMalloc failed\n", 2),
				free(file), free(data), exit(1));
		data->file = file;
		data->player = player;
		if (data->player == NULL || data->file == NULL)
			(free(data), free(file), free(player), exit(1));
		if (the_start(data, av) == false)
			(exit(1));
		return (0);
	}
	return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 1);
}

void	the_handover(t_data *data)
{
	data->map_width = data->file->line_len;
	data->map_height = data->file->line_hei;
	data->player->pos[0] = (double)data->file->pos[0] + 0.5;
	data->player->pos[1] = (double)data->file->pos[1] + 0.5;
}
