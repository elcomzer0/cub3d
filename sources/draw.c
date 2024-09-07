/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/07 02:05:02 by jorgonca         ###   ########.fr       */
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



void    ceiling_floor(t_data *data)
{
    int x;
    int y;
    int color1;
    int color2;
    int color_floor;
    int color_ceiling;
    
    color_ceiling = data->color->blue;
    color_floor = data->color->magenta;

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y <= HEIGHT)
        {
            if (y < HEIGHT / 2)
            {
            color1 = color_ceiling;
            my_xpm_pixel_put(data, x, y, color1);
                
            }
            else
            {
                color2 = color_floor;
                my_xpm_pixel_put(data, x, y, color2);
            }
            y++;
        }
        x++;
    }
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

int blend_colors_2(int color1, int color2, double blend_factor)
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
    blended_color = blend_colors_2(color, blend_color, blend_factor);

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
    blended_color = blend_colors_2(color, blend_color, blend_factor);

    return blended_color;
}
void ceiling_floor_sw(t_data *data)
{
    int y; // Declare y here
    int x; // Declare x here
    double ray_dir_x0; // x- and y-direction of the ray
    double ray_dir_y0; // x- and y-direction of the ray
    double ray_dir_x1; // x- and y-direction of the ray
    double ray_dir_y1; // x- and y-direction of the ray
    int p; // loop variable
    double pos_z; // z-coordinate in camera space
    double row_distance; // distance from player to the floor/ceiling
    double floor_step_x; // x-step for each row
    double floor_step_y; // y-step for each row
    double floor_x; // x-coordinate of the floor
    double floor_y; // y-coordinate of the floor
    int cell_x; // x-coordinate of the floor
    int cell_y; // y-coordinate of the floor
    int tx; // x-coordinate of the floor texture
    int ty; // y-coordinate of the floor
    int floor_texture; // texture index for the floor
    int ceiling_texture; // texture index for the ceiling
    int color; // color of the floor
    double shading_factor; // shading factor for the floor

    ray_dir_x0 = data->player[0]->dx - data->raycast->plane[0]->x;
    ray_dir_y0 = data->player[0]->dy - data->raycast->plane[0]->y;
    ray_dir_x1 = data->player[0]->dx + data->raycast->plane[0]->x;
    ray_dir_y1 = data->player[0]->dy + data->raycast->plane[0]->y;

    // Render floor
    for (y = HEIGHT / 2 + 1; y < HEIGHT; y++)
    {
        p = y - HEIGHT / 2;
        pos_z = 0.5 * HEIGHT;
        row_distance = pos_z / p;
        floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIDTH;
        floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIDTH;
        floor_x = data->player[0]->pos[0]->x + row_distance * ray_dir_x0;
        floor_y = data->player[0]->pos[0]->y + row_distance * ray_dir_y0;

        for (x = 0; x < WIDTH; x++)
        {
            cell_x = (int)floor_x;
            cell_y = (int)floor_y;
            tx = (int)(TEXTURE_SIZE * (floor_x - cell_x)) & (TEXTURE_SIZE - 1);
            ty = (int)(TEXTURE_SIZE * (floor_y - cell_y)) & (TEXTURE_SIZE - 1);
            floor_x += floor_step_x;
            floor_y += floor_step_y;

            floor_texture = 2; // Assuming floor texture index is 2
            color = retrieve_px_info(data, tx, ty, floor_texture);

            // Calculate shading factor based on distance and shadow
            shading_factor = 1.0 / (1.0 + row_distance * row_distance * 0.1);
            color = shading_color_floor(color, shading_factor);

            my_xpm_pixel_put(data, x, y, color);
        }
    }

    // Render ceiling
    for (y = 0; y < HEIGHT / 2; y++)
    {
        p = HEIGHT / 2 - y;
        pos_z = 0.5 * HEIGHT;
        row_distance = pos_z / p;
        floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIDTH;
        floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIDTH;
        floor_x = data->player[0]->pos[0]->x + row_distance * ray_dir_x0;
        floor_y = data->player[0]->pos[0]->y + row_distance * ray_dir_y0;

        for (x = 0; x < WIDTH; x++)
        {
            cell_x = (int)floor_x;
            cell_y = (int)floor_y;
            tx = (int)(TEXTURE_SIZE * (floor_x - cell_x)) & (TEXTURE_SIZE - 1);
            ty = (int)(TEXTURE_SIZE * (floor_y - cell_y)) & (TEXTURE_SIZE - 1);
            floor_x += floor_step_x;
            floor_y += floor_step_y;

            ceiling_texture = 3; // Assuming ceiling texture index is 1
            color = retrieve_px_info(data, tx, ty, ceiling_texture);

            // Calculate shading factor based on distance and shadow
            shading_factor = 1.0 / (1.0 + row_distance * row_distance * 0.1);
            color = shading_color_ceiling(color, shading_factor);

            my_xpm_pixel_put(data, x, y, color);
        }
    }
}
// void ceiling_floor_sw(t_data *data)
// {
//     int y;
//     int x;
//     double ray_dir_x0;
//     double ray_dir_y0;
//     double ray_dir_x1;
//     double ray_dir_y1;
//     int p;
//     double pos_z;
//     double row_distance;
//     double floor_step_x;
//     double floor_step_y;
//     double floor_x;
//     double floor_y;
//     int cell_x;
//     int cell_y;
//     int tx;
//     int ty;
//     int floor_texture;
//     int color;
//     double shading_factor;

//     ray_dir_x0 = data->player[0]->dx - data->raycast->plane[0]->x;
//     ray_dir_y0 = data->player[0]->dy - data->raycast->plane[0]->y;
//     ray_dir_x1 = data->player[0]->dx + data->raycast->plane[0]->x;
//     ray_dir_y1 = data->player[0]->dy + data->raycast->plane[0]->y;

//     for (y = HEIGHT / 2 + 1; y < HEIGHT; y++)
//     {
//         p = y - HEIGHT / 2;
//         pos_z = 0.5 * HEIGHT;
//         row_distance = pos_z / p;
//         floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIDTH;
//         floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIDTH;
//         floor_x = data->player[0]->pos[0]->x + row_distance * ray_dir_x0;
//         floor_y = data->player[0]->pos[0]->y + row_distance * ray_dir_y0;

//         for (x = 0; x < WIDTH; x++)
//         {
//             cell_x = (int)floor_x;
//             cell_y = (int)floor_y;
//             tx = (int)(TEXTURE_SIZE * (floor_x - cell_x)) & (TEXTURE_SIZE - 1);
//             ty = (int)(TEXTURE_SIZE * (floor_y - cell_y)) & (TEXTURE_SIZE - 1);
//             floor_x += floor_step_x;
//             floor_y += floor_step_y;

//             floor_texture = 2; // Assuming floor texture index is 3
//             color = retrieve_px_info(data, tx, ty, floor_texture);

//             // Calculate shading factor based on distance and shadow
//             shading_factor = 1.0 / (1.0 + row_distance * row_distance * 0.1);
//             color = shading_color_v2(color, shading_factor);

//             my_xpm_pixel_put(data, x, y, color);
//         }
//     }
// }


// void ceiling_floor_sw(t_data *data)
// {
//     int y;
//     int x;
//     double ray_dir_x0;
//     double ray_dir_y0;
//     double ray_dir_x1;
//     double ray_dir_y1;
//     int p;
//     double pos_z;
//     double row_distance;
//     double floor_step_x;
//     double floor_step_y;
//     double floor_x;
//     double floor_y;
//     int cell_x;
//     int cell_y;
//     int tx;
//     int ty;
//     int floor_texture;
//     int color;
//     int blend_color;
//     double shading_factor;
//     double blend_factor = 0.5; // Adjust this value to control the blend intensity
//     int dark_mist_color = 0x000000; // Dark color for the misty layer
//     int alpha = 64; // Semi-transparent alpha value
//     // Define the blend color (e.g., a light blue color)
//     //blend_color = 0xADD8E6;
//     // dark magenta
//     //blend_color = 0x800080;
//     int black = 0x000000;
//     int light_blue = 0x0000FF;
//     blend_color = (black << 16) | (0 << 8) | light_blue;

//                 // Apply mist layer effect
//     blend_color = blend_colors((alpha << 24) | dark_mist_color, blend_color);
    
    

//     ray_dir_x0 = data->player[0]->dx - data->raycast->plane[0]->x;
//     ray_dir_y0 = data->player[0]->dy - data->raycast->plane[0]->y;
//     ray_dir_x1 = data->player[0]->dx + data->raycast->plane[0]->x;
//     ray_dir_y1 = data->player[0]->dy + data->raycast->plane[0]->y;

//     for (y = HEIGHT / 2 + 1; y < HEIGHT; y++)
//     {
//         p = y - HEIGHT / 2;
//         pos_z = 0.5 * HEIGHT;
//         row_distance = pos_z / p;
//         floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIDTH;
//         floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIDTH;
//         floor_x = data->player[0]->pos[0]->x + row_distance * ray_dir_x0;
//         floor_y = data->player[0]->pos[0]->y + row_distance * ray_dir_y0;

//         for (x = 0; x < WIDTH; x++)
//         {
//             cell_x = (int)floor_x;
//             cell_y = (int)floor_y;
//             tx = (int)(TEXTURE_SIZE * (floor_x - cell_x)) & (TEXTURE_SIZE - 1);
//             ty = (int)(TEXTURE_SIZE * (floor_y - cell_y)) & (TEXTURE_SIZE - 1);
//             floor_x += floor_step_x;
//             floor_y += floor_step_y;

//             floor_texture = 3; // Assuming floor texture index is 3
//             color = retrieve_px_info(data, tx, ty, floor_texture);

//             // Calculate shading factor based on distance and shadow
//             shading_factor = 1.0 / (1.0 + row_distance * row_distance * 0.1);
//             color = shading_color(color, shading_factor);

//             // Blend the floor texture color with the blend color
//             color = blend_colors_2(color, blend_color, blend_factor);

//             my_xpm_pixel_put(data, x, y, color);
//         }
//     }
// }

void ceiling_floor_v5(t_data *data)
{
    int x;
    int y;
    int color1;
    int color2;
    int dark_mist_color = 0x000000; // Dark color for the misty layer
    int alpha = 64; // Semi-transparent alpha value

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y <= HEIGHT)
        {
            if (y < HEIGHT / 2)
            {
                // Black to dark blue gradient for the ceiling
                int blue = (y * 64 / (HEIGHT / 2)); // Dark blue component
                color1 = (blue);

                // Apply mist layer effect
                color1 = blend_colors((alpha << 24) | dark_mist_color, color1);

                my_xpm_pixel_put(data, x, y, color1);
            }
            else
            {
                // Lighter magenta to darker magenta gradient for the floor
                int light_magenta = 255 - ((y - HEIGHT / 2) * 127 / (HEIGHT / 2)); // Lighter magenta
                int dark_magenta = 128 + ((y - HEIGHT / 2) * 127 / (HEIGHT / 2)); // Darker magenta
                color2 = (dark_magenta << 16) | (0 << 8) | light_magenta;

                // Apply mist layer effect
                color2 = blend_colors((alpha << 24) | dark_mist_color, color2);

                my_xpm_pixel_put(data, x, y, color2);
            }
            y++;
        }
        x++;
    }
}

void render_stars(t_data *data, int num_stars)
{
    for (int i = 0; i < num_stars; i++)
    {
        // Ensure that the index is within bounds
        if (i >= 0 && i < num_stars)
        {
            int star_color = 0xFFFFFF; // White color for stars
            my_xpm_pixel_put(data, data->star_x[i], data->star_y[i], star_color);
        }
    }
}




int    cub_draw(t_data *data)
{ 
    //ceiling_floor(data);
    ceiling_floor_sw(data);
   
    //mist_layer(data, 100, 0x000000);
    //draw_gradient(data);
    //render_stars(data, 99);
    raycasting(data);
    mlx_put_image_to_window(data->mlx, data->win, data->raycast->texture[4].tex_img, 0, 0);
    return (0);
}