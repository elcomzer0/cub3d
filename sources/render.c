/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:05 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/21 00:55:02 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

//FOR TESTING PURPOSES ONLY
void map_test(t_data *data)
{
    int map[MAP_SIZE][MAP_SIZE] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
   // data->map = map;
    data->map_offset_x = (WIDTH - (MAP_SIZE * TILE_SIZE) ) / 2;
    data->map_offset_y = (HEIGHT - (MAP_SIZE * TILE_SIZE) ) / 2;
    draw_map(data, map, data->map_offset_x, data->map_offset_y);
    
}


//FOR TESTING PURPOSES ONLY
void raycasting(t_data *data, int map[MAP_SIZE][MAP_SIZE], int map_offset_x, int map_offset_y)
{
    //t_point player_center = {map_offset_x + data->player_x * TILE_SIZE + TILE_SIZE / 2, map_offset_y + data->player_y * TILE_SIZE + TILE_SIZE / 2};
    (void)map_offset_x;
    (void)map_offset_y;
    double ray_angle;
    double ray_dir_x, ray_dir_y;
    int map_x, map_y;
    double side_dist_x, side_dist_y;
    double delta_dist_x, delta_dist_y;
    double perp_wall_dist;
    int step_x, step_y;
    int hit, side;

    for (int x = 0; x < WIDTH; x++)
    {
        ray_angle = data->arrow_angle + (FOV / 2) + ((double)x / WIDTH) * FOV;
        ray_dir_x = cos(ray_angle * (M_PI / 180));
        ray_dir_y = sin(ray_angle * (M_PI / 180));
        
        map_x = data->player_x;
        map_y = data->player_y;

        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (data->player_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - data->player_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->player_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - data->player_y) * delta_dist_y;
        }
        
        hit = 0;
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map[map_y][map_x] == 1)
            {
                hit = 1;
            }
        }

        if (side == 0)
        {
            perp_wall_dist = (map_x - data->player_x + (1 - step_x) / 2) / ray_dir_x;
        }
        else
        {
            perp_wall_dist = (map_y - data->player_y + (1 - step_y) / 2) / ray_dir_y;
        }
        
        int line_height = (int)(HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0)
        {
            draw_start = 0;
        }
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT)
        {
            draw_end = HEIGHT - 1;
        }
        
        int color = (side == 1) ? 0x00FF0000 : 0x0000FF00;
        for (int y = draw_start; y < draw_end; y++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}