/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:11 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/01 16:26:50 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

void	ft_init_z(t_data *data)
{
	int	i;

	data->z_values = (int **)malloc(sizeof(int *) * (data->map_height));
	if (data->z_values == NULL)
	{
		perror("Error: Failed to allocate memory for z_values");
		ft_clean(data);
		//ft_destroy(data);
		exit(1);
	}
	i = 0;
	while (i < data->map_height)
	{
		data->z_values[i] = (int *)malloc(sizeof(int) * (data->map_width));
		if (data->z_values[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 20);
			//perror("");
			while (i-- > 0)
				free(data->z_values[i]);
			ft_clean(data);
			ft_destroy(data);
			exit(1);
		}
		i++;
	}
	//data->z_values[i] = NULL;
	/* while(i > 0)
	{
		printf("data->z_values[%d] = %p\n", i, data->z_values[i]);
		i--;
	}*/
}
int count_characters(char *line)
{
    int count = 0;
    while (line[count] != '\0' && line[count] != '\n')
    {
        count++;
    }
    return count;
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
	width = count_characters(line);
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


void fill_values(int *z_values, char *line, t_data *data)
{
    int i;

    i = 0;
    while (/* line[i] &&  */i < data->map_width)
    {
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
        {
            z_values[i] = -1; // Use -1 or any other special value to denote the player's position
            data->player_x = i;
            data->player_y = data->current_line;

            // Ensure the player struct is allocated
            if (!data->player)
            {
                data->player = (t_player **)malloc(sizeof(t_player *));
				if (!data->player)
				{
					perror("Error: Failed to allocate memory for player");
					ft_clean(data);
					//ft_destroy(data);
					exit(1);
				}
                data->player[0] = (t_player *)malloc(sizeof(t_player));
            	if (!data->player[0])
				{
					perror("Error: Failed to allocate memory for player");
					ft_clean(data);
					//ft_destroy(data);
					exit(1);
				}
				data->player[0]->pos = NULL;
			}
            if (!data->player[0]->pos)
            {
                data->player[0]->pos = (t_point **)malloc(sizeof(t_point *));
                if (!data->player[0]->pos)
				{
					perror("Error: Failed to allocate memory for player");
					ft_clean(data);
					//ft_destroy(data);
					exit(1);
				}
				data->player[0]->pos[0] = (t_point *)malloc(sizeof(t_point));
				if (!data->player[0]->pos[0])
				{
					perror("Error: Failed to allocate memory for player");
					ft_clean(data);
					//ft_destroy(data);
					exit(1);
				}

			}

            data->player[0]->pos[0]->x = i;
            data->player[0]->pos[0]->y = data->current_line;
// dx and dy needs to be initialized here
            if (line[i] == 'N')
			{
                data->player[0]->angle = 90;
				data->player[0]->dx = 0;
				data->player[0]->dy = -1;
				data->raycast->plane[0]->x = 0.66; // Camera plane for facing North
    			data->raycast->plane[0]->y = 0; 
			}

            else if (line[i] == 'S')
			{
                data->player[0]->angle = 270;
				data->player[0]->dx = 0;
				data->player[0]->dy = 1;
				data->raycast->plane[0]->x = -0.66; // Camera plane for facing South
    			data->raycast->plane[0]->y = 0;
			}
            else if (line[i] == 'W')
			{
                data->player[0]->angle = 180;
				data->player[0]->dx = -1;
				data->player[0]->dy = 0;
				data->raycast->plane[0]->x = 0; 
    			data->raycast->plane[0]->y = -0.66;
			}
            else if (line[i] == 'E')
			{
                data->player[0]->angle = 0;
				data->player[0]->dx = 1;
				data->player[0]->dy = 0;
				data->raycast->plane[0]->x = 0;
    			data->raycast->plane[0]->y = 0.66;
			}
        }
        else if (line[i] == '1' || line[i] == '0' || line[i] == '2' || line[i] == '3' || line[i] == '4')
        {
            z_values[i] = line[i] - '0'; // Convert '1' or '0' character to integer 1 or 0
        }
        else
        {
            // Handle unexpected characters
            z_values[i] = 0; // Default to 0 for unexpected characters
        }
        i++;
    }
    /* while (i < data->map_width)
    {
        z_values[i] = 0; // Ensure the rest of the values are set to 0 if the line is shorter than map_width
        i++;
    } */
}


int	ft_open(char *file, int fd, t_data *data)
{
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(data);
		close(fd);
		exit(1);
	}
	return (fd);
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

void print_z_values(t_data *data)
{
	int i = 0;
	int j = 0;
	while(i < data->map_height)
	{
		j = 0;
		while(j < data->map_width)
		{
			printf("z_values[%d][%d]: %d\n", i, j, data->z_values[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void find_player_pos(t_data *data, int **z_values)
{
	(void)z_values;
    // Print the player's position and orientation
	//write(1, "Player position: ", 18);
    if (data->player)
    {
        printf("Player position: (%f, %f)\n", data->player[0]->pos[0]->x, data->player[0]->pos[0]->y);
        printf("Player angle: %f\n", data->player[0]->angle);
    }
    else
    {
        printf("No player found in the map.\n");
    }
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
	while (line && i < data->map_height)
	{
		data->current_line = i;
		fill_values(data->z_values[i], line, data);
		free(line);
		
		line = get_next_line(fd);
		i++;
	}
	//print_z_values(data);
	//create_map_coord(data);
	
	find_player_pos(data, data->z_values);
	free(line);
	close(fd);
}