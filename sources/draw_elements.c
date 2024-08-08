/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:30:52 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/08 19:38:38 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}
/* t_color create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
} */

void map_draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        my_map_pixel_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
        
}


void    draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
    
}

void    draw_square(t_data *data, int x, int y, int size, int color)
{
    int i;
    int j;

    i = 0;
    //j = 0;

    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            my_mlx_pixel_put(data, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void    draw_circle(t_data *data, int xc, int yc, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put(data, xc + x, yc + y, color);
            }
        }
    }
}

void draw_triangle(t_data *data, int x, int y, int size, int color)
{

   for (int i = 0; i < size; i++)
   {
        for (int j = 0; j <= i; j++)
        {
            my_mlx_pixel_put(data, x + j, y + i, color);
        }
    }
}

void draw_hexagon(t_data *data, int xc, int yc, int size, int color)
{
    int y = -size;
    while (y <=  size)
    {
        int x = -size;
        while (x <= size)
        {
            if (abs(x) + abs(y) <= size)
            {
                my_mlx_pixel_put(data, xc + x, yc + y, color);
            }
            x++;
        }
        y++;
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
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    
}

void    draw_rainbow(t_data *data)
{
    int colors[] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0x00FFFF00, 0x0000FFFF, 0x00FF00FF};
    int color_count = sizeof(colors) / sizeof(colors[0]);
    int stripe_height = HEIGHT / color_count;

    int y = 0;
    while (y < HEIGHT)
    {
        int color = colors[y / stripe_height];
        int x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    
}

void draw_rectangle(t_data *data, int x, int y, int width, int height, int color)
{
    draw_line(data, x, y, x + width, y, color);
    draw_line(data, x, y, x, y + height, color);
    draw_line(data, x + width, y, x + width, y + height, color);
    draw_line(data, x, y + height, x + width, y + height, color);   
}

void draw_filled_rectangle(t_data *data, int x, int y, int width, int height, int color)
{
    for(int i = y; i < y + height; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            my_map_pixel_put(data, j, i, color);
        }
    }
}

void map_draw_rectangle(t_data *data, int x, int y, int width, int height, int color)
{
    map_draw_line(data, x, y, x + width, y, color);
    map_draw_line(data, x, y, x, y + height, color);
    map_draw_line(data, x + width, y, x + width, y + height, color);
    map_draw_line(data, x, y + height, x + width, y + height, color);
}

t_point rotate_point(t_point p, t_point center, float angle)
{
    t_point rotated;
    float radians = angle * M_PI / 180;

    rotated.x = (p.x - center.x) * cos(radians) - (p.y - center.y) * sin(radians) + center.x;
    rotated.y = (p.x - center.x) * sin(radians) + (p.y - center.y) * cos(radians) + center.y;

    return (rotated);
}

void rot_draw_triangle(t_data *data, t_point p1, t_point p2, t_point p3, float angle)
{
    // Calculate the middpoint of the hypotenuse
    t_point hypotenuse_mid = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    
    // Rotate the points around the hypotenuse midpoint
    t_point rp1 = rotate_point(p1, hypotenuse_mid, angle);
    t_point rp2 = rotate_point(p2, hypotenuse_mid, angle);
    t_point rp3 = rotate_point(p3, hypotenuse_mid, angle);
    
    // Draw the rotated triangle
    draw_line(data, rp1.x, rp1.y, rp2.x, rp2.y, 0x00FF0000);
    draw_line(data, rp2.x, rp2.y, rp3.x, rp3.y, 0x0000FF00);
    draw_line(data, rp3.x, rp3.y, rp1.x, rp1.y, 0x000000FF);
    
}