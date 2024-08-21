/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:05 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/21 18:24:00 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"


void rc_delta_dist(t_data *data)
{
   // write(1, "1\n", 2);
//printf( "ray_dir: %p\n", &data->raycast);   
 //   printf( "ray_dir: %f\n", data->raycast->ray_dir[0]->x);
    if (data->raycast->ray_dir[0] == NULL || data->raycast->delta_dist[0] == NULL)
    {
        write(2, "Error: ray_dir[0]->x is NULL\n", 30);
        return ;
    }
    if (data->raycast->ray_dir[0]->x == 0)
        data->raycast->delta_dist[0]->x = FLT_MAX;// 1e30;
    else
        data->raycast->delta_dist[0]->x = fabs(1 / data->raycast->ray_dir[0]->x);
    
    if (data->raycast->ray_dir[0]->y == 0)
        data->raycast->delta_dist[0]->y = FLT_MAX; // 1e30;
    else
        data->raycast->delta_dist[0]->y = fabs(1 / data->raycast->ray_dir[0]->y);
 //   printf( "ray_dir x: %f\n", data->raycast->ray_dir[0]->x);
  //  printf( "ray_dir y: %f\n", data->raycast->ray_dir[0]->y);


}

void rc_side_step(t_data *data)
{
    if (data->raycast->ray_dir[0] == NULL 
        || data->raycast->step[0] == NULL
        || data->raycast->side_dist[0] == NULL || data->player[0]->pos[0] == NULL)
    {
        write(2, "Error: ray_dir[0] or step[0] or side_dist[0] or player[0]->pos[0] is NULL\n", 75);
        return ;
    }
    if (data->raycast->ray_dir[0]->x < 0)
    {
        data->raycast->step[0]->x = -1;
        data->raycast->side_dist[0]->x = (data->player[0]->pos[0]->x - data->raycast->map_x) * data->raycast->delta_dist[0]->x;
    }
    else
    {
        data->raycast->step[0]->x = 1;
        data->raycast->side_dist[0]->x = (data->raycast->map_x + 1.0 - data->player[0]->pos[0]->x) * data->raycast->delta_dist[0]->x;
    }
    if (data->raycast->ray_dir[0]->y < 0)
    {
        data->raycast->step[0]->y = -1;
        data->raycast->side_dist[0]->y = (data->player[0]->pos[0]->y - data->raycast->map_y) * data->raycast->delta_dist[0]->y;
    }
    else
    {
        data->raycast->step[0]->y = 1;
        data->raycast->side_dist[0]->y = (data->raycast->map_y + 1.0 - data->player[0]->pos[0]->y) * data->raycast->delta_dist[0]->y;
    }
}

void rc_loop_hit(t_data *data)
{
    if (data->raycast->side_dist[0] == NULL
        || data->raycast->delta_dist[0] == NULL || data->raycast->step[0] == NULL)
    {
        write(2, "Error: side_dist[0] or delta_dist[0] or step[0] is NULL\n", 57);
        return ;    
    }
    while (data->raycast->hit == 0)
    {
        if (data->raycast->side_dist[0]->x < data->raycast->side_dist[0]->y)
        {
            data->raycast->side_dist[0]->x += data->raycast->delta_dist[0]->x;
            data->raycast->map_x += data->raycast->step[0]->x;
            data->raycast->side = 0;
        }
        else
        {
            data->raycast->side_dist[0]->y += data->raycast->delta_dist[0]->y;
            data->raycast->map_y += data->raycast->step[0]->y;
            data->raycast->side = 1;
        }
        if (data->z_values[data->raycast->map_y][data->raycast->map_x] > 0)
        {
            data->raycast->hit = 1;
        }
    }
}

void raycasting(t_data *data)
{
    int x;

    if (data == NULL || data->raycast == NULL
        || data->player == NULL
        || data->raycast->ray_dir[0] == NULL || data->player[0]->pos[0] == NULL)
        {
            write(2, "Error: One or more pointers are NULL\n", 38);
            return ;
        }
    for (x = 0; x < WIDTH; x++)
    {
    /* carmera_x and ray_dir */
        data->raycast->camera_x = 2 * x / (float)WIDTH - 1;
        printf("camera_x: %f\n", data->raycast->camera_x);
        data->raycast->ray_dir[0]->x = data->player[0]->dx + data->raycast->camera_x * data->raycast->plane[0]->x;
        data->raycast->ray_dir[0]->y = data->player[0]->dy + data->raycast->camera_x * data->raycast->plane[0]->y;
        printf("player[0]->dx: %f\n", data->player[0]->dx);
        printf("ray_dir[0]->x: %f\n", data->raycast->ray_dir[0]->x);
        printf("plane[0]->x: %f\n", data->raycast->plane[0]->x);
    /* int map_x and map_y */
        data->raycast->map_x = (int)data->player[0]->pos[0]->x;
        data->raycast->map_y = (int)data->player[0]->pos[0]->y;
        printf("data->player[0]->pos[0]->x: %f\n", data->player[0]->pos[0]->x);
        printf("data->player[0]->pos[0]->y: %f\n", data->player[0]->pos[0]->y);
        printf("map_x: %d\n", data->raycast->map_x);
        printf("map_y: %d\n", data->raycast->map_y);
        printf("plane[0]->y: %f\n", data->raycast->plane[0]->y);
        printf("ray_dir[0]->y: %f\n", data->raycast->ray_dir[0]->y);
        printf("(int)data->player[0]->pos[0]->x: %d\n", (int)data->player[0]->pos[0]->x);
        printf("(int)data->player[0]->pos[0]->y: %d\n", (int)data->player[0]->pos[0]->y);
    /* delta_dist */
        rc_delta_dist(data);
    /* side_dist and step */
        rc_side_step(data);
    /* while loop hit */
        rc_loop_hit(data);
    /* draw */
        if (data->raycast->side == 0)
            data->raycast->perp_wall_dist = (data->raycast->side_dist[0]->x - data->raycast->delta_dist[0]->x);
        else
            data->raycast->perp_wall_dist = (data->raycast->side_dist[0]->y - data->raycast->delta_dist[0]->y);
        printf("perp_wall_dist: %f\n", data->raycast->perp_wall_dist);
        data->raycast->line_height = (int)(HEIGHT / data->raycast->perp_wall_dist);    
        data->raycast->draw_start = -data->raycast->line_height / 2 + HEIGHT / 2;
        data->raycast->draw_end = data->raycast->line_height / 2 + HEIGHT / 2;
        
        printf("z_values: %d\n", data->z_values[data->raycast->map_y][data->raycast->map_x]);
        if (data->z_values[data->raycast->map_y][data->raycast->map_x] == COLOR_RED)
        {
            data->raycast->color = data->color->red;
            //write(2, "Error: z_values is not a valid color\n", 37);
        }
        else if (data->z_values[data->raycast->map_y][data->raycast->map_x] == COLOR_GREEN)
        {
            data->raycast->color = data->color->green;
        }
        else if (data->z_values[data->raycast->map_y][data->raycast->map_x] == COLOR_BLUE)
        {
            data->raycast->color = data->color->blue;
        }
        else if (data->z_values[data->raycast->map_y][data->raycast->map_x] == COLOR_MAGENTA)
        {
            data->raycast->color = data->color->magenta;
        }
        else
        {
            data->raycast->color = data->color->yellow;
        }
        printf("color: %d\n", data->raycast->color);
        for  (int y = 0; y < HEIGHT; y++)
        {
            //write(1, "1\n", 2);
            my_mlx_pixel_put(data, x, y, data->raycast->color);
            //write(1, "2\n", 2);
        }
    }
}





void print_map(int map[MAP_SIZE][MAP_SIZE]) {
    printf("Map data:\n");
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
}

void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE], float arrow_angle)
{
    float fov = 90; // Full FOV of 135 degrees
    int blue_color = create_trgb(255, 0, 0, 255);
    int magenta_color = create_trgb(255, 0, 255, 255);
    //int yellow_color = create_trgb(255, 255, 255, 0); // Yellow for FOV lines
    float arrow_angle_t = arrow_angle;

    double ray_angle, ray_dir_x, ray_dir_y;
    int map_x, map_y;
    int hit;

    // Print the map data for debugging
    //print_map(map);

    // Calculate the center of the screen
    int screen_center_x = WIDTH / 2;
    int screen_center_y = HEIGHT / 2;

    // Set player's position to the center of the screen
    data->player_x = screen_center_x;
    data->player_y = screen_center_y;

    // t_point center = {screen_center_x, screen_center_y};
    // t_point line_end = {screen_center_x, screen_center_y - 100}; // Arbitrary length for FOV lines

    // // Calculate FOV endpoints
    // t_point fov_left_end = rotate_point(line_end, center, arrow_angle_t - (fov / 2));
    // t_point fov_right_end = rotate_point(line_end, center, arrow_angle_t + (fov / 2));

    // Draw FOV lines
    //draw_line(data, center.x, center.y, fov_left_end.x, fov_left_end.y, yellow_color);
    //draw_line(data, center.x, center.y, fov_right_end.x, fov_right_end.y, yellow_color);

    // Calculate start and end angles for the FOV
    double start_angle = arrow_angle_t - 135; // start point must be here - 135. arro_angle must be included here for key manipulation
    //double end_angle = arrow_angle + (fov / 2);

    // Calculate the angle step per pixel column
    double angle_step = fov / WIDTH;
    
    //printf("Starting raycasting...\n");
    printf ("start_angle: %f\n", start_angle);
    printf("arrow_angle_t: %f\n", arrow_angle_t);
    printf("angle_step: %f\n", angle_step);
    for (int x = 0; x < WIDTH; x++)
    {
        // Calculate the ray angle for this column
        ray_angle = start_angle + (x * angle_step);

        // Convert angle to radians
        ray_angle = ray_angle * (M_PI / 180);
       // printf("ray_angle: %f\n", ray_angle);
        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);
        //printf("ray_dir_x: %f\n", ray_dir_x);
        //printf("ray_dir_y: %f\n", ray_dir_y);
        double ray_x = data->player_x;
        double ray_y = data->player_y;

        hit = 0;
        t_point ray_start = {data->player_x, data->player_y};
        t_point ray_end;

        while (!hit)
        {
            ray_x += ray_dir_x * 200.0; // Adjusted increment step for visibility
            ray_y += ray_dir_y * 200.0;

            map_x = (int)(ray_x / TILE_SIZE);
            map_y = (int)(ray_y / TILE_SIZE);

            //printf("Ray coordinates: (%f, %f) -> Map cell: (%d, %d)\n", ray_x, ray_y, map_x, map_y);

            if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE)
            {
                if (map[map_y][map_x] == 1)
                {
                    hit = 1;
                    ray_end.x = ray_x;
                    ray_end.y = ray_y;
                    //printf("Ray hit wall at x: %d, y: %d\n", (int)ray_x, (int)ray_y);
                    // Draw the hit point as a small circle
                    draw_circle(data, (int)ray_x, (int)ray_y, 3, blue_color);
                }
            }
            else
            {
                hit = 1; // Stop the ray if it goes out of map bounds
                //printf("Ray out of map bounds at x: %d, y: %d\n", (int)ray_x, (int)ray_y);
                ray_end.x = ray_x;
                ray_end.y = ray_y;
            }
        }

        // Draw the ray line from the start point to the end point
        draw_line(data, ray_start.x, ray_start.y, ray_end.x, ray_end.y, magenta_color);
    }

    //printf("Raycasting completed.\n");
}
