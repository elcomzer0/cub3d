/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:05 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/06 23:47:19 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

/**
 * Draws a single column of the game world with shading applied.
 *
 * This function is responsible for rendering a single vertical column of the
 * game world, including applying shading based on the distance and orientation
 * of the wall.
 *
 * @param data The main data structure containing the game state.
 * @param x The x-coordinate of the current column being drawn.
 * @param draw_start The starting y-coordinate for drawing the column.
 * @param compass The compass direction of the current wall.
 */
void draw_world(t_data *data, int x, int draw_start, int compass)
{
    int color;
    int wall_type;
    int shaded_color;
    double shading_factor;
    
    color = 0;
    shading_factor = 0;
    wall_type = xpm_switcher(data, compass);
    color = retrieve_px_info(data, data->raycast->texture_x, data->raycast->texture_y, wall_type);
    shading_factor = apply_shading(data, shading_factor);
    shaded_color = shading_color(color, shading_factor);
    my_xpm_pixel_put(data, x, draw_start, shaded_color);
}


/**
 * Calculates the starting and ending draw positions for a wall segment based on the perpendicular wall distance.
 *
 * This function takes the current game state data, the current line height, and the current draw start and end positions.
 * It calculates the new draw start and end positions based on the perpendicular wall distance, ensuring that the wall segment
 * is drawn within the visible screen area.
 *
 * @param data The main data structure containing the game state.
 * @param line_height A pointer to the current line height value.
 * @param draw_start A pointer to the current draw start position.
 * @param draw_end A pointer to the current draw end position.
 */
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

/**
 * Draws a texture on the screen based on the current ray casting information.
 *
 * This function calculates the x-coordinate of the texture to be drawn based on the perpendicular wall distance and the ray direction. It also calculates the step size for the texture coordinates and the starting texture position.
 *
 * @param data The main data structure containing the game state.
 * @param draw_start The starting y-coordinate for drawing the texture.
 * @param line_height The height of the wall segment to be drawn.
 */
void draw_texture(t_data *data, int draw_start, int line_height)
{
    double hit_x;

    if (data->raycast->side == 0)
        hit_x = data->player[0]->pos[0]->y + data->raycast->perp_wall_dist * data->raycast->ray_dir[0]->y;
    else
        hit_x = data->player[0]->pos[0]->x + data->raycast->perp_wall_dist * data->raycast->ray_dir[0]->x;
    hit_x -= ft_floor(hit_x);
    data->raycast->texture_x = hit_x * TEXTURE_SIZE;
    if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x > 0)
        data->raycast->texture_x = TEXTURE_SIZE - data->raycast->texture_x - 1;
    if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y < 0)
        data->raycast->texture_x = TEXTURE_SIZE - data->raycast->texture_x - 1;
    data->raycast->step_n = 1.0 * TEXTURE_SIZE / line_height;
    data->raycast->texture_pos = (draw_start - HEIGHT / 2 + line_height / 2) * data->raycast->step_n;
}

/**
 * Draws the wall textures on the screen for the current ray casting iteration.
 *
 * This function iterates through the vertical pixels of the current wall segment and draws the corresponding texture pixels. The texture coordinates are calculated based on the perpendicular wall distance and the ray direction.
 *
 * @param data The main data structure containing the game state.
 * @param x The current horizontal pixel coordinate being rendered.
 * @param draw_start The starting vertical pixel coordinate for the current wall segment.
 * @param draw_end The ending vertical pixel coordinate for the current wall segment.
 */
void draw_loop(t_data *data, int x, int draw_start, int draw_end)
{
     while (draw_start <= draw_end)
    {
        data->raycast->texture_y = (int)data->raycast->texture_pos & (TEXTURE_SIZE - 1);
        data->raycast->texture_pos = data->raycast->texture_pos + data->raycast->step_n;
        if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y < 0)              
            draw_world(data, x, draw_start, 1);
        else if (data->raycast->side == 1 && data->raycast->ray_dir[0]->y > 0)
            draw_world(data, x, draw_start, 2);
        else if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x < 0)
            draw_world(data, x, draw_start, 3);
        else if (data->raycast->side == 0 && data->raycast->ray_dir[0]->x > 0)
            draw_world(data, x, draw_start, 4);
        draw_start++;
    }
}
