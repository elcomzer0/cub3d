/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/21 01:11:18 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    //write(1, "1\n", 2);
    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    //write(1, "2\n", 2);
    *(unsigned int*)dst = color;
    //write(1, "3\n", 2);
}

void my_map_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    
    dst = data->map_addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void  draw_arrow(t_data *data, t_point center, int line_length, int triangle_size, float angle)
{
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
    draw_circle(data, center.x, center.y, 5, 0x00FF0000);
    
    //draw the line
    draw_line(data, center.x, center.y, rotated_line_end.x, rotated_line_end.y, 0x00FF0000);

    //draw the triangle
    draw_line(data, triangle_tip.x, triangle_tip.y, triangle_left.x, triangle_left.y, 0x0000FF00);
    draw_line(data, triangle_tip.x, triangle_tip.y, triangle_right.x, triangle_right.y, 0x000000FF);
    draw_line(data, triangle_left.x, triangle_left.y, triangle_right.x, triangle_right.y, 0x00FF0000);

    //draw the field of view lines
    t_point fov_left_end = rotate_point(line_end, center, angle - 67.5);
    t_point fov_right_end = rotate_point(line_end, center, angle + 67.5);
    draw_line(data, center.x, center.y, fov_left_end.x, fov_left_end.y, 0x00FFFF00);
    draw_line(data, center.x, center.y, fov_right_end.x, fov_right_end.y, 0x00FFFF00);

    //draw diagonal line
    t_point diagonal_left_end  = rotate_point(line_end, center, angle - 45);
    t_point diagonal_right_end = rotate_point(line_end, center, angle + 45);
    draw_line(data, center.x, center.y, diagonal_left_end.x, diagonal_left_end.y, 0x0000FFFF);
    draw_line(data, center.x, center.y, diagonal_right_end.x, diagonal_right_end.y, 0x0000FFFF);
}

void draw_map(t_data *data, int map[MAP_SIZE][MAP_SIZE], int offset_x, int offset_y)
{
    /* int i;
    int j; */
    
   

/*     while (i < MAP_SIZE)
    {
        j = 0;
        while (j < MAP_SIZE)
        {
            int x = j * TILE_SIZE + offset_x;
            int y = i * TILE_SIZE + offset_y;
            if (map[i][j] == 1)
            {
                draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FFFFFF);
            }
            else
            {
                draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FF0000);
            }
            j++;
        }
    } */
   //write(1, "1\n", 2);
   for(int i = 0; i < MAP_SIZE; i++)
   {
    //write(1, "2\n", 2);
        for(int j = 0; j < MAP_SIZE; j++)
        {
            //write(1, "3\n", 2);
            int x = j * TILE_SIZE + offset_x;
            int y = i * TILE_SIZE + offset_y;
            if (map[i][j] == 1)
            {
                //write(1, "4\n", 2);
                //map_draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FFFFFF);
                draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FFFFFF);
                //draw_filled_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FFFFFF);
                //write(1, "4\n", 2);
            }
            else
            {
                //write(1, "5\n", 2);
                //map_draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FF0000);
               draw_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FF0000);
                //draw_filled_rectangle(data, x, y, TILE_SIZE, TILE_SIZE, 0x00FF0000);
            }
        }
    }
    //write(1, "2\n", 2);
}

/* void display_angle(t_data *data)
{
    char angle_str[50];
    float_to_string(data->arrow_angle, angle_str);
    mlx_string_put(data->mlx, data->win, 10, 10, 0x00FFFFFF, angle_str);
    //free(angle_str);
} */
void    cub_draw(t_data *data)
{
    int map[MAP_SIZE][MAP_SIZE] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    //t_point center;
    
    data->player_x = 1;
    data->player_y = 1;
    
    //center = (t_point){data->map_offset_x + data->player_x * TILE_SIZE + TILE_SIZE / 2, data->map_offset_y + data->player_y * TILE_SIZE + TILE_SIZE / 2};
    //Define the vertices of the triangle
    //t_point p1 = {960, 540};
    //t_point p2 = {960, 640};
    //t_point p3 = {1060, 640};
    
       //Define arrow inputs
    t_point center = {WIDTH / 2 , HEIGHT / 2};
    int line_length = 100;
    int triangle_size = 30;
    //data->arrow_angle = 0.0f;
    //data->arrow_angle
    
   // data->arrow_angle = 180;
    
        //draw_gradient(data);
   // draw_rainbow(data);
    //draw_square(data, 1460, 540, 100, 0x00FF0000);
//    draw_circle(data, 960, 540, 300, 0x00FF7F00);

    draw_circle(data, (WIDTH / 2), (HEIGHT / 2), 100, 0x248A8D8F);
    //draw_hexagon(data, 460, 540, 100, 0x000000FF);
    //draw_triangle(data, 960, 740, 100, 0x000000FF);
    //draw_line(data, 960, 540, 960, 440, 0x00FF0000);
    //rot_draw_triangle(data, p1, p2, p3, angle);
    draw_arrow(data, center, line_length, triangle_size, data->arrow_angle);
    //display_angle(data);
    raycasting(data, map, data->map_offset_x, data->map_offset_y);
}