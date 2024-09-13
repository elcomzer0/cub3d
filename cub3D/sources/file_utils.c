/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:26:10 by miturk            #+#    #+#             */
/*   Updated: 2024/09/13 15:35:20 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	check_name(char **argv)
{
	int	i;

	i = (int)ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][i - 5], "/.cub", 5) == 0)
		return (ft_putstr_fd("Error:\nInvalid file\n", 2), false);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4) != 0)
		return (ft_putstr_fd("Error:\nInvalid file\n", 2), false);
	return (true);
}

int	check_access(t_file *data, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error:\nCannot open file\n", 2), false);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), ft_putstr_fd("Error:\nFunction error\n", 2), false);
	while (line != NULL)
	{
		free(line);
		data->i++;
		line = get_next_line(fd);
	}
	close(fd);
	if (data->i < 8 || data->i > INT_MAX)
		return (ft_putstr_fd("Error:\nInvalid size of file\n", 2), false);
	return (data->i);
}

char	**file_fill(t_file *data, char **argv, int j, char *tmp)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error:\nInvalid file\n", 2), NULL);
	data->file = ft_calloc((data->i + 1), sizeof(char *));
	if (data->file == NULL)
		return (close(fd), ft_putstr_fd("Error:\nMalloc error\n", 2), NULL);
	tmp = get_next_line(fd);
	if (tmp == NULL)
		return (close(fd), data->file[j] = NULL,
			ft_putstr_fd("Error:\nFunction error\n", 2), NULL);
	while (j < data->i && tmp != NULL)
	{
		if (tmp == NULL)
			return (close(fd), data->file[j] = NULL,
				ft_putstr_fd("Error:\nFunction error\n", 2), NULL);
		data->file[j] = ft_strdup(tmp);
		if (data->file[j] == NULL)
			return (free(tmp), ft_putstr_fd("Error:\nFunction\n", 2), NULL);
		(free(tmp), tmp = get_next_line(fd));
		j++;
	}
	return (close(fd), data->file[j] = NULL, data->file);
}

void	free_z_values_fail(t_data *data, int i, int j)
{
	j = 0;
	while (j < i)
	{
		free(data->z_values[i]);
		j++;
	}
	free(data->z_values);
	data->z_values = 0;
}

int	map_conversion(t_data *data, int i)
{
	int	j;

	data->z_values = (int **)malloc(sizeof(int *)
			* (data->file->line_hei));
	if (data->z_values == NULL)
		return (ft_free(data->file),
			ft_putstr_fd("Error:\nMalloc\n", 2), false);
	while (data->file->map[i] != NULL)
	{
		data->z_values[i] = (int *)malloc(sizeof(int)
				* (data->file->line_len));
		if (data->z_values[i] == NULL)
			return (free_z_values_fail(data, 0, i), ft_free(data->file),
				ft_putstr_fd("Error:\nMalloc\n", 2), false);
		j = 0;
		while (data->file->map[i][j] != '\0')
		{
			data->z_values[i][j] = change_value(data->file->map[i][j] - '0');
			j++;
		}
		i++;
	}
	return (true);
}
