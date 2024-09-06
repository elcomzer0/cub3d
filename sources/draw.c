/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/06 16:10:53 by jorgonca         ###   ########.fr       */
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
   
    //mist_layer(data, 100, 0x000000);
    //draw_gradient(data);
    render_stars(data, 99);
    raycasting(data);
    mlx_put_image_to_window(data->mlx, data->win, data->raycast->texture[4].tex_img, 0, 0);
    return (0);
}