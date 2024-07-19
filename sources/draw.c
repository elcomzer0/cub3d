/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/20 00:38:04 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
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

void    cub_draw(t_data *data)
{
    //Define the vertices of the triangle
    //t_point p1 = {960, 540};
    //t_point p2 = {960, 640};
    //t_point p3 = {1060, 640};
    
       //Define arrow inputs
    t_point center = {960, 540};
    int line_length = 300;
    int triangle_size = 30;
   // data->arrow_angle = 180;
    
        //draw_gradient(data);
   // draw_rainbow(data);
    //draw_square(data, 1460, 540, 100, 0x00FF0000);
//    draw_circle(data, 960, 540, 300, 0x00FF7F00);
    draw_circle(data, 960, 540, 300, 0x248A8D8F);
    //draw_hexagon(data, 460, 540, 100, 0x000000FF);
    //draw_triangle(data, 960, 740, 100, 0x000000FF);
    //draw_line(data, 960, 540, 960, 440, 0x00FF0000);
    //rot_draw_triangle(data, p1, p2, p3, angle);
    draw_arrow(data, center, line_length, triangle_size, data->arrow_angle);
}