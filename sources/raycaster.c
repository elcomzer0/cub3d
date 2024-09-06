/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:14 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/06 23:18:53 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"


/**
 * Updates the ray's position and direction based on the calculated side distance and delta distance values.
 * The function determines which grid line the ray has hit (x or y) and updates the corresponding map coordinates and side value.
 *
 * @param data A pointer to the main data struct containing the ray casting information.
 */
void side_hit_x(t_data *data)
{
    data->raycast->side_dist[0]->x += data->raycast->delta_dist[0]->x;
    data->raycast->map_x += data->raycast->step[0]->x;
    data->raycast->side = 0;
}

/**
 * Updates the ray's position and direction based on the calculated side distance and delta distance values.
 * The function determines which grid line the ray has hit (x or y) and updates the corresponding map coordinates and side value.
 *
 * @param data A pointer to the main data struct containing the ray casting information.
 */
void side_hit_y(t_data *data)
{
    data->raycast->side_dist[0]->y += data->raycast->delta_dist[0]->y;
    data->raycast->map_y += data->raycast->step[0]->y;
    data->raycast->side = 1;
}

/**
 * Performs the ray casting loop to determine when the ray hits a wall.
 * The function updates the ray's position and direction based on the calculated
 * side distance and delta distance values, and stops the loop when a wall is hit.
 * The wall type is also stored for later use.
 *
 * @param data A pointer to the main data struct containing the ray casting information.
 */
void rc_loop_hit(t_data *data)
{
    int map_value;
    
    map_value = 0;
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
            side_hit_x(data);
        else
            side_hit_y(data);
        map_value = data->z_values[data->raycast->map_y][data->raycast->map_x]; //for later 1 and 32
        if (map_value >= 1 && map_value <= 5)
        {
            data->raycast->hit = 1;
            data->raycast->wall_type = map_value;
            break;  // Store the wall type
        }
    }
}

void raycasting_loop(t_data *data, int line_height, int draw_start, int draw_end)
{
    int x;

    x = 0;
    while (x < WIDTH)
    {
        calculate_ray_direction(data, x);
        calculate_map_position(data);
        rc_delta_dist(data);
        rc_side_step(data);
        rc_loop_hit(data);
        perp_wall_dist(data);
        draw_end_to_start(data, &line_height, &draw_start, &draw_end);
        draw_texture(data, draw_start, line_height);
        draw_loop(data, x, draw_start, draw_end);
        x++;
    }
}

/**
 * Performs ray casting to render the walls of the game world.
 *
 * This function iterates through each horizontal pixel of the screen and calculates the ray direction, map position, and distance to the wall for that ray. It then determines the height and vertical position of the wall segment to be drawn and calls the appropriate drawing functions to render the wall texture.
 *
 * @param data The main data structure containing the game state.
 */
void raycasting(t_data *data)
{
    int line_height;
    int draw_start;
    int draw_end;
    
    line_height = 0;
    draw_start = 0;
    draw_end = 0;
    if (data == NULL || data->raycast == NULL
        || data->player == NULL
        || data->raycast->ray_dir[0] == NULL || data->player[0]->pos[0] == NULL
        || data->color == NULL)
        {
            write(2, "Error: One or more pointers for raycast are NULL\n", 38);
            return ;
        }
    raycasting_loop(data, line_height, draw_start, draw_end);
}