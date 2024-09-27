/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:30:52 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/13 16:36:42 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

//  * Calculates the source color components from the provided source color.
//  * This function takes a source color and extracts the red, 
// 		green, and blue components into the 
// 			corresponding fields of the `t_data` struct.
//  * @param data Pointer to the main data struct 
// 			containing rendering information.
//  * @param source_color The source color to extract the components from.

void	blend_colors_source(t_data *data, int source_color)
{
	data->src_r = (source_color >> 16) & 0xFF;
	data->src_g = (source_color >> 8) & 0xFF;
	data->src_b = source_color & 0xFF;
}

//  * Renders the floor texture and applies shading to the floor.
//  *
//  * This function is responsible for:
//  * - Setting the floor texture index to 3 (assuming the floor 
// 			texture is at index 3).
//  * - Retrieving the pixel information for the 
// 			current floor texture coordinates using `retrieve_px_info()`.
//  * - Calculating a shading factor based on the row distance.
//  * - Applying the shading factor to the floor 
// 			color using `shading_color_floor()`.
//  * @param data Pointer to the main data struct 
// 			containing the rendering information.

void	render_cl_shader(t_data *data)
{
	data->fl_cl->floor_tex = 0;
	data->fl_cl->color = retrieve_px_info(data, data->fl_cl->tex[0],
			data->fl_cl->tex[1], data->fl_cl->floor_tex);
	data->fl_cl->shading_factor = 1.0 / (1.0 + data->fl_cl->row_distance
			* data->fl_cl->row_distance * 0.1);
	data->fl_cl->color = shading_color_ceiling(data, data->fl_cl->color,
			data->fl_cl->shading_factor);
}

//  * Calculates the texture coordinates 
// 		for the floor based on the current position and step values.
//  * This function is responsible for updating the `cell`, `tex`, 
// 			and `floor` fields of the `data->fl_cl` struct.
//  * The `cell` field is set to the integer part of the 
// 			current floor position, which represents the current tile or cell.
//  * The `tex` field is calculated based on the fractional part of the 
// 			floor position, which represents the position 
// 				within the current tile.
//  * The `floor` field is then updated by adding the 
// 			`floor_step` values to move to the next position.
//  * @param data Pointer to the main data struct containing 
// 			the rendering information.
//  * @param p The current row index.
//  * @param y The current column index.

void	render_cl_step(t_data *data, int p, int y)
{
	p = (HEIGHT >> 1) - y;
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
