/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/07 17:26:40 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int blend_colors(int src_color, int dest_color)
{
    int src_a = (src_color >> 24) & 0xFF;
    int src_r = (src_color >> 16) & 0xFF;
    int src_g = (src_color >> 8) & 0xFF;
    int src_b = src_color & 0xFF;

    int dest_r = (dest_color >> 16) & 0xFF;
    int dest_g = (dest_color >> 8) & 0xFF;
    int dest_b = dest_color & 0xFF;

    int out_r = (src_r * src_a + dest_r * (255 - src_a)) / 255;
    int out_g = (src_g * src_a + dest_g * (255 - src_a)) / 255;
    int out_b = (src_b * src_a + dest_b * (255 - src_a)) / 255;

    return (out_r << 16) | (out_g << 8) | out_b;
}

void my_xpm_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;  
    //unsigned int *dst_color;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    dst = data->raycast->texture[4].tex_addr + (y * data->raycast->texture[4].line_length + x * (data->raycast->texture[4].bpp / 8));
 
    *(unsigned int *)dst = color;
}
    

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;  // Silently return if out of bounds
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}





void    draw_gradient(t_data *data)
{
    int y = 0;
    while (y < HEIGHT)
    {
        int x = 0;
        while (x < WIDTH)
        {
            int color = (x * 255 / WIDTH) << 16 | (y * 255 / HEIGHT) << 8;
            my_xpm_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    
}

int blend_colors_clfl(int color1, int color2, double blend_factor)
{
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int r = (int)((1 - blend_factor) * r1 + blend_factor * r2);
    int g = (int)((1 - blend_factor) * g1 + blend_factor * g2);
    int b = (int)((1 - blend_factor) * b1 + blend_factor * b2);

    return (r << 16) | (g << 8) | b;
}
int shading_color_ceiling(int color, double shading_factor)
{
    int r, g, b;
    int blended_color;
    double blend_factor = 0.5; // Adjust this value to control the blend intensity
    int blend_color = 0x000000;// Example blend color (light turquoise)

    // Extract RGB components from the original color
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;

    // Apply shading factor
    r = (int)(r * shading_factor);
    g = (int)(g * shading_factor);
    b = (int)(b * shading_factor);

    // Combine the shaded color components back into a single integer
    color = (r << 16) | (g << 8) | b;

    // Blend the shaded color with the blend color
    blended_color = blend_colors_clfl(color, blend_color, blend_factor);

    return blended_color;
}

int shading_color_floor(int color, double shading_factor)
{
    int r, g, b;
    int blended_color;
    double blend_factor = 0.5; // Adjust this value to control the blend intensity
    int blend_color = 0x000000; // Example blend color (light blue)

    // Extract RGB components from the original color
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;

    // Apply shading factor
    r = (int)(r * shading_factor);
    g = (int)(g * shading_factor);
    b = (int)(b * shading_factor);

    // Combine the shaded color components back into a single integer
    color = (r << 16) | (g << 8) | b;

    // Blend the shaded color with the blend color
    blended_color = blend_colors_clfl(color, blend_color, blend_factor);

    return blended_color;
}

/**
 * Calculates the texture coordinates for the floor based on the current position and step values.
 *
 * This function is responsible for updating the `cell`, `tex`, and `floor` fields of the `data->fl_cl` struct.
 * The `cell` field is set to the integer part of the current floor position, which represents the current tile or cell.
 * The `tex` field is calculated based on the fractional part of the floor position, which represents the position within the current tile.
 * The `floor` field is then updated by adding the `floor_step` values to move to the next position.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 * @param p The current row index.
 * @param y The current column index.
 */
void render_cl_step(t_data *data, int p, int y)
{
    p = HEIGHT / 2 - y;
    data->fl_cl->pos_z = 0.5 * HEIGHT;
    data->fl_cl->row_distance = data->fl_cl->pos_z / p;
    data->fl_cl->floor_step[0] = data->fl_cl->row_distance * (data->fl_cl->ray_dx[1] - data->fl_cl->ray_dx[0]) / WIDTH;
    data->fl_cl->floor_step[1] = data->fl_cl->row_distance * (data->fl_cl->ray_dy[1] - data->fl_cl->ray_dy[0]) / WIDTH;
    data->fl_cl->floor[0] = data->player->pos[0] + data->fl_cl->row_distance * data->fl_cl->ray_dx[0];
    data->fl_cl->floor[1] = data->player->pos[1] + data->fl_cl->row_distance * data->fl_cl->ray_dy[0];
}

/**
 * Renders the floor texture and applies shading to the floor.
 *
 * This function is responsible for:
 * - Setting the floor texture index to 3 (assuming the floor texture is at index 3).
 * - Retrieving the pixel information for the current floor texture coordinates using `retrieve_px_info()`.
 * - Calculating a shading factor based on the row distance.
 * - Applying the shading factor to the floor color using `shading_color_floor()`.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 */
void render_cl_shader(t_data *data)
{
    data->fl_cl->floor_tex = 3;
    data->fl_cl->color = retrieve_px_info(data, data->fl_cl->tex[0], data->fl_cl->tex[1], data->fl_cl->floor_tex);
    data->fl_cl->shading_factor = 1.0 / (1.0 + data->fl_cl->row_distance * data->fl_cl->row_distance * 0.1);
    data->fl_cl->color = shading_color_floor(data->fl_cl->color, data->fl_cl->shading_factor);
}

/**
 * Calculates the texture coordinates for the floor based on the current position and step values.
 *
 * This function is responsible for updating the `cell`, `tex`, and `floor` fields of the `data->fl_cl` struct.
 * The `cell` field is set to the integer part of the current floor position, which represents the current tile or cell.
 * The `tex` field is calculated based on the fractional part of the floor position, which represents the position within the current tile.
 * The `floor` field is then updated by adding the `floor_step` values to move to the next position.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 */
void render_fl_step(t_data *data, int p, int y)
{
    p = y - HEIGHT / 2;
    data->fl_cl->pos_z = 0.5 * HEIGHT;
    data->fl_cl->row_distance = data->fl_cl->pos_z / p;
    data->fl_cl->floor_step[0] = data->fl_cl->row_distance * (data->fl_cl->ray_dx[1] - data->fl_cl->ray_dx[0]) / WIDTH;
    data->fl_cl->floor_step[1] = data->fl_cl->row_distance * (data->fl_cl->ray_dy[1] - data->fl_cl->ray_dy[0]) / WIDTH;
    data->fl_cl->floor[0] = data->player->pos[0] + data->fl_cl->row_distance * data->fl_cl->ray_dx[0];
    data->fl_cl->floor[1] = data->player->pos[1] + data->fl_cl->row_distance * data->fl_cl->ray_dy[0];
}
// void render_fl_step(t_data *data, int p, int y)
// {
//     p = y - HEIGHT / 2;
//     data->fl_cl->pos_z = 0.5 * HEIGHT;
//     data->fl_cl->row_distance = data->fl_cl->pos_z / p;
//     data->fl_cl->floor_step[0] = data->fl_cl->row_distance * (data->fl_cl->ray_dx[1] - data->fl_cl->ray_dx[0]) / WIDTH;
//     data->fl_cl->floor_step[1] = data->fl_cl->row_distance * (data->fl_cl->ray_dy[1] - data->fl_cl->ray_dy[0]) / WIDTH;
//     data->fl_cl->floor[0] = data->player[0]->pos[0]->x + data->fl_cl->row_distance * data->fl_cl->ray_dx[0];
//     data->fl_cl->floor[1] = data->player[0]->pos[0]->y + data->fl_cl->row_distance * data->fl_cl->ray_dy[0];
// }

/**
 * Renders the floor texture and applies shading to the floor.
 *
 * This function is responsible for:
 * - Setting the floor texture index to 2 (assuming the floor texture is at index 2).
 * - Retrieving the pixel information for the current floor texture coordinates using `retrieve_px_info()`.
 * - Calculating a shading factor based on the row distance.
 * - Applying the shading factor to the floor color using `shading_color_floor()`.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 */
void render_fl_shader(t_data *data)
{
    data->fl_cl->floor_tex = 2; // Assuming floor texture index is 2
    data->fl_cl->color = retrieve_px_info(data, data->fl_cl->tex[0], data->fl_cl->tex[1], data->fl_cl->floor_tex);
    data->fl_cl->shading_factor = 1.0 / (1.0 + data->fl_cl->row_distance * data->fl_cl->row_distance * 0.1);
    data->fl_cl->color = shading_color_floor(data->fl_cl->color, data->fl_cl->shading_factor);
}

/**
 * Calculates the texture coordinates for the floor based on the current position and step values.
 *
 * This function is responsible for updating the `cell`, `tex`, and `floor` fields of the `data->fl_cl` struct.
 * The `cell` field is set to the integer part of the current floor position, which represents the current tile or cell.
 * The `tex` field is calculated based on the fractional part of the floor position, which represents the position within the current tile.
 * The `floor` field is then updated by adding the `floor_step` values to move to the next position.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 */
void render_pos_tex(t_data *data)
{
    data->fl_cl->cell[0] = (int)data->fl_cl->floor[0];
    data->fl_cl->cell[1] = (int)data->fl_cl->floor[1];
    data->fl_cl->tex[0] = (int)(TEXTURE_SIZE * (data->fl_cl->floor[0] - data->fl_cl->cell[0])) & (TEXTURE_SIZE - 1);
    data->fl_cl->tex[1] = (int)(TEXTURE_SIZE * (data->fl_cl->floor[1] - data->fl_cl->cell[1])) & (TEXTURE_SIZE - 1);
    data->fl_cl->floor[0] += data->fl_cl->floor_step[0];
    data->fl_cl->floor[1] += data->fl_cl->floor_step[1];
    
}

/**
 * Renders the floor texture and applies shading to the floor.
 *
 * This function iterates over the bottom half of the screen, rendering the floor texture
 * and applying shading to the floor. It calculates the texture coordinates for the floor
 * based on the current position and step values, retrieves the pixel information for the
 * current floor texture coordinates, calculates a shading factor based on the row distance,
 * and applies the shading factor to the floor color.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 */
void render_floor(t_data *data)
{
    int y;
    int x;
    int p;
    
    y = HEIGHT / 2 + 1;
    p = 0;
    while (y < HEIGHT)
    {
        render_fl_step(data, p, y);
        x = 0;
        while (x < WIDTH)
        {
            render_pos_tex(data);
            render_fl_shader(data);
            my_xpm_pixel_put(data, x, y, data->fl_cl->color);
            x++;
        }
        y++;
    }
}

/**
 * Renders the ceiling texture and applies shading to the ceiling.
 *
 * This function iterates over the top half of the screen, rendering the ceiling texture
 * and applying shading to the ceiling. It calculates the texture coordinates for the ceiling
 * based on the current position and step values, retrieves the pixel information for the
 * current ceiling texture coordinates, calculates a shading factor based on the row distance,
 * and applies the shading factor to the ceiling color.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 */
void render_ceiling(t_data *data)
{
    int y;
    int x;
    int p;
    
    x = 0;
    y = 0;
    p = 0;
    while (y < HEIGHT / 2)
    {
        render_cl_step(data, p, y);
        x = 0;
        while (x < WIDTH)
        {
            render_pos_tex(data);
            render_cl_shader(data);
            my_xpm_pixel_put(data, x, y, data->fl_cl->color);
            x++;
        }
        y++;
    }
}

void ceiling_floor(t_data *data)
{
    data->fl_cl->ray_dx[0] = data->player->dx - data->raycast->plane[0];
    data->fl_cl->ray_dy[0] = data->player->dy - data->raycast->plane[1];
    data->fl_cl->ray_dx[1] = data->player->dx + data->raycast->plane[0];
    data->fl_cl->ray_dy[1] = data->player->dy + data->raycast->plane[1];
    render_floor(data);
    render_ceiling(data);
}
// void ceiling_floor(t_data *data)
// {
//     data->fl_cl->ray_dx[0] = data->player[0]->dx - data->raycast->plane[0]->x;
//     data->fl_cl->ray_dy[0] = data->player[0]->dy - data->raycast->plane[0]->y;
//     data->fl_cl->ray_dx[1] = data->player[0]->dx + data->raycast->plane[0]->x;
//     data->fl_cl->ray_dy[1] = data->player[0]->dy + data->raycast->plane[0]->y;
//     render_floor(data);
//     render_ceiling(data);
// }

int    cub_draw(t_data *data)
{ 
    ceiling_floor(data);
    raycasting(data);
    mlx_put_image_to_window(data->mlx, data->win, data->raycast->texture[4].tex_img, 0, 0);
    return (0);
}