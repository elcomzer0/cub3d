/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/24 21:55:09 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"



int blend_colors(int src_color, int dest_color)
{
    int src_a = (src_color >> 24) & 0xFF;
    int src_r = (src_color >> 16) & 0xFF;
    int src_g = (src_color >> 8) & 0xFF;
    int src_b = src_color & 0xFF;

    int dest_a = (dest_color >> 24) & 0xFF;
    int dest_r = (dest_color >> 16) & 0xFF;
    int dest_g = (dest_color >> 8) & 0xFF;
    int dest_b = dest_color & 0xFF;

    int out_a = src_a + dest_a * (255 - src_a) / 255;
    
    if (out_a == 0)
    {
        return (0 << 24 | 0 << 16 | 0 << 8 | 0); // Fully transparent
    }

    int out_r = (src_r * src_a + dest_r * dest_a * (255 - src_a) / 255) / out_a;
    int out_g = (src_g * src_a + dest_g * dest_a * (255 - src_a) / 255) / out_a;
    int out_b = (src_b * src_a + dest_b * dest_a * (255 - src_a) / 255) / out_a;

    return (out_a << 24 | out_r << 16 | out_g << 8 | out_b);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;
    unsigned int *dst_color;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    dst_color = (unsigned int*)dst;

    // Blend the new color with the existing color at the pixel
    *dst_color = blend_colors(color, *dst_color);
}


/* void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
} */

void my_map_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    
    dst = data->map_addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void  draw_arrow(t_data *data, t_point center, int line_length, int triangle_size, float angle)
{
    int red_color = create_trgb(255, 255, 0, 0);
    int green_color = create_trgb(255, 0, 255, 0);
    int blue_color = create_trgb(255, 0, 0, 255);
    int yellow_color = create_trgb(255, 255, 255, 0);
    int cyan_color = create_trgb(255, 0, 255, 255);
    //calculate the end point of the line
    t_point line_end = {center.x, center.y - line_length};
    t_point rotated_line_end = rotate_point(line_end, center, angle);

    //calculate the vertices of the triangle
    t_point triangle_tip = rotated_line_end;
    t_point triangle_left = {triangle_tip.x - triangle_size / 2, triangle_tip.y + triangle_size};
    t_point triangle_right = {triangle_tip.x + triangle_size / 2, triangle_tip.y + triangle_size};

    triangle_left = rotate_point(triangle_left, triangle_tip, angle);
    triangle_right = rotate_point(triangle_right, triangle_tip, angle);
    
    //draw the circle
    draw_circle(data, center.x, center.y, 5, red_color);
    
    //draw the line
    draw_line(data, center.x, center.y, rotated_line_end.x, rotated_line_end.y, red_color);

    //draw the triangle
    draw_line(data, triangle_tip.x, triangle_tip.y, triangle_left.x, triangle_left.y, green_color); // color is green
    draw_line(data, triangle_tip.x, triangle_tip.y, triangle_right.x, triangle_right.y, blue_color); // color is blue
    draw_line(data, triangle_left.x, triangle_left.y, triangle_right.x, triangle_right.y, red_color); // color is red

    //draw the field of view lines
    t_point fov_left_end = rotate_point(line_end, center, angle - 67.5);
    t_point fov_right_end = rotate_point(line_end, center, angle + 67.5);
    draw_line(data, center.x, center.y, fov_left_end.x, fov_left_end.y, yellow_color); // color is yellow
    draw_line(data, center.x, center.y, fov_right_end.x, fov_right_end.y, yellow_color);

    //draw diagonal line
    t_point diagonal_left_end  = rotate_point(line_end, center, angle - 45);
    t_point diagonal_right_end = rotate_point(line_end, center, angle + 45);
    draw_line(data, center.x, center.y, diagonal_left_end.x, diagonal_left_end.y, cyan_color); // color is cyan
    draw_line(data, center.x, center.y, diagonal_right_end.x, diagonal_right_end.y, cyan_color);
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
}


void    cub_draw(t_data *data)
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
    
 
    
    /* data->player_x = 1;
    data->player_y = 1; */
    //calculate player position at the center of the map
    

    int color = create_trgb(50, 128, 128, 128); // 0xAARRGGBB (alpha, red, green, blue), grey = (128, 128, 128)
    //Define arrow inputs
    t_point center = {WIDTH / 2 , HEIGHT / 2};
    data->player_x = 1;
    data->player_y = 1;
    //data->map_offset_x = (WIDTH / 2) - (MAP_SIZE * TILE_SIZE / 2)
    int line_length = 100;
    int triangle_size = 30;


    raycasting_2D(data, map, data->arrow_angle);
    //raycasting(data, map, data->map_offset_x, data->map_offset_y);
    draw_circle(data, (WIDTH / 2), (HEIGHT / 2), 100, color); //0x248A8D8F);
    //raycasting_2D(data, map);
   
    draw_arrow(data, center, line_length, triangle_size, data->arrow_angle);
    //display_angle(data);
    //raycasting_2D(data, map, data->map_offset_x, data->map_offset_y);
}