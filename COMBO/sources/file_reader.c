/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:35:12 by ggwagons          #+#    #+#             */
/*   Updated: 2024/09/08 14:01:18 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	work_split(t_file *data, char **argv)
{
	init_file(data);
	if (for_file(data, argv) == false)
		return (false);
	if (for_text(data) == false)
		return (false);
	if (for_map(data) == false)
		return (false);
	return (true);
}

int	for_file(t_file *data, char **argv)
{
	if (check_name(argv) == false)
		return (false);
	if (check_access(data, argv) == false)
		return (ft_free(data), false);
	if (file_fill(data, argv, 0, NULL) == NULL)
		return (ft_free(data), false);
	if (file_check(data, -1, NULL) == false)
		return (ft_free(data), false);
	return (true);
}

int	for_text(t_file *data)
{
	if (list_textures(data, 0, 0, NULL) == NULL)
		return (ft_free(data), false);
	if (check_textures(data, -1, NULL) == false)
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
		return (ft_putstr_fd("Error: map too big\n", 2), ft_free(data), false);
	return (true);
}

int	for_map(t_file *data)
{
	if (list_map(data) == NULL)
		return (ft_free(data), false);
	if (check_map(data, NULL, 0, 0) == false)
		return (ft_free(data), false);
	(remove_newline(data), map_width(data));
	if (square_map(data, -1, 0, 0) == false)
		return (ft_free(data), false);
	if (player_pos(data) == NULL)
		return (ft_free(data), false);
	if (data->pos[0] == 0 || data->pos[1] == 0 || \
		data->pos[0] == (data->line_hei) || data->pos[1] == (data->line_len))
		return (ft_putstr_fd("Error: Wrong player position\n", 2),
			ft_free(data), false);
	if (valid_map(data, 0, 0) == false)
		return (ft_free(data), false);
	return (true);
}
