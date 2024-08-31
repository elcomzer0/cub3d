/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/31 13:12:37 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"



int blend_colors(int src_color, int dest_color)
{
    int src_a = (src_color >> 24) & 0xFF;
    //printf("src_a: %d\n", src_a);
    int src_r = (src_color >> 16) & 0xFF;
    int src_g = (src_color >> 8) & 0xFF;
    int src_b = src_color & 0xFF;

    int dest_a = (dest_color >> 24) & 0xFF;
    int dest_r = (dest_color >> 16) & 0xFF;
    int dest_g = (dest_color >> 8) & 0xFF;
    int dest_b = dest_color & 0xFF;

    int out_a = src_a + dest_a * (255 - src_a) / 255;
   // printf("src_a: %d, dest_a: %d, out_a: %d\n", src_a, dest_a, out_a);
    if (out_a == 0)
    {
        return (0 << 24 | 0 << 16 | 0 << 8 | 0); // Fully transparent
    }
    write(1, "HELLO\n", 6);

    int out_r = (src_r * src_a + dest_r * dest_a * (255 - src_a) / 255) / out_a;
    int out_g = (src_g * src_a + dest_g * dest_a * (255 - src_a) / 255) / out_a;
    int out_b = (src_b * src_a + dest_b * dest_a * (255 - src_a) / 255) / out_a;

    return (out_a << 24 | out_r << 16 | out_g << 8 | out_b);
}

#include <stdint.h>

/**
 * Draws a pixel on the image data with the specified color, blending it with the existing pixel color.
 *
 * @param data The image data structure.
 * @param x The x-coordinate of the pixel to draw.
 * @param y The y-coordinate of the pixel to draw.
 * @param color The color to draw the pixel in.
 */
/* void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    // Use WIDTH and HEIGHT constants for bounds checking
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;  // Silently return if out of bounds

    char *dst;
    unsigned int *dst_color;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    
    if (((uintptr_t)dst % sizeof(unsigned int)) == 0) {
        dst_color = (unsigned int*)dst;
        *dst_color = blend_colors(color, *dst_color);
    } else {
        // Handle unaligned access
        unsigned int existing_color;
        memcpy(&existing_color, dst, sizeof(unsigned int));
        unsigned int blended_color = blend_colors(color, existing_color);
        memcpy(dst, &blended_color, sizeof(unsigned int));
    }
} */



/* void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;
    unsigned int *dst_color;
    

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));

    dst_color = (unsigned int*)dst;
    // Blend the new color with the existing color at the pixel
    *dst_color = blend_colors(color, *dst_color);
} */


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;  // Silently return if out of bounds
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

// void my_mlx_pixel_put(t_data *data, int x, int y, int draw_end, int color)
// {

//     if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
//         return;  // Silently return if out of bounds
//     char    *dst;
//     dst = data->addr + (y * draw_end + x * (data->bpp / 8));
//     *(unsigned int*)dst = color;
// }

/* void my_map_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    
    dst = data->map_addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void  draw_arrow(t_data *data, t_point center, int line_length, int triangle_size, double angle)
{
    int red_color = create_trgb(255, 255, 0, 0);
    int green_color = create_trgb(255, 0, 255, 0);
    int blue_color = create_trgb(255, 0, 0, 255);
    int yellow_color = create_trgb(255, 255, 255, 0);
    int cyan_color = create_trgb(255, 0, 255, 255);
    //calculate the end point of the line
    center.x = data->player[0]->pos[0]->x;
    center.y = data->player[0]->pos[0]->y;
    t_point line_end = {data->player[0]->pos[0]->x, data->player[0]->pos[0]->y - line_length};
    t_point rotated_line_end = rotate_point(line_end, center, angle);

    //calculate the vertices of the triangle
    t_point triangle_tip = rotated_line_end;
    t_point triangle_left = {triangle_tip.x - triangle_size / 2, triangle_tip.y + triangle_size};
    t_point triangle_right = {triangle_tip.x + triangle_size / 2, triangle_tip.y + triangle_size};

    triangle_left = rotate_point(triangle_left, triangle_tip, angle);
    triangle_right = rotate_point(triangle_right, triangle_tip, angle);
    
    //draw the circle
    draw_circle(data, data->player[0]->pos[0]->x, data->player[0]->pos[0]->y, 5, red_color);
    
    //draw the line
    draw_line(data, data->player[0]->pos[0]->x, data->player[0]->pos[0]->y, rotated_line_end.x, rotated_line_end.y, red_color);

    //draw the triangle
    draw_line(data, triangle_tip.x, triangle_tip.y, triangle_left.x, triangle_left.y, green_color); // color is green
    draw_line(data, triangle_tip.x, triangle_tip.y, triangle_right.x, triangle_right.y, blue_color); // color is blue
    draw_line(data, triangle_left.x, triangle_left.y, triangle_right.x, triangle_right.y, red_color); // color is red

    //draw the field of view lines
    t_point fov_left_end = rotate_point(line_end, center, angle - 67.5);
    t_point fov_right_end = rotate_point(line_end, center, angle + 67.5);
    draw_line(data, data->player[0]->pos[0]->x, data->player[0]->pos[0]->y, fov_left_end.x, fov_left_end.y, yellow_color); // color is yellow
    draw_line(data, data->player[0]->pos[0]->x, data->player[0]->pos[0]->y, fov_right_end.x, fov_right_end.y, yellow_color);

    //draw diagonal line
    t_point diagonal_left_end  = rotate_point(line_end, center, angle - 45);
    t_point diagonal_right_end = rotate_point(line_end, center, angle + 45);
    draw_line(data, data->player[0]->pos[0]->x, data->player[0]->pos[0]->y, diagonal_left_end.x, diagonal_left_end.y, cyan_color); // color is cyan
    draw_line(data, data->player[0]->pos[0]->x, data->player[0]->pos[0]->y, diagonal_right_end.x, diagonal_right_end.y, cyan_color);
}

void draw_map(t_data *data, int map[MAP_SIZE][MAP_SIZE], int offset_x, int offset_y)
{

    int white_color = create_trgb(255, 255, 255, 255);
    int red_color = create_trgb(255, 255, 0, 0);
   for(int i = 0; i < MAP_SIZE; i++)
   {
        for(int j = 0; j < MAP_SIZE; j++)
        {
            int x = j * TILE_SIZE + offset_x;
            int y = i * TILE_SIZE + offset_y;
            if (map[i][j] == 1)
            {
                //map_draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FFFFFF);
                draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, white_color);
                //draw_filled_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FFFFFF);
            }
            else
            {
                //map_draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FF0000);
               draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, red_color);
                //draw_filled_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FF0000);
            }
        }
    }
    //write(1, "2\n", 2);
} */


void    cub_draw(t_data *data)
{ 
    raycasting(data);
}