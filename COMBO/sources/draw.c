/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/11 16:28:45 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

// void blend_colors_source(t_data *data, int source_color)
// {
    
//     data->src_a = (source_color >> 24) & 0xFF;
//     data->src_r = (source_color >> 16) & 0xFF;
//     data->src_g = (source_color >> 8) & 0xFF;
//     data->src_b = source_color & 0xFF;
// }

// int blend_colors(int src_color, int dest_color, t_data *data)
// {
//     blend_colors_source(data, src_color);

//     data->dest_r = (dest_color >> 16) & 0xFF;
//     data->dest_g = (dest_color >> 8) & 0xFF;
//     data->dest_b = dest_color & 0xFF;
    
//     int out_r = (data->src_r * data->src_a + data->dest_r * (255 - data->src_a)) / 255;
//     int out_g = (data->src_g * data->src_a + data->dest_g * (255 - data->src_a)) / 255;
//     int out_b = (data->src_b * data->src_a + data->dest_b * (255 - data->src_a)) / 255;
//     return (out_r << 16) | (out_g << 8) | out_b;
// }

void my_xpm_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;  
    //unsigned int *dst_color;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    dst = data->raycast->texture[4].tex_addr + (y * data->raycast->texture[4].line_length + x * (data->raycast->texture[4].bpp / 8));
 
    *(unsigned int *)dst = color;
}
    

// void my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {

//     if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
//         return;  // Silently return if out of bounds
//     char    *dst;
//     dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
//     *(unsigned int*)dst = color;
// }





// void    draw_gradient(t_data *data)
// {
//     int y = 0;
//     while (y < HEIGHT)
//     {
//         int x = 0;
//         while (x < WIDTH)
//         {
//             int color = (x * 255 / WIDTH) << 16 | (y * 255 / HEIGHT) << 8;
//             my_xpm_pixel_put(data, x, y, color);
//             x++;
//         }
//         y++;
//     }
    
// }


/**
 * Calculates the source color components from the provided source color.
 *
 * This function takes a source color and extracts the red, green, and blue components into the corresponding fields of the `t_data` struct.
 *
 * @param data Pointer to the main data struct containing rendering information.
 * @param source_color The source color to extract the components from.
 */
void blend_colors_source(t_data *data, int source_color)
{
    data->src_r = (source_color >> 16) & 0xFF;
    data->src_g = (source_color >> 8) & 0xFF;
    data->src_b = source_color & 0xFF;
}

/**
 * Blends two colors based on a given blend factor.
 *
 * This function takes two colors and a blend factor, and returns a new color that is a blend of the two input colors.
 * The blend factor determines the relative contribution of each input color to the output color.
 *
 * @param data Pointer to the main data struct containing rendering information.
 * @param color1 The first color to blend.
 * @param color2 The second color to blend.
 * @param blend_factor The blend factor, between 0.0 and 1.0, that determines the relative contribution of each input color.
 * @return The blended color.
 */
int blend_colors_clfl(t_data *data, int color1, int color2, double blend_factor)
{
    int r;
    int g;
    int b;

    blend_colors_source(data, color1);
    data->dest_r = (color2 >> 16) & 0xFF;
    data->dest_g = (color2 >> 8) & 0xFF;
    data->dest_b = color2 & 0xFF;
    r = (int)((1 - blend_factor) * data->src_r + blend_factor * data->dest_r);
    g = (int)((1 - blend_factor) * data->src_g + blend_factor * data->dest_g);
    b = (int)((1 - blend_factor) * data->src_b + blend_factor * data->dest_b);
    return (r << 16) | (g << 8) | b;
}

/**
 * Applies shading to the ceiling color based on the provided shading factor.
 *
 * This function takes the current ceiling color and a shading factor, and returns a new color with the shading applied.
 * The shading factor is typically calculated based on the distance from the player to the ceiling.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 * @param color The current ceiling color.
 * @param shading_factor The shading factor to apply to the ceiling color.
 * @return The new shaded ceiling color.
 */
int shading_color_ceiling(t_data *data, int color, double shading_factor)
{
    int r;
    int g;
    int b;
    
    r = data->file->text->cr;
	g = data->file->text->cg;
	b = data->file->text->cb;
    data->blend_factor = 0.5;
    data->blend_color = create_trgb(0, r, g, b);
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    r = (int)(r * shading_factor);
    g = (int)(g * shading_factor);
    b = (int)(b * shading_factor);
    color = (r << 16) | (g << 8) | b;
    data->blended_color = blend_colors_clfl(data, color, data->blend_color, data->blend_factor);
    return data->blended_color;
}

/* int shading_color_ceiling(t_data *data, int color, double shading_factor)
{
    //int r, g, b;
    int blended_color;
	int blend_color;
    double blend_factor;
    
    // r = data->file->text->cr;
	// g = data->file->text->cg;
	// b = data->file->text->cb;
    blend_factor = 0.5;
    blend_color = create_trgb(0, data->file->text->cr, data->file->text->cg, data->file->text->cb);
    data->file->text->cr = (color >> 16) & 0xFF;
    data->file->text->cg = (color >> 8) & 0xFF;
    data->file->text->cb = color & 0xFF;
    data->file->text->cr = (int)(data->file->text->cr * shading_factor);
    data->file->text->cg = (int)(data->file->text->cg * shading_factor);
    data->file->text->cb = (int)(data->file->text->cb * shading_factor);
    color = (data->file->text->cr << 16) | (data->file->text->cg << 8) | data->file->text->cb;
    blended_color = blend_colors_clfl(data, color, blend_color, blend_factor);
    return blended_color;
} */

/**
 * Applies shading to the floor color based on the provided shading factor.
 *
 * This function takes the current floor color and a shading factor, and returns a new color with the shading applied.
 * The shading factor is typically calculated based on the distance from the player to the floor.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 * @param color The current floor color.
 * @param shading_factor The shading factor to apply to the floor color.
 * @return The new shaded floor color.
 */
int shading_color_floor(t_data *data, int color, double shading_factor)
{
    int r;
    int g;
    int b;
    
	r = data->file->text->fr;
	g = data->file->text->fg;
	b = data->file->text->fb;
    data->blend_factor = 0.5;
    data->blend_color = create_trgb(0, r, g, b);
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    r = (int)(r * shading_factor);
    g = (int)(g * shading_factor);
    b = (int)(b * shading_factor);
    color = (r << 16) | (g << 8) | b;
    data->blended_color = blend_colors_clfl(data, color, data->blend_color, data->blend_factor);
    return data->blended_color;
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
    data->fl_cl->floor_tex = 0;
    data->fl_cl->color = retrieve_px_info(data, data->fl_cl->tex[0], data->fl_cl->tex[1], data->fl_cl->floor_tex);
    data->fl_cl->shading_factor = 1.0 / (1.0 + data->fl_cl->row_distance * data->fl_cl->row_distance * 0.1);
    data->fl_cl->color = shading_color_ceiling(data, data->fl_cl->color, data->fl_cl->shading_factor);
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
    p = y - (HEIGHT / 2);
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
 * - Setting the floor texture index to 2 (assuming the floor texture is at index 2).
 * - Retrieving the pixel information for the current floor texture coordinates using `retrieve_px_info()`.
 * - Calculating a shading factor based on the row distance.
 * - Applying the shading factor to the floor color using `shading_color_floor()`.
 *
 * @param data Pointer to the main data struct containing the rendering information.
 */
void render_fl_shader(t_data *data)
{
    data->fl_cl->floor_tex = 3; // Assuming floor texture index is 2
    data->fl_cl->color = retrieve_px_info(data, data->fl_cl->tex[0], data->fl_cl->tex[1], data->fl_cl->floor_tex);
    data->fl_cl->shading_factor = 1.0 / (1.0 + data->fl_cl->row_distance * data->fl_cl->row_distance * 0.1);
    data->fl_cl->color = shading_color_floor(data, data->fl_cl->color, data->fl_cl->shading_factor);
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
    
    y = HEIGHT / 2;
    p = 0;
    while (y++, y < HEIGHT)
    {
        render_fl_step(data, p, y);
        x = -1;
        while (x++, x < WIDTH)
        {
            render_pos_tex(data);
            render_fl_shader(data);
            my_xpm_pixel_put(data, x, y, data->fl_cl->color);
        }
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
    
    
    y = -1;
    p = 0;
    while (y++, y < HEIGHT / 2)
    {
        render_cl_step(data, p, y);
        x = -1;
        while (x++, x < WIDTH)
        {
            render_pos_tex(data);
            render_cl_shader(data);
            my_xpm_pixel_put(data, x, y, data->fl_cl->color);
        }
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


int    cub_draw(t_data *data)
{ 
    ceiling_floor(data);
    raycasting(data);

    mlx_put_image_to_window(data->mlx, data->win, data->raycast->texture[4].tex_img, 0, 0);
    return (0);
}