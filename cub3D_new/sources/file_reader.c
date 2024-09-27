/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:35:12 by ggwagons          #+#    #+#             */
/*   Updated: 2024/09/22 16:10:40 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	work_split(t_data *data, t_file *file, char **argv)
{
	init_file(file);
	if (for_file(file, argv) == false)
		return (false);
	if (for_text(file) == false)
		return (false);
	if (for_map(file) == false)
		return (false);
	if (xpm_check(data, file->text->no, 0, 0) == false
		|| xpm_check(data, file->text->so, 0, 0) == false
		|| xpm_check(data, file->text->we, 0, 0) == false
		|| xpm_check(data, file->text->ea, 0, 0) == false)
		return (ft_free(file), false);
	return (true);
}

int	for_file(t_file *data, char **argv)
{
	if (check_name(argv) == false)
		return (false);
	if (check_access(data, argv) == false)
		return (ft_free(data), false);
	if (file_fill(data, argv, 0) == NULL)
		return (ft_free(data), false);
	if (file_check(data, -1, NULL) == false)
		return (ft_free(data), false);
	return (true);
}

int	for_text(t_file *data)
{
	if (list_textures(data, -1, 0, NULL) == NULL)
		return (ft_free(data), false);
	if (check_textures(data, -1, NULL) == false)
		return (ft_free(data), false);
	if (double_id(data, NULL, NULL, -1) == false)
		return (ft_free(data), false);
	if (text_check(data) == false)
		return (ft_free(data), false);
	if (check_filetype(data) == false)
		return (ft_free(data), false);
	if (open_text(data) == false)
		return (ft_free(data), false);
	if (check_color(data) == false)
		return (ft_free(data), false);
	if (data->line_hei > INT_MAX || data->line_len > INT_MAX)
		return (ft_putstr_fd("Error\nInvalid file\n", 2),
			ft_free(data), false);
	return (true);
}

int	for_map(t_file *data)
{
	if (list_map(data) == NULL)
		return (ft_free(data), false);
	if (check_map(data, NULL, 0, 0) == false)
		return (ft_free(data), false);
	if (remove_newline(data, NULL, -1, 0) == false)
		return (ft_free(data), false);
	map_width(data);
	if (square_map(data, -1, 0, 0) == false)
		return (ft_free(data), false);
	if (player_pos(data) == NULL)
		return (ft_free(data), false);
	if (data->pos[0] == 0 || data->pos[1] == 0 || \
		data->pos[0] == (data->line_hei) || data->pos[1] == (data->line_len))
		return (ft_putstr_fd("Error\nInvalid map\n", 2),
			ft_free(data), false);
	if (valid_map(data, 0, 0) == false)
		return (ft_free(data), false);
	return (true);
}

int	open_text(t_file *data)
{
	int	fd;

	fd = open(data->text->no, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nCannot open NO texture\n", 2), false);
	close(fd);
	fd = open(data->text->so, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nCannot open SO texture\n", 2), false);
	close(fd);
	fd = open(data->text->we, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nCannot open WE texture\n", 2), false);
	close(fd);
	fd = open(data->text->ea, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nCannot open EA texture\n", 2), false);
	return (close(fd), true);
}
