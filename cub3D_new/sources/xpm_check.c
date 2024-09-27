/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:44:20 by miturk            #+#    #+#             */
/*   Updated: 2024/09/22 16:12:53 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	open_texture_file(const char *text)
{
	int	fd;

	fd = open(text, O_RDONLY);
	if (fd == -1)
		ft_putstr_fd("Error\nCannot open texture\n", 2);
	return (fd);
}

ssize_t	read_texture_file(int fd, char *buffer, size_t buffer_size)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, buffer_size - 1);
	if (bytes_read <= 0)
		(close(fd), ft_putstr_fd("Error\nCannot read texture\n", 2));
	else
		buffer[bytes_read] = '\0';
	return (bytes_read);
}

int	parse_texture_header(const char *header_line, int *width, int *height)
{
	*width = 0;
	*height = 0;
	while (*header_line >= '0' && *header_line <= '9')
	{
		*width = *width * 10 + (*header_line - '0');
		header_line++;
	}
	if (*header_line != ' ')
		return (ft_putstr_fd("Error\nInvalid texture header\n", 2), false);
	header_line++;
	while (*header_line >= '0' && *header_line <= '9')
	{
		*height = *height * 10 + (*header_line - '0');
		header_line++;
	}
	if (*header_line != ' ')
		return (ft_putstr_fd("Error\nInvalid texture header\n", 2), false);
	return (true);
}

int	validate_texture_dimensions(int width, int height)
{
	if (width != 64 || height != 64)
		return (ft_putstr_fd("Error\nTexture is not 64x64\n", 2), false);
	return (true);
}

int	xpm_check(t_data *data, char *text, int width, int height)
{
	char	buffer[BUFFER_SIZE];
	char	*header_line;
	ssize_t	bytes_read;
	int		fd;

	(void)data;
	fd = open_texture_file(text);
	if (fd == -1)
		return (false);
	bytes_read = read_texture_file(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (close(fd), false);
	header_line = ft_strnstr(buffer, "\"", bytes_read);
	if (!header_line)
		return (close(fd),
			ft_putstr_fd("Error\nInvalid texture format\n", 2), false);
	header_line++;
	if (!parse_texture_header(header_line, &width, &height))
		return (close(fd), false);
	close(fd);
	return (validate_texture_dimensions(width, height));
}
