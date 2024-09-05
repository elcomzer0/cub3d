/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:05 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/05 02:29:13 by jorgonca         ###   ########.fr       */
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
    if(data->raycast->ray_dir[0]->x == 0)
        data->raycast->delta_dist[0]->x = DBL_MAX;
    else
        data->raycast->delta_dist[0]->x = fabs(1 / data->raycast->ray_dir[0]->x);
    if(data->raycast->ray_dir[0]->y == 0)
        data->raycast->delta_dist[0]->y = DBL_MAX;
    else
        data->raycast->delta_dist[0]->y = fabs(1 / data->raycast->ray_dir[0]->y);
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
        int map_value = data->z_values[data->raycast->map_y][data->raycast->map_x];
        if (map_value >= 1 && map_value <= 5)
        {
            data->raycast->hit = 1;
            data->raycast->wall_type = map_value;
            break;  // Store the wall type
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
/* int  get_color(t_data *data, int wall_type)
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
} */

/* int test_color(t_data *data, int x, int y, int texture_index)
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
    //return (*(int *)data->raycast->texture[i].tex_addr + (y * data->raycast->texture[i].line_length + x * (data->raycast->texture[i].bpp / 8)));
} */

int texture_info(t_data *data, int x, int y, int texture_index)
{
    return (*(int *)data->raycast->texture[texture_index].tex_addr + (y * data->raycast->texture[texture_index].line_length + x * (data->raycast->texture[texture_index].bpp / 8)));
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
    // else 
    // {
    //     //strcpy(&data->raycast->texture->path[0], ".textures/WOOD_1C.xpm");
    //     return 4;
    // }
    // else 
    //     return -1; // Default color if wall type is not recognized
    /* else if (wall_type == 4)
    {
        //strcpy(&data->raycast->texture->path[0], ".textures/WOOD_1C.xpm");
        return 4;
    }
    else if (wall_type == 5)
        return data->color->yellow; */
}

// void draw_world(t_data *data, int x, int draw_start, int draw_end)
// {
//     (void)draw_end;
//     int color = 0;
//     int wall_type = data->raycast->wall_type;
//     int texture_index = xpm_switcher(data, wall_type);
//     //color = get_color(data, wall_type);
//     //color = test_color(data, data->raycast->texture_x, data->raycast->texture_y, texture_index);
//     // if (data->raycast->side == 1)
//     //     color = color / 2;
//     //my_mlx_pixel_put(data, x, draw_start, color);
//     my_xpm_pixel_put(data, x, draw_start, color);

// }

void draw_world_v2(t_data *data, int x, int draw_start, int compass)
{
    int color = 0;
    int wall_type = xpm_switcher(data, compass);
   // printf("draw_start: %d\n", draw_start);
    //printf("wall_type: %d\n", wall_type);
    color = texture_info(data, data->raycast->texture_x, data->raycast->texture_y, wall_type);
    //color = test_color(data, data->raycast->texture_x, data->raycast->texture_y, wall_type);
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
    *line_height = (int)(HEIGHT / data->raycast->perp_wall_dist);
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

   // data->raycast->texture_num = data->raycast->wall_type - 1; // check if that is intended to be like this
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
            data->raycast->texture_pos += data->raycast->step_n;
            //data->color->color32 = data->map_addr[(data->raycast->texture_y * TEXTURE_SIZE) + data->raycast->texture_x];
            if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y < 0)              
                draw_world_v2(data, x, draw_start, 1);
            else if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y > 0)
                draw_world_v2(data, x, draw_start, 2);
            else if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x < 0)
                draw_world_v2(data, x, draw_start, 3);
            else if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x > 0)
                draw_world_v2(data, x, draw_start, 4);
            draw_start++;
           // printf("draw_start: %d, draw_end: %d\n", draw_start, draw_end);
            //printf("x: %d, draw_start: %d, draw_end: %d\n", x, draw_start, draw_end);
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
