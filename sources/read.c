/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:11 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/02 19:37:47 by jorgonca         ###   ########.fr       */
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
	/* while(i > 0)
	{
		printf("data->z_values[%d] = %p\n", i, data->z_values[i]);
		i--;
	}*/
}

int	read_width(char *file, t_data *data)
{
	(void)file;
	char	*line;
	int		fd;
	int		width;

	fd = 0;
	fd = ft_open(file, fd, data);
	line = get_next_line(fd);
	width = ft_wordcounter(line, ' ');
	free(line);
	return (width);
}

int	read_height(char *file, t_data *data)
{
	(void)file;
	char	*line;
	int		fd;
	int		height;

	fd = 0;
	fd = ft_open(file, fd, data);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
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
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(data);
		//ft_printf("ERROR %s\n", strerror(error_code));
		close(fd);
		exit(1);
	}
	return (fd);
}

void find_player_pos(t_data *data, int  **z_values)
{
	int x;
	int y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (z_values[y][x] == atoi("N") || z_values[y][x] == atoi("S") 
			|| z_values[y][x] == atoi("E") || z_values[y][x] == atoi("W"))
			{
				data->player_x = x;
				data->player_y = y;
				data->z_values[y][x] = 0;
				if (z_values[y][x] == atoi("N"))
					data->start_angle = NORTH_FOV;
				else if (z_values[y][x] == atoi("S"))
					data->start_angle = SOUTH_FOV;
				else if (z_values[y][x] == atoi("E"))
					data->start_angle = EAST_FOV;
				else if (z_values[y][x] == atoi("W"))
					data->start_angle = WEST_FOV;
				break;
			}
			x++;
		}
		printf("z_values[%d][%d] = %d\n", y, x, z_values[y][x]);
		y++;
	}
	printf("data->player_x: %d\n", data->player_x);
	printf("data->player_y: %d\n", data->player_y);
	printf("data->start_angle: %f\n", data->start_angle);
}

void create_map_coord(t_data *data)
{
	int x;
	int y;
	
	y = 0;
	data->map_coord = (t_point **)malloc(sizeof(t_point *) * (data->map_height + 1));
	while(y < data->map_height)
	{
		data->map_coord[y] = (t_point *)malloc(sizeof(t_point) * (data->map_width + 1));
		x = 0;
		while(x < data->map_width)
		{
			data->map_coord[y][x].x = x;
			data->map_coord[y][x].y = y;
			x++;
		}
		y++;
	}
	//print map_coord
	/* int i = 0;
	while(i < data->map_height)
	{
		int j = 0;
		while(j < data->map_width)
		{
			printf("map_coord[%d][%d]: %f, %f\n", i, j, data->map_coord[i][j].x, data->map_coord[i][j].y);
			j++;
		}
		i++;
	printf("\n");
	} */
}



void	ft_info_read(char *file, t_data *data)
{
	char	*line;
	int		i;
	int	fd;
	
	fd = 0;
	
	fd = ft_open(file, fd, data);
	data->map_height = read_height(file, data);
	data->map_width = read_width(file, data);
	ft_init_z(data);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		fill_values(data->z_values[i], line, data);
		//printf("%s\n", line);
		//printf("z_values[%d]: %d\n", i, data->z_values[i][i]);
		free(line);
		
		line = get_next_line(fd);
		i++;
	}
	create_map_coord(data);
	find_player_pos(data, data->z_values);
	free(line);
	close(fd);
}