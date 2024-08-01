/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AVP <AVP@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:11 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/31 15:57:20 by AVP              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

void	ft_init_z(t_data *data)
{
	int	i;

	data->z_values = (int **)malloc(sizeof(int *) * (data->map_height + 1));
	if (data->z_values == NULL)
	{
		perror("Error: Failed to allocate memory for z_values");
		//ft_printf("Error message: %s\n", strerror(12));
		ft_destroy(data);
		exit(1);
	}
	i = 0;
	while (i < data->map_height)
	{
		data->z_values[i] = (int *)malloc(sizeof(int) * (data->map_width + 1));
		if (data->z_values[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 20);
			//ft_printf("Error: Failed to allocate memory for z_values[%d]: ", i);
			perror("");
			//ft_printf("Error message: %s\n", strerror(12));
			ft_destroy(data);
			exit(1);
		}
		i++;
	}
	data->z_values[i] = NULL;
}

int	read_width(char *file, t_data *data)
{
	(void)file;
	char	*line;
	//int		fd;
	int		width;

	//fd = 0;
	//fd = ft_open(file, fd, data);
	line = get_next_line(data->fd);
	width = ft_wordcounter(line, ' ');
	free(line);
	return (width);
}

int	read_height(char *file, t_data *data)
{
	(void)file;
	char	*line;
	//int		fd;
	int		height;

	//fd = 0;
	//fd = ft_open(file, fd, data);
	height = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(data->fd);
	}
	close (data->fd);
	free(line);
	return (height);
}

void	fill_values(int *line_z, char *line, t_data *data)
{
	int		i;
	char	**nums;

	nums = ft_split(line, ' ');
	if (!nums)
	{
		free(data);
		exit(1);
	}
	i = 0;
	while (nums[i])
	{
		line_z[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}


int	ft_open(char *file, int fd, t_data *data)
{
	//int	error_code;

	//error_code = 2;
	data->fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(data);
		//ft_printf("ERROR %s\n", strerror(error_code));
		close(fd);
		exit(1);
	}
	return (fd);
}

void	ft_info_read(char *file, t_data *data)
{
	char	*line;
	int		i;

	data->fd = 0;
	
	data->fd = ft_open(file, data->fd, data);
	data->map_height = read_height(file, data);
	data->map_width = read_width(file, data);
	ft_init_z(data);
	line = get_next_line(data->fd);
	i = 0;
	while (line)
	{
		fill_values(data->z_values[i], line, data);
		free(line);
		line = get_next_line(data->fd);
		i++;
	}
	free(line);
	close(data->fd);
}