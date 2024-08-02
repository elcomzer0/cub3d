/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:35 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/02 17:33:26 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

/*init of map coordinates and set center of the map
Center of the map is the center of the map_img. Calculated
by x and y coordinates of left upper most pos of pixel. This will define the position
of the player accordingly where the pixel of the image is.
First define center of map inside the image. create coordinates by size of map and tiles.
then position player_pos at center pixel of the tile. Tiles correspond to 64px x 64 px. which
again correspont to float 1.0 x 1.0 in math. 0.5 x 0.5 would be the center of tile and
centered 32 x 32px. HOW?*/
/* void (set_map_to_center)(t_data *data)
{}

void init_map_coord(t_data *data)
{}

//init of position
int open_map(t_data *data, char **buf)
{

    //data->fd = open(data->map_name, O_RDONLY);
    //ft_open(data->map_name, fd, buf);
    ft_info_read(data->map_name, data);     
    
    return (0);
}

int map_to_buf(t_data *data) //int map[MAP_SIZE][MAP_SIZE])
{
    
    int map[MAP_SIZE][MAP_SIZE] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };


    data->map_buf = (char **)malloc(sizeof(char *) * MAP_SIZE * MAP_SIZE);
    if (!buf)
    {
        write(2, "Error: malloc failed\n", 20);
        return (1);
    }
    open_map(data, data->map_buf);
    
    return (0);
} */

/* void check_map_for_player(t_data *data, char **buf)
{} */
/* void check_player_pos(t_data *data, char pos)
{
    if (pos == 'W')
    {
        data->player_pos = "W";
    }
    else if (pos == 'E')
    {
        data->player_pos = "E";
    }
    else if (pos == 'N')
    {
        data->player_pos = "N";
    }
    else if (pos == 'S')
    {
        data->player_pos = "S";
    }
    else
    {
        //ft_clean(data);
        exit(1);
    }
} */

/* void switch_pos(t_data *data)
{
    if (strcmp(data->player_pos, "W") == 0)
    {
        data->arrow_angle = WEST_FOV;
        data->start_angle = data->arrow_angle;
    }
    else if (strcmp(data->player_pos, "E") == 0)
    {
        data->arrow_angle = EAST_FOV;
        data->start_angle = data->arrow_angle;
    }
    else if (strcmp(data->player_pos, "N") == 0)
    {
        data->arrow_angle = NORTH_FOV;
        data->start_angle = data->arrow_angle;
    }
    else if (strcmp(data->player_pos, "S") == 0)
    {
        data->arrow_angle = SOUTH_FOV;
        data->start_angle = data->arrow_angle;
    }
    else
    {
        //ft_clean(data);
        exit(1);
    }
} */

/* void switch_pos(t_data *data)
{
    int i;
    
    i = 0;
    while (i < 0)
    {
        if (strcmp(data->z_values[i], "W") == 0)
        {
            data->arrow_angle = WEST_FOV;
            data->start_angle = data->arrow_angle;
        }
        else if (strcmp(data->z_values[i], "E") == 0)
        {
            data->arrow_angle = EAST_FOV;
            data->start_angle = data->arrow_angle;
        }
        else if (strcmp(data->z_values[i], "N") == 0)
        {
            printf("1\n");
            data->arrow_angle = NORTH_FOV;
            data->start_angle = data->arrow_angle;
        }
        else if (strcmp(data->z_values[i], "S") == 0)
        {
            data->arrow_angle = SOUTH_FOV;
            data->start_angle = data->arrow_angle;
        }
        i++;
    }
} */
/* void init_pos(t_data *data)
{
    //pre version of the variables will be changed later on. 
    data->center_pos = malloc(sizeof(t_point *));
    if (data->center_pos)
    {
        *data->center_pos = malloc(sizeof(t_point));
        if (*data->center_pos)
        {
            (*data->center_pos)->x = WIDTH / 2;
            (*data->center_pos)->y = HEIGHT / 2;
        }
    } */
   /*  data->player_pos = data->center_pos;
    data->arrow_angle = NORTH_FOV;
    data->start_angle = data->arrow_angle; */

    //define starting positions by player position and its directional view
    //check_player_pos(data, data->player_pos);
   /* switch_pos(data);
} */

/* int init_pos(t_data *data)
{
    switch_pos(data);
} */


//void init_colors(t_data *data)

//void init_textures(t_data *data)

//void init_math(t_data *data)


int ft_init(t_data *data)
{
    // t_point center;
    
    // data->player_x = 1;
    // data->player_y = 1;
    
    // center = (t_point){data->map_offset_x + data->player_x * TILE_SIZE + TILE_SIZE / 2, data->map_offset_y + data->player_y * TILE_SIZE + TILE_SIZE / 2};
    
    
    //map_to_buf(data);
    //open_map(data, data->map_buf);
    ft_info_read(data->map_name, data);
    
    
 /*    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
    //data->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    //data->map_addr = mlx_get_data_addr(data->map_img, &data->bpp, &data->line_length, &data->endian);

    map_test(data);
    cub_draw(data);
    //mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    //mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 2, 1L<<0, key_hook_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_hook_release, data);

    cub_menu(data);
    
    mlx_hook(data->win, 17, 0, ft_destroy, data);
    mlx_loop(data->mlx); */
    return (0);
}