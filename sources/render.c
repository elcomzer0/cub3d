/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:05 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/27 17:06:49 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

//FOR TESTING PURPOSES ONLY
void map_test(t_data *data)
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
   // data->map = map;
    data->map_offset_x = (WIDTH - (MAP_SIZE * TILE_SIZE) ) / 2;
    data->map_offset_y = (HEIGHT - (MAP_SIZE * TILE_SIZE) ) / 2;
    //t_vector center = {data->map_offset_x + data->player_x * TILE_SIZE + TILE_SIZE / 2, data->map_offset_y + data->player_y * TILE_SIZE + TILE_SIZE / 2};
    draw_map(data, map, data->map_offset_x, data->map_offset_y);
    
}


//FOR TESTING PURPOSES ONLY
/* void raycasting(t_data *data, int map[MAP_SIZE][MAP_SIZE], int map_offset_x, int map_offset_y)
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
        
        
    }
} */

void raycasting_v2(t_data *data, int map[MAP_SIZE][MAP_SIZE], float arrow_angle)
{
    //t_point player_center = {map_offset_x + data->player_x * TILE_SIZE + TILE_SIZE / 2, map_offset_y + data->player_y * TILE_SIZE + TILE_SIZE / 2};
    // (void)map_offset_x;
    // (void)map_offset_y;
    float fov = 90;
   // int blue_color = create_trgb(255, 0, 0, 255);
    //int magenta_color = create_trgb(255, 0, 255, 255);
    double ray_angle;
    double ray_dir_x, ray_dir_y;
    int map_x, map_y;
    double side_dist_x, side_dist_y;
    double delta_dist_x, delta_dist_y;
    double perp_wall_dist;
    int step_x, step_y;
    int hit, side;
    
   // (void)arrow_angle;
    float arrow_angle_t = arrow_angle;
    float start_angle = arrow_angle_t - 135;
    float angle_step = fov / WIDTH;
    
    for (int x = 0; x < WIDTH; x++)
    {
        ray_angle = start_angle + x * angle_step;
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
        //printf("2");
        int color = (side == 1) ? 0x00FF0000 : 0x0000FF00;
        for (int y = draw_start; y < draw_end; y++)
        {
            printf("1");
            my_mlx_pixel_put(data, x, y, color);
        }
        
    }
}

/* void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE], int map_offset_x, int map_offset_y)
{
    double ray_angle, ray_dir_x, ray_dir_y;
    int map_x, map_y;
    int hit;
    (void)map_offset_x;
    (void)map_offset_y;
    

    for (int x = 0; x < WIDTH; x++) {
        ray_angle = data->arrow_angle + (FOV / 2) - ((double)x / WIDTH) * FOV;
        ray_dir_x = cos(ray_angle * (M_PI / 180));
        ray_dir_y = sin(ray_angle * (M_PI / 180));

        double ray_x = data->player_x;
        double ray_y = data->player_y;

        hit = 0;
        while (!hit) {
            // Move the ray forward a small step
            ray_x += ray_dir_x * 0.1;
            ray_y += ray_dir_y * 0.1;

            map_x = (int)ray_x;
            map_y = (int)ray_y;

            // Check if the ray has hit a wall
            if (map[map_y][map_x] == 1) {
                hit = 1;
                my_mlx_pixel_put(data, map_x , map_y, 0xFFFFFF); // Draw white dot at wall collision with offset
            } else {
                my_mlx_pixel_put(data, map_x , map_y, 0xAAAAAA); // Draw gray dot for ray path with offset
            }
        }
    }
} */

/* void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE])
{
    int magenta_color = create_trgb(255, 0, 255, 255);
    int blue_color = create_trgb(255, 0, 0, 255);
    double ray_angle, ray_dir_x, ray_dir_y;
    int map_x, map_y;
    int hit;

    // Calculate the center of the screen
    int screen_center_x = WIDTH / 2;
    int screen_center_y = HEIGHT / 2;

    // Set player's position to the center of the screen
    data->player_x = screen_center_x;
    data->player_y = screen_center_y;

    for (int x = 0; x < WIDTH; x++) {
        ray_angle = data->arrow_angle + (FOV / 2) - ((double)x / WIDTH) * FOV;
        ray_dir_x = cos(ray_angle * (M_PI / 180));
        ray_dir_y = sin(ray_angle * (M_PI / 180));

        double ray_x = data->player_x;
        double ray_y = data->player_y;

        hit = 0;
        while (!hit) {
            // Move the ray forward a small step
            ray_x += ray_dir_x * 0.1;
            ray_y += ray_dir_y * 0.1;

            // Convert screen coordinates to map coordinates
            map_x = (int)(ray_x / TILE_SIZE);
            map_y = (int)(ray_y / TILE_SIZE);

            // Check bounds and if the ray has hit a wall
            if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE) {
                if (map[map_y][map_x] == 1) {
                    hit = 1;
                    my_mlx_pixel_put(data, x, (int)(ray_y - screen_center_y + HEIGHT / 2), blue_color); // Draw white dot at wall collision
                } else {
                    my_mlx_pixel_put(data, x, (int)(ray_y - screen_center_y + HEIGHT / 2), magenta_color); // Draw gray dot for ray path
                }
            } else {
                // Stop the ray if it goes out of map bounds
                hit = 1;
            }
        }
    }
} */

/* void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE])
{
    int magenta_color = create_trgb(255, 0, 255, 255);
    int blue_color = create_trgb(255, 0, 0, 255);
    double ray_angle, ray_dir_x, ray_dir_y;
    int hit, map_x, map_y;

    for (int x = 0; x < WIDTH; x++) {
        ray_angle = data->arrow_angle + (FOV / 2) - ((double)x / WIDTH) * FOV;
        ray_dir_x = cos(ray_angle * (M_PI / 180));
        ray_dir_y = sin(ray_angle * (M_PI / 180));

        double ray_x = data->player_x;
        double ray_y = data->player_y;
        hit = 0;

        while (!hit) {
            ray_x += ray_dir_x * 0.1;
            ray_y += ray_dir_y * 0.1;
            map_x = (int)(ray_x / TILE_SIZE);
            map_y = (int)(ray_y / TILE_SIZE);

            if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE) {
                if (map[map_y][map_x] == 1) {
                    hit = 1;
                    my_mlx_pixel_put(data, x, (int)(ray_y - data->player_y + HEIGHT / 2), blue_color);
                } else {
                    my_mlx_pixel_put(data, x, (int)(ray_y - data->player_y + HEIGHT / 2), magenta_color);
                }
            } else {
                hit = 1; // Stop the ray if it goes out of map bounds
            }
        }
    }
} */

/* void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE], float arrow_angle) //, float fov)
{
    float fov = FOV;
    int blue_color = create_trgb(255, 0, 0, 255);
    int magenta_color = create_trgb(255, 0, 255, 255);

    double ray_angle, ray_dir_x, ray_dir_y;
    int map_x, map_y;
    int hit;

    // Calculate the center of the screen
    int screen_center_x = WIDTH / 2;
    int screen_center_y = HEIGHT / 2;

    // Set player's position to the center of the screen
    data->player_x = screen_center_x;
    data->player_y = screen_center_y;

    // Calculate start and end angles for the FOV
    double start_angle = arrow_angle - (fov / 2);
    double end_angle = arrow_angle + (fov / 2);

    for (int x = 0; x < WIDTH; x++) {
        // Map screen x-coordinate to corresponding angle within the FOV
        end_angle = start_angle + FOV;
        ray_angle = start_angle + ((double)x / WIDTH) * (end_angle - start_angle);

        ray_dir_x = cos(ray_angle * (M_PI / 180));
        ray_dir_y = sin(ray_angle * (M_PI / 180));

        double ray_x = data->player_x;
        double ray_y = data->player_y;

        hit = 0;
        while (!hit) {
            ray_x += ray_dir_x * 0.1;
            ray_y += ray_dir_y * 0.1;

            map_x = (int)(ray_x / TILE_SIZE);
            map_y = (int)(ray_y / TILE_SIZE);

            if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE) {
                if (map[map_y][map_x] == 1) {
                    hit = 1;
                    my_mlx_pixel_put(data, x, (int)(ray_y - screen_center_y + HEIGHT / 2), blue_color); // Draw blue dot at wall collision
                } else {
                    my_mlx_pixel_put(data, x, (int)(ray_y - screen_center_y + HEIGHT / 2), magenta_color); // Draw magenta dot for ray path
                }
            } else {
                hit = 1; // Stop the ray if it goes out of map bounds
            }
        }
    }
} */

/* void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE], float arrow_angle)
{
    float fov = FOV;
    int blue_color = create_trgb(0, 0, 0, 255);
    int magenta_color = create_trgb(0, 0, 255, 255);

    double ray_angle, ray_dir_x, ray_dir_y;
    int map_x, map_y;
    int hit;

    // Calculate the center of the screen
    int screen_center_x = WIDTH / 2;
    int screen_center_y = HEIGHT / 2;

    // Set player's position to the center of the screen
    data->player_x = screen_center_x;
    data->player_y = screen_center_y;

    // Calculate start and end angles for the FOV
    double start_angle = arrow_angle - (fov / 2);
    //double end_angle = arrow_angle + (fov / 2);

    for (int x = 0; x < WIDTH; x++) {
        // Map screen x-coordinate to corresponding angle within the FOV
        ray_angle = start_angle + ((double)x / WIDTH) * fov;

        // Convert angle to radians
        ray_angle = ray_angle * (M_PI / 180);

        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);

        double ray_x = data->player_x;
        double ray_y = data->player_y;

        hit = 0;
        while (!hit) {
            ray_x += ray_dir_x * 0.1;
            ray_y += ray_dir_y * 0.1;

            map_x = (int)(ray_x / TILE_SIZE);
            map_y = (int)(ray_y / TILE_SIZE);

            if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE) {
                if (map[map_y][map_x] == 1) {
                    hit = 1;
                    my_mlx_pixel_put(data, x, (int)(ray_y - screen_center_y + HEIGHT / 2), blue_color); // Draw blue dot at wall collision
                } else {
                    my_mlx_pixel_put(data, x, (int)(ray_y - screen_center_y + HEIGHT / 2), magenta_color); // Draw magenta dot for ray path
                }
            } else {
                hit = 1; // Stop the ray if it goes out of map bounds
            }
        }
    }
} */

/* void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE], float arrow_angle)
{
    float fov = 135;
    int blue_color = create_trgb(255, 0, 0, 255);
    int magenta_color = create_trgb(255, 0, 255, 255);
    int yellow_color = create_trgb(255, 255, 255, 0); // Yellow for FOV lines

    double ray_angle, ray_dir_x, ray_dir_y;
    int map_x, map_y;
    int hit;

    // Calculate the center of the screen
    int screen_center_x = WIDTH / 2;
    int screen_center_y = HEIGHT / 2;

    // Set player's position to the center of the screen
    data->player_x = screen_center_x;
    data->player_y = screen_center_y;

    t_point center = {screen_center_x, screen_center_y};
    t_point line_end = {screen_center_x, screen_center_y - 100}; // Arbitrary length for FOV lines

    // Calculate FOV endpoints
    t_point fov_left_end = rotate_point(line_end, center, arrow_angle - (fov / 2));
    t_point fov_right_end = rotate_point(line_end, center, arrow_angle + (fov / 2));

    // Draw FOV lines
    draw_line(data, center.x, center.y, fov_left_end.x, fov_left_end.y, yellow_color);
    draw_line(data, center.x, center.y, fov_right_end.x, fov_right_end.y, yellow_color);

    // Calculate start and end angles for the FOV
    double start_angle = arrow_angle - (fov / 2);
    //double end_angle = arrow_angle + (fov / 2);

    // Calculate the angle step per pixel column
    double angle_step = fov / WIDTH;
//    printf("angle_step: %f\n", angle_step);
    for (int x = 0; x < WIDTH; x++) {
        // Calculate the ray angle for this column
        ray_angle = start_angle + (x * angle_step);

        // Convert angle to radians
        ray_angle = ray_angle * (M_PI / 180);

        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);
    //printf("ray_angle: %f\n", ray_angle);
        double ray_x = data->player_x;
        double ray_y = data->player_y;

        hit = 0;
        while (!hit) {
            ray_x += ray_dir_x * 1.0;
            ray_y += ray_dir_y * 1.0;

            map_x = (int)(ray_x / TILE_SIZE);
            map_y = (int)(ray_y / TILE_SIZE);
    //rintf("map_x: %d, map_y: %d\n", map_x, map_y);
            if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE) {
                if (map[map_y][map_x] == 1) {
                    hit = 1;
                    printf("hit\n");
                    my_mlx_pixel_put(data, x, (int)(ray_y - screen_center_y + HEIGHT / 2), blue_color); // Draw blue dot at wall collision
                } else {
                    printf("no hit\n");
                    my_mlx_pixel_put(data, x, (int)(ray_y - screen_center_y + HEIGHT / 2), magenta_color); // Draw magenta dot for ray path
                }
            } else {
                hit = 1; // Stop the ray if it goes out of map bounds
            }
        }
    }
} */

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
