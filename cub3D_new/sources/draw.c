/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:33:07 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/27 19:09:37 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"
/**
	 * Calculates the texture coordinates for the floor 
				based on the current position and step values.
	* This function is responsible for updating the `cell`,
				`tex`, and `floor` fields of the `data->fl_cl` struct.
	* The `cell` field is set to the integer part of the current 
				floor position, which represents the current tile or cell.
	* The `tex` field is calculated based on the fractional 
				part of the floor position, which represents the 
					position within the current tile.
	* The `floor` field is then updated by adding the `floor_step` values 
				to move to the next position.
	* @param data Pointer to the main data struct 
			containing the rendering information.
*/
void	render_pos_tex(t_data *data)
{
	data->fl_cl->cell[0] = (int)data->fl_cl->floor[0];
	data->fl_cl->cell[1] = (int)data->fl_cl->floor[1];
	data->fl_cl->tex[0] = (int)(TEXTURE_SIZE
			* (data->fl_cl->floor[0] - data->fl_cl->cell[0]))
		& (TEXTURE_SIZE - 1);
	data->fl_cl->tex[1] = (int)(TEXTURE_SIZE
			* (data->fl_cl->floor[1] - data->fl_cl->cell[1]))
		& (TEXTURE_SIZE - 1);
	data->fl_cl->floor[0] += data->fl_cl->floor_step[0];
	data->fl_cl->floor[1] += data->fl_cl->floor_step[1];
}
/**
 * Renders the floor texture and applies shading to the floor.
 * This function iterates over the bottom half of the screen, rendering the 
			floor texture
 * and applying shading to the floor. It calculates the
			texture coordinates for the floor
 * based on the current position and step values, 
			retrieves the pixel information for the
 * current floor texture coordinates, calculates a shading
			factor based on the row distance,
 			 and applies the shading factor to the floor color.
 * @param data Pointer to the main data struct
			containing the rendering information.
*/

void	render_floor(t_data *data)
{
	int	y;
	int	x;
	int	p;

	y = (HEIGHT >> 1);
	p = 0;
	while (y++, y < HEIGHT)
	{
		render_fl_step(data, p, y);
		x = WIDTH;
		while (x--, x >= 0)
		{
			render_pos_tex(data);
			render_fl_shader(data);
			my_xpm_pixel_put(data, x, y, data->fl_cl->color);
		}
	}
}

//  * Renders the ceiling texture and applies shading to the ceiling.
//  * This function iterates over the top half of 
// 			the screen,rendering the ceiling texture
//  * and applying shading to the ceiling. 
// 			It calculates the texture coordinates for the ceiling
//  * based on the current position and step values, 
// 			retrieves the pixel information for the
//  * current ceiling texture coordinates,
// 			calculates a shading factor based on the row distance,
//  * and applies the shading factor to the ceiling color.
//  * @param data Pointer to the main data struct 
// 			containing the rendering information.
void	render_ceiling(t_data *data)
{
	int	y;
	int	x;
	int	p;

	y = -1;
	p = 0;
	while (y++, y < (HEIGHT >> 1))
	{
		render_cl_step(data, p, y);
		x = WIDTH;
		while (x--, x >= 0)
		{
			render_pos_tex(data);
			render_cl_shader(data);
			my_xpm_pixel_put(data, x, y, data->fl_cl->color);
		}
	}
}

void	ceiling_floor(t_data *data)
{
	data->fl_cl->ray_dx[0] = data->player->dx - data->raycast->plane[0];
	data->fl_cl->ray_dy[0] = data->player->dy - data->raycast->plane[1];
	data->fl_cl->ray_dx[1] = data->player->dx + data->raycast->plane[0];
	data->fl_cl->ray_dy[1] = data->player->dy + data->raycast->plane[1];
	render_floor(data);
	render_ceiling(data);
}

int	cub_draw(t_data *data)
{
	ceiling_floor(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->raycast->texture[4].tex_img, 0, 0);
	return (0);
}
