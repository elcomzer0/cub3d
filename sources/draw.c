/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/06 03:15:32 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

#define PERLIN_SIZE 256

static int permutation[PERLIN_SIZE] = { /* Permutation array */ };
static int p[PERLIN_SIZE * 2];

void init_perlin_noise()
{
    for (int i = 0; i < PERLIN_SIZE; i++)
    {
        p[PERLIN_SIZE + i] = p[i] = permutation[i];
    }
}

static double fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

static double lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

static double grad(int hash, double x, double y, double z)
{
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double perlin_noise(double x, double y, double z)
{
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;

    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
                        lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
                lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
                     lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

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

void ceiling_floor_v2(t_data *data)
{
{
    int x;
    int y;
    int color1;
    int color2;

    init_perlin_noise(); // Initialize the Perlin noise

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y <= HEIGHT)
        {
            if (y < HEIGHT / 2)
            {
                // Red to blue gradient for the ceiling
                int red = 255 - (y * 255 / (HEIGHT / 2));
                int blue = y * 255 / (HEIGHT / 2);
                color1 = (red << 16) | (blue);

                // Add misty clouds effect using Perlin noise
                double noise = perlin_noise(x * 0.05, y * 0.05, 0.0); // Adjust scaling factor
                int alpha = (int)((noise + 1) * 32); // Reduce alpha to make the effect less intense
                int white = 0xFFFFFF;
                color1 = blend_colors((alpha << 24) | white, color1);

                my_xpm_pixel_put(data, x, y, color1);
            }
            else
            {
                // Lighter magenta to darker magenta gradient for the floor
                int light_magenta = 255 - ((y - HEIGHT / 2) * 127 / (HEIGHT / 2)); // Lighter magenta
                int dark_magenta = 128 + ((y - HEIGHT / 2) * 127 / (HEIGHT / 2)); // Darker magenta
                color2 = (light_magenta << 16) | (0 << 8) | dark_magenta;
                my_xpm_pixel_put(data, x, y, color2);
            }
            y++;
        }
        x++;
    }
}

}
#include <stdlib.h> // For rand()

void ceiling_floor_v3(t_data *data)
{
    int x;
    int y;
    int color1;
    int color2;

    init_perlin_noise(); // Initialize the Perlin noise

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y <= HEIGHT)
        {
            if (y < HEIGHT / 2)
            {
                // Red to blue gradient for the ceiling
                int red = 255 - (y * 255 / (HEIGHT / 2));
                int blue = y * 255 / (HEIGHT / 2);
                color1 = (red << 16) | (blue);

                // Add misty clouds effect using Perlin noise
                double noise = perlin_noise(x * 0.1, y * 0.1, 0.0);
                int alpha = (int)((noise + 1) * 32); // Further reduce alpha to make the effect less intense
                int white = 0xFFFFFF;
                color1 = blend_colors((alpha << 24) | white, color1);

                my_xpm_pixel_put(data, x, y, color1);
            }
            else
            {
                // Lighter magenta to darker magenta gradient for the floor
                int light_magenta = 255 - ((y - HEIGHT / 2) * 127 / (HEIGHT / 2)); // Lighter magenta
                int dark_magenta = 128 + ((y - HEIGHT / 2) * 127 / (HEIGHT / 2)); // Darker magenta
                color2 = (light_magenta << 16) | (0 << 8) | dark_magenta;
                my_xpm_pixel_put(data, x, y, color2);
            }
            y++;
        }
        x++;
    }
}

#include <stdlib.h> // For rand()

void ceiling_floor_v4(t_data *data)
{
    int x;
    int y;
    int color1;
    int color2;

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y <= HEIGHT)
        {
            if (y < HEIGHT / 2)
            {
                // Red to blue gradient for the ceiling
                int red = 255 - (y * 255 / (HEIGHT / 2));
                int blue = y * 255 / (HEIGHT / 2);
                color1 = (red << 16) | (blue);

                // Add misty clouds effect
                int alpha = rand() % 30 + 10; // Random transparency between 50 and 150
                int white = 0xFFFAAA;
                color1 = blend_colors((alpha << 24) | white, color1);

                my_xpm_pixel_put(data, x, y, color1);
            }
            else
            {
                // Lighter magenta to darker magenta gradient for the floor
                int light_magenta = 255 - ((y - HEIGHT / 2) * 127 / (HEIGHT / 2)); // Lighter magenta
                int dark_magenta = 128 + ((y - HEIGHT / 2) * 127 / (HEIGHT / 2)); // Darker magenta
                color2 = (light_magenta << 16) | (0 << 8) | dark_magenta;
                my_xpm_pixel_put(data, x, y, color2);
            }
            y++;
        }
        x++;
    }
}

void mist_layer(t_data *data, int alpha, int dark_color)
{
    int x;
    int y;
    int blended_color;

    for (x = 0; x < WIDTH; x++)
    {
        for (y = 0; y < HEIGHT; y++)
        {
            int current_color = dark_color; // Assuming you have a function to get the current pixel color
            blended_color = blend_colors((alpha << 24) | dark_color, current_color);
            my_xpm_pixel_put(data, x, y, blended_color);
        }
    }
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
    ceiling_floor_v5(data);
    //draw_gradient(data);
    render_stars(data, 99);
    raycasting(data);
    //mist_layer(data, 100, 0x000000);
    mlx_put_image_to_window(data->mlx, data->win, data->raycast->texture[4].tex_img, 0, 0);
    return (0);
}