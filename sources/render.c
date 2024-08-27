/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:05 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/28 00:06:44 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"


/**
 * Calculates the delta distance for the ray casting algorithm.
 * The delta distance is the distance the ray has to move in the x or y direction
 * for the next step in the grid.
 *
 * @param data The main data structure containing the game state.
 */


void rc_delta_dist(t_data *data)
{
     //          printf("before delta_dist calc side_dist_x: %f, side_dist_y: %f\n", data->raycast->side_dist[0]->x, data->raycast->side_dist[0]->y);
    if(data->raycast->ray_dir[0]->x == 0)
        data->raycast->delta_dist[0]->x = DBL_MAX;
    else
        data->raycast->delta_dist[0]->x = fabs(1 / data->raycast->ray_dir[0]->x);
    if(data->raycast->ray_dir[0]->y == 0)
        data->raycast->delta_dist[0]->y = DBL_MAX;
    else
        data->raycast->delta_dist[0]->y = fabs(1 / data->raycast->ray_dir[0]->y);
    //printf("after delta_dist calc side_dist_x: %f, side_dist_y: %f\n", data->raycast->side_dist[0]->x, data->raycast->side_dist[0]->y);
    //printf("delta_dist_x: %f, delta_dist_y: %f\n", data->raycast->delta_dist[0]->x, data->raycast->delta_dist[0]->y);
   // printf("ray_dir_x: %f, ray_dir_y: %f\n", data->raycast->ray_dir[0]->x, data->raycast->ray_dir[0]->y);
}

/**
 * Calculates the initial side distance values for the ray casting algorithm.
 * The side distance is the distance the ray has to move in the x or y direction
 * to reach the next grid cell.
 *
 * @param data The main data structure containing the game state.
 */
void rc_side_step(t_data *data)
{
  /*   if (data->raycast->ray_dir[0] == NULL 
        || data->raycast->step[0] == NULL
        || data->raycast->side_dist[0] == NULL || data->player[0]->pos[0] == NULL)
    {
        write(2, "Error: ray_dir[0] or step[0] or side_dist[0] or player[0]->pos[0] is NULL\n", 75);
        return ;
    } */
         //  printf("before r_side_step calc side_dist_x: %f, side_dist_y: %f\n", data->raycast->side_dist[0]->x, data->raycast->side_dist[0]->y);

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
        //printf("@ here 1\n");
    }
    /* printf("after calc of side_dist data->raycast->side_dist[0]->x = %f\n", data->raycast->side_dist[0]->x);
    printf("after calc of side_dist data->raycast->side_dist[0]->y = %f\n", data->raycast->side_dist[0]->y); */
}

/**
 * Performs the ray casting loop to determine the hit point on a wall.
 *
 * This function is responsible for iterating the ray casting algorithm until a
 * wall is hit. It updates the map position and side distance values as the ray
 * moves through the grid. When a wall is hit, the wall type is stored in the
 * `wall_type` field of the `raycast` struct.
 *
 * @param data The main data structure containing the game state.
 */


void rc_loop_hit(t_data *data)
{
    if (data->raycast->side_dist[0] == NULL
        || data->raycast->delta_dist[0] == NULL || data->raycast->step[0] == NULL)
    {
        write(2, "Error: side_dist[0] or delta_dist[0] or step[0] is NULL\n", 57);
        return ;
    }
            //printf("before rc_loop_hit side_dist_x: %f, side_dist_y: %f\n", data->raycast->side_dist[0]->x, data->raycast->side_dist[0]->y);

    data->raycast->hit = 0;
    while (data->raycast->hit == 0)
    {
        if (data->raycast->side_dist[0]->x < data->raycast->side_dist[0]->y)
        {
            data->raycast->side_dist[0]->x += data->raycast->delta_dist[0]->x;
            data->raycast->map_x += data->raycast->step[0]->x;
            data->raycast->side = 0;
            //printf("step_x: %f, step_y: %f\n", data->raycast->step[0]->x, data->raycast->step[0]->y);
           printf("@ here 2\n");
        }
        else
        {
            data->raycast->side_dist[0]->y += data->raycast->delta_dist[0]->y;
            data->raycast->map_y += data->raycast->step[0]->y;
           // printf("step_x: %f, step_y: %f\n", data->raycast->step[0]->x, data->raycast->step[0]->y);
            data->raycast->side = 1;
        }
        if (data->raycast->map_x < 0 || data->raycast->map_x >= MAP_SIZE ||
            data->raycast->map_y < 0 || data->raycast->map_y >= MAP_SIZE)
        {
            // Handle out-of-bounds case
            printf("Out of bounds: %d, %d\n", data->raycast->map_x, data->raycast->map_y);
            break;
        }
        //only the first if is important for the wall type later
       printf("data->raycast->map_x: %d, data->raycast->map_y: %d\n", data->raycast->map_x, data->raycast->map_y);
       if (data->z_values[data->raycast->map_y][data->raycast->map_x] == '1')
       {
            data->raycast->hit = 1;
            data->raycast->wall_type = 1;  // Store the wall type
        }
    }
}

/**
 * Determines the color to use for a given wall type.
 *
 * This function takes a wall type integer and returns the corresponding color
 * value. The color values are retrieved from the `data->color` struct, which
 * likely contains the RGB values for each wall type.
 *
 * @param data The main data structure containing the game state.
 * @param wall_type The integer value representing the wall type.
 * @return The color value to use for the given wall type.
 */
int get_color(t_data *data, int wall_type)
{
    if (wall_type == 1)
        return data->color->red;
    else if (wall_type == 2)
        return data->color->green;
    else if (wall_type == 3)
        return data->color->blue;
    else if (wall_type == 4)
        return data->color->magenta;
    else if (wall_type == 5)
        return data->color->yellow;
    else 
        return 0; // Default color if wall type is not recognized
}

/**
 * Calculates the ray direction for a given x-coordinate in the rendering loop.
 *
 * This function calculates the ray direction vector based on the player's
 * direction and the camera plane. The resulting ray direction vector is stored
 * in the `data->raycast->ray_dir[0]` struct.
 *
 * @param data The main data structure containing the game state.
 * @param x The x-coordinate of the current ray being cast.
 */
void calculate_ray_direction(t_data *data, int x)
{
    data->raycast->camera_x = 2 * x /(double)WIDTH - 1;
    data->raycast->ray_dir[0]->x = data->player[0]->dx + data->raycast->camera_x * data->raycast->plane[0]->x;
    data->raycast->ray_dir[0]->y = data->player[0]->dy + data->raycast->camera_x * data->raycast->plane[0]->y;
}

/**
 * Calculates the map position for the current ray being cast.
 *
 * This function calculates the integer map coordinates (map_x, map_y) based on
 * the player's current position. These map coordinates are used to determine
 * which grid cell the ray is currently in during the raycasting process.
 *
 * @param data The main data structure containing the game state.
 */
void calculate_map_position(t_data *data)
{
    data->raycast->map_x = (int)data->player[0]->pos[0]->x;
    data->raycast->map_y = (int)data->player[0]->pos[0]->y;
}

void draw_end_to_start(t_data *data, int *line_height, int *draw_start, int *draw_end)
{
    *line_height = (int)(HEIGHT / data->raycast->perp_wall_dist);
    *draw_start -= (*line_height) / 2 + HEIGHT / 2;
    if (*draw_start < 0)
        *draw_start = 0;
    *draw_end = *line_height / 2 + HEIGHT / 2;
    if (*draw_end >= HEIGHT)
        *draw_end = HEIGHT - 1;
}

/*
    function is used to round down a floating-point number to the nearest integer value that is less than or equal to the original number.
*/
int round_down_fltpoint(double x)
{
    int result = (int)x;  // Convert the floating-point number to an integer (truncation towards zero)
    
    // If the number is positive or if the truncation did not change the number, return the result.
    if (x >= 0 || (double)result == x)
    {
        return result;
    }
    else
    {
        // If the number is negative and has a fractional part, subtract 1 to round down.
        return result - 1;
    }
}

void draw_texture(t_data *data, int draw_start, int line_height)
{
    double hit_x;

    if (data->raycast->side == 0)
        hit_x = data->player[0]->pos[0]->y + data->raycast->perp_wall_dist * data->raycast->ray_dir[0]->y;
    else
        hit_x = data->player[0]->pos[0]->x + data->raycast->perp_wall_dist * data->raycast->ray_dir[0]->x;
    hit_x -= round_down_fltpoint(hit_x);
    data->raycast->texture_x = hit_x * TEXTURE_SIZE;
    if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x > 0)
        data->raycast->texture_x = TEXTURE_SIZE - data->raycast->texture_x - 1;
    if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y < 0)
        data->raycast->texture_x = TEXTURE_SIZE - data->raycast->texture_x - 1;
    data->raycast->step_n = 1.0 * TEXTURE_SIZE / line_height;
    data->raycast->texture_pos = (draw_start - HEIGHT / 2 + line_height / 2) * data->raycast->step_n;
}

/* void draw_world(t_data *data)
{
    int x;
    int y;
    int color;

    for (x = 0; x < WIDTH; x++)
    {
        for (y = 0; y < HEIGHT; y++)
        {
            color = get_color(data, data->raycast->wall_type);
            my_mlx_pixel_put(data, x, y, color);
        }
    }
} */
void draw_world(t_data *data, int x)
{
 //   int x;
    
    int color;

    
            color = get_color(data, data->raycast->wall_type);
            my_mlx_pixel_put(data, x, 64, color);
    

}

void draw_loop(t_data *data, int x, int draw_start, int draw_end)
{
     while (draw_start < draw_end)
        {
            data->raycast->texture_y = (int)data->raycast->texture_pos & (TEXTURE_SIZE - 1);
            data->raycast->texture_pos += data->raycast->step_n;
            if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y < 0)
                draw_world(data, x);
            else if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y > 0)
                draw_world(data, x);
            else if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x < 0)
                draw_world(data, x);
            else if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x > 0)
                draw_world(data, x);
            draw_start++;
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
        calculate_ray_direction(data, x);
        calculate_map_position(data);
        rc_delta_dist(data);
        rc_side_step(data);
        rc_loop_hit(data);
        if (data->raycast->side == 0)
            data->raycast->perp_wall_dist = (data->raycast->side_dist[0]->x - data->raycast->delta_dist[0]->x);
        else
            data->raycast->perp_wall_dist = (data->raycast->side_dist[0]->y - data->raycast->delta_dist[0]->y);
        int line_height, draw_start, draw_end;
        line_height = 0;
        draw_start = 0;
        draw_end = 0;
        draw_end_to_start(data, &line_height, &draw_start, &draw_end);
        draw_texture(data, draw_start, line_height);
        draw_loop(data, x, draw_start, draw_end);
    }
}
