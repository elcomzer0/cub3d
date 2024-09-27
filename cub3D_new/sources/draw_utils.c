/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:31:14 by ggwagons          #+#    #+#             */
/*   Updated: 2024/09/26 19:50:39 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

/**
 * Blends two colors based on a given blend factor.
 * This function takes two colors and a blend factor, and returns a new
			 color that is a blend of the two input colors.
 * The blend factor determines the relative contribution of each input 
			color to the output color.
 * @param data Pointer to the main 
			data struct containing rendering information.
 * @param color1 The first color to blend.
 * @param color2 The second color to blend.
 * @param blend_factor The blend factor, between 0.0 and 1.0, 
			that determines the relative contribution of each input color.
 * @return The blended color.
*/
int	blend_colors_clfl(t_data *data, int color1, int color2, double blend_factor)
{
	int	r;
	int	g;
	int	b;

	blend_colors_source(data, color1);
	data->dest_r = (color2 >> 16) & 0xFF;
	data->dest_g = (color2 >> 8) & 0xFF;
	data->dest_b = color2 & 0xFF;
	r = (int)((1 - blend_factor) * data->src_r + blend_factor * data->dest_r);
	g = (int)((1 - blend_factor) * data->src_g + blend_factor * data->dest_g);
	b = (int)((1 - blend_factor) * data->src_b + blend_factor * data->dest_b);
	return ((r << 16) | (g << 8) | b);
}

// * Applies shading to the ceiling color based on the provided shading factor.
//  * This function takes the current ceiling color and a 
// 			shading factor, and returns a new color with the shading applied.
//  * The shading factor is typically calculated based on 
// 			the distance from the player to the ceiling.
//  * @param data Pointer to the main data struct 
// 			containing the rendering information.
//  * @param color The current ceiling color.
//  * @param shading_factor The shading factor to apply to the ceiling color.
//  * @return The new shaded ceiling color.

int	shading_color_ceiling(t_data *data, int color, double shading_factor)
{
	int	r;
	int	g;
	int	b;

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
	data->blended_color = blend_colors_clfl(data, color,
			data->blend_color, data->blend_factor);
	return (data->blended_color);
}

//  * Applies shading to the floor color based on 
// 			the provided shading factor.
//  * This function takes the current floor color 
// 		and a shading factor, and returns a new color with the shading applied.
//  * The shading factor is typically calculated based 
// 			on the distance from the player to the floor.
//  * @param data Pointer to the main data struct 
// 			containing the rendering information.
//  * @param color The current floor color.
//  * @param shading_factor The shading factor to apply to the floor color.
//  * @return The new shaded floor color.

int	shading_color_floor(t_data *data, int color, double shading_factor)
{
	int	r;
	int	g;
	int	b;

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
	data->blended_color = blend_colors_clfl(data, color,
			data->blend_color, data->blend_factor);
	return (data->blended_color);
}

//  * Calculates the texture coordinates for the 
// 	floor based on the current position and step values.
//  * This function is responsible for updating the `cell`,
// 			 `tex`, and `floor` fields of the `data->fl_cl` struct.
//  * The `cell` field is set to the integer part of the current 
// 			floor position, which represents the current tile or cell.
//  * The `tex` field is calculated based on the fractional part of 
// 			the floor position, which represents 
// 					the position within the current tile.
//  * The `floor` field is then updated by adding the `floor_step` 
// 			values to move to the next position.
//  * @param data Pointer to the main data struct 
// 			containing the rendering information.

void	render_fl_step(t_data *data, int p, int y)
{
	p = y - (HEIGHT >> 1);
	data->fl_cl->pos_z = 0.5 * HEIGHT;
	data->fl_cl->row_distance = data->fl_cl->pos_z / p;
	data->fl_cl->floor_step[0] = data->fl_cl->row_distance
		* (data->fl_cl->ray_dx[1] - data->fl_cl->ray_dx[0]) / WIDTH;
	data->fl_cl->floor_step[1] = data->fl_cl->row_distance
		* (data->fl_cl->ray_dy[1] - data->fl_cl->ray_dy[0]) / WIDTH;
	data->fl_cl->floor[0] = data->player->pos[0]
		+ data->fl_cl->row_distance * data->fl_cl->ray_dx[0];
	data->fl_cl->floor[1] = data->player->pos[1]
		+ data->fl_cl->row_distance * data->fl_cl->ray_dy[0];
}

//  * Renders the floor texture and applies shading to the floor.
//  *
//  * This function is responsible for:
//  * - Setting the floor texture index to 2
// 			(assuming the floor texture is at index 2).
//  * - Retrieving the pixel information for the current 
// 			floor texture coordinates using `retrieve_px_info()`.
//  * - Calculating a shading factor based on the row distance.
//  * - Applying the shading factor to the floor 
// 			color using `shading_color_floor()`.
//  *
//  * @param data Pointer to the main data struct 
// 			containing the rendering information.

void	render_fl_shader(t_data *data)
{
	data->fl_cl->floor_tex = 3;
	data->fl_cl->color = retrieve_px_info(data, data->fl_cl->tex[0],
			data->fl_cl->tex[1], data->fl_cl->floor_tex);
	data->fl_cl->shading_factor = 1.0 / (1.0 + data->fl_cl->row_distance
			* data->fl_cl->row_distance * 0.1);
	data->fl_cl->color = shading_color_floor(data, data->fl_cl->color,
			data->fl_cl->shading_factor);
}
