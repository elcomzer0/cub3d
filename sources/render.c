/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:05 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/06 03:37:21 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"



void rc_delta_dist(t_data *data)
{
    if(data->raycast->ray_dir[0]->x == 0)
        data->raycast->delta_dist[0]->x = DBL_MAX;
    else
        data->raycast->delta_dist[0]->x = fabs(1 / data->raycast->ray_dir[0]->x);
    if(data->raycast->ray_dir[0]->y == 0)
        data->raycast->delta_dist[0]->y = DBL_MAX;
    else
        data->raycast->delta_dist[0]->y = fabs(1 / data->raycast->ray_dir[0]->y);
}


void rc_side_step(t_data *data)
{
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

    data->raycast->hit = 0;
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
        int map_value = data->z_values[data->raycast->map_y][data->raycast->map_x]; //for later 1 and 32
        if (map_value >= 1 && map_value <= 5)
        {
            data->raycast->hit = 1;
            data->raycast->wall_type = map_value;
            break;  // Store the wall type
        }
    }
}


int test_color(t_data *data, int x, int y, int texture_index)
{
     if (x < 0 || x >= data->raycast->texture[texture_index].width || 
        y < 0 || y >= data->raycast->texture[texture_index].height) {
        return 0; // Or a default color for out-of-bounds pixels
    }

    int pixel_index = (y * data->raycast->texture[texture_index].line_length) + 
                      (x * (data->raycast->texture[texture_index].bpp / 8));

    char *pixel_data = data->raycast->texture[texture_index].tex_addr + pixel_index;

    // Assuming XRGB format (little-endian)
    int color = (pixel_data[3] << 24) | 
                (pixel_data[2] << 16) | 
                (pixel_data[1] << 8) | 
                pixel_data[0];

    return color;
}


int  xpm_switcher(t_data *data, int wall_type)
{
    (void)data;
    if (wall_type == 1)
    {
        //strcpy(&data->raycast->texture->path[0], ".textures/WARN_1A.xpm");
        return 0;
    }
    else if (wall_type == 2)
    {
     //   strcpy(&data->raycast->texture->path[0], ".textures/WOOD_1C.xpm");
        return 1;
    }
    else if (wall_type == 3)
    {
       // strcpy(&data->raycast->texture->path[0], ".textures/WARN_1A.xpm");
        return 2;
    }
    else// (wall_type == 4)
    {
        //strcpy(&data->raycast->texture->path[0], ".textures/WOOD_1C.xpm");
        return 3;
    }
}



/* void draw_world_v3(t_data *data, int x, int draw_start, int compass)
{
    int color = 0;
    int wall_type = xpm_switcher(data, compass);
    color = test_color(data, data->raycast->texture_x, data->raycast->texture_y, wall_type);
    // Calculate the distance from the player to the wall
    double distance = data->raycast->perp_wall_dist;

    // Apply shading based on distance
    double shading_factor = 1.0 / (1.0 + distance * distance * 0.0051); // Adjust the factor as needed
    int r = ((color >> 16) & 0xFF) * shading_factor;
    int g = ((color >> 8) & 0xFF) * shading_factor;
    int b = (color & 0xFF) * shading_factor;
    int shaded_color = (r << 16) | (g << 8) | b;

    my_xpm_pixel_put(data, x, draw_start, shaded_color);
} */

void draw_world_v3(t_data *data, int x, int draw_start, int compass)
{
    int color = 0;
    int wall_type = xpm_switcher(data, compass);
    color = test_color(data, data->raycast->texture_x, data->raycast->texture_y, wall_type);

    // Calculate the distance from the player to the wall
    double distance = data->raycast->perp_wall_dist;

    // Determine the side of the wall and apply different shading factors
    double shading_factor;
    if (data->raycast->side == 0) // Vertical wall
    {
        if (data->raycast->ray_dir[0]->x > 0) // East-facing wall
        {
            shading_factor = 1.0 / (1.0 + distance * distance * 0.0051); // Lighter shading
        }
        else // West-facing wall
        {
            shading_factor = 1.0 / (1.0 + distance * distance * 0.04); // Darker shading
        }
    }
    else // Horizontal wall
    {
        if (data->raycast->ray_dir[0]->y > 0) // South-facing wall
        {
            shading_factor = 1.0 / (1.0 + distance * distance * 0.0051); // Lighter shading
        }
        else // North-facing wall
        {
            shading_factor = 1.0 / (1.0 + distance * distance * 0.04); // Darker shading
        }
    }

    // Apply shading to the color
    int r = ((color >> 16) & 0xFF) * shading_factor;
    int g = ((color >> 8) & 0xFF) * shading_factor;
    int b = (color & 0xFF) * shading_factor;
    int shaded_color = (r << 16) | (g << 8) | b;

    my_xpm_pixel_put(data, x, draw_start, shaded_color);
}

void draw_world_v2(t_data *data, int x, int draw_start, int compass)
{
    int color = 0;

    int wall_type = xpm_switcher(data, compass);

    color = test_color(data, data->raycast->texture_x, data->raycast->texture_y, wall_type);

    my_xpm_pixel_put(data, x, draw_start, color);
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
void  calculate_map_position(t_data *data)
{
    data->raycast->map_x = (int)data->player[0]->pos[0]->x;
    data->raycast->map_y = (int)data->player[0]->pos[0]->y;
}

void draw_end_to_start(t_data *data, int *line_height, int *draw_start, int *draw_end)
{
    *line_height = (HEIGHT / data->raycast->perp_wall_dist);
    *draw_start = -(*line_height) / 2 + HEIGHT / 2;
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




void draw_loop(t_data *data, int x, int draw_start, int draw_end)
{
     while (draw_start < draw_end)
        {
            data->raycast->texture_y = (int)data->raycast->texture_pos & (TEXTURE_SIZE - 1);
            data->raycast->texture_pos = data->raycast->texture_pos + data->raycast->step_n;
            if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y < 0)              
                draw_world_v3(data, x, draw_start, 1);
            else if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y > 0)
                draw_world_v3(data, x, draw_start, 2);
            else if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x < 0)
                draw_world_v3(data, x, draw_start, 3);
            else if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x > 0)
                draw_world_v3(data, x, draw_start, 4);
            draw_start++;
        }
}

void perp_wall_dist(t_data *data)
{
    if (data->raycast->side == 0)
        data->raycast->perp_wall_dist = (data->raycast->map_x - data->player[0]->pos[0]->x + (1 - data->raycast->step[0]->x) / 2) / data->raycast->ray_dir[0]->x;
    else
        data->raycast->perp_wall_dist = (data->raycast->map_y - data->player[0]->pos[0]->y + (1 - data->raycast->step[0]->y) / 2) / data->raycast->ray_dir[0]->y;
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
    x = 0;
    while (x < WIDTH)
    {   
        calculate_ray_direction(data, x);
        calculate_map_position(data);
        rc_delta_dist(data);
        rc_side_step(data);
        rc_loop_hit(data);
        perp_wall_dist(data);
        int line_height, draw_start, draw_end;
        line_height = 0;
        draw_start = 0;
        draw_end = 0;
        draw_end_to_start(data, &line_height, &draw_start, &draw_end);
        draw_texture(data, draw_start, line_height);
        draw_loop(data, x, draw_start, draw_end);
        x++;
    }
}
