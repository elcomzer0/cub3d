/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:13:08 by miturk            #+#    #+#             */
/*   Updated: 2024/09/22 13:49:50 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

char	*ft_read_from_buffer_newline(char **line_buffer)
{
	int		i;
	char	*ab_new;
	char	*new_string;

	i = 0;
	new_string = *line_buffer;
	if (!*line_buffer)
		return (NULL);
	while ((*line_buffer)[i] != '\n' && (*line_buffer)[i] != '\0')
		i++;
	if ((*line_buffer)[i] == '\n')
		i++;
	ab_new = (char *)malloc(sizeof(char) * (i + 1));
	if (!ab_new)
		return (free(*line_buffer), *line_buffer = NULL, NULL);
	ab_new[i] = '\0';
	i = 0;
	while (new_string[i] != '\n' && (*line_buffer)[i] != '\0')
	{
		ab_new[i] = new_string[i];
		i++;
	}
	if (new_string[i] == '\n')
		ab_new[i] = new_string[i];
	return (ab_new);
}

char	*ft_clean_buffer(char **line_buffer)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	if (!*line_buffer)
		return (NULL);
	while ((*line_buffer)[i] != '\n' && (*line_buffer)[i])
		i++;
	if (!*line_buffer)
		return (free(*line_buffer), *line_buffer = NULL, NULL);
	rest = (char *)malloc(sizeof(char) * get_strlen(*line_buffer) - i + 1);
	if (!rest)
		return (free(rest), free(*line_buffer), *line_buffer = NULL, NULL);
	i++;
	j = 0;
	while ((*line_buffer)[i + j])
	{
		rest[j] = (*line_buffer)[i + j];
		j++;
	}
	rest[j] = '\0';
	free(*line_buffer);
	return (*line_buffer = NULL, line_buffer = NULL, rest);
}

char	*ft_read_from_file_to_buffer(t_file *data, char **line_buffer)
{
	char	*new_string;
	int		byte;

	byte = 1;
	new_string = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_string)
		return (free(*line_buffer), *line_buffer = NULL, NULL);
	while (!get_strchr(*line_buffer, '\n') && byte != 0)
	{
		byte = read(data->fd, new_string, BUFFER_SIZE);
		if (byte == -1)
			return (free(*line_buffer), free(new_string),
				*line_buffer = NULL, NULL);
		if (byte == 0)
			return (free(new_string), NULL);
		new_string[byte] = '\0';
		*line_buffer = get_strjoin(*line_buffer, new_string, 0);
		if (!*line_buffer)
		{
			return (free(*line_buffer), *line_buffer = NULL, NULL);
		}
	}
	return (free(new_string), *line_buffer);
}

char	*get_next_line(t_file *data)
{
	static char	*line_buffer = NULL;
	char		*newline;
	char		*tmp;

	if (data->stop == true && line_buffer != NULL)
		return (free(line_buffer), line_buffer = NULL, NULL);
	if (data->stop == true && line_buffer == NULL)
		return (NULL);
	if (data->fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_read_from_file_to_buffer(data, &line_buffer);
	if (tmp)
		line_buffer = tmp;
	else
	{
		tmp = get_strdup(line_buffer);
		if (!tmp)
			return (free(line_buffer), line_buffer = NULL, NULL);
		return (free(line_buffer), line_buffer = NULL, tmp);
	}
	if (!line_buffer)
		return (free(line_buffer), line_buffer = NULL, NULL);
	newline = ft_read_from_buffer_newline(&line_buffer);
	line_buffer = ft_clean_buffer(&line_buffer);
	return (newline);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	line = NULL;
// 	fd = open("../maps/simple_map.cub", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf(">>%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	printf(">>%s", line);
// 	free(line);
// 	if (!close(fd))
// 		return (0);
// }