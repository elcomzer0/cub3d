/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwagons <ggwagons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:44:44 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/11 22:16:41 by ggwagons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

//  * Applies shading to a wall based on the distance from the player 
// 		and the wall's orientation.
//  * This function calculates a shading factor based on the 
// 			perpendicular distance to the wall and the wall's orientation
//  * (vertical or horizontal, and the direction the wall is 
// 			facing). The shading factor is used to adjust the color of the
//  * wall when rendering. Side is 0 for vertical walls and 1
// 			 for horizontal walls. 
//  * @param data The main data structure containing the game state.
//  * @param shading_factor The initial shading factor, which 
// 		will be adjusted by this function.
//  * @return The adjusted shading factor.

double	apply_shading(t_data *data, double shading_factor)
{
	double	dist;

	dist = data->raycast->perp_wall_dist;
	if (data->raycast->side == 0)
	{
		if (data->raycast->ray_dir[0] > 0)
			shading_factor = 1.0 / (1.0 + dist * dist * EA_LT_SHADER);
		else
			shading_factor = 1.0 / (1.0 + dist * dist * EA_DK_SHADER);
	}
	else
	{
		if (data->raycast->ray_dir[1] > 0)
			shading_factor = 1.0 / (1.0 + dist * dist * NO_LT_SHADER);
		else
			shading_factor = 1.0 / (1.0 + dist * dist * NO_DK_SHADER);
	}
	return (shading_factor);
}

//  * Applies shading to a color based on a shading factor.
//  * This function takes a color value and a shading factor, and returns a new
//  * color value with the red, green, and blue components 
//   	adjusted based on the shading factor.
//  * @param color The original color value.
//  * @param shading_factor The shading factor to apply, between 0.0 and 1.0.
//  * @return The shaded color value.

int	shading_color(int color, double shading_factor)
{
	int	r;
	int	g;
	int	b;
	int	shaded_color;

	r = ((color >> 16) & 0xFF) * shading_factor;
	g = ((color >> 8) & 0xFF) * shading_factor;
	b = (color & 0xFF) * shading_factor;
	shaded_color = (r << 16) | (g << 8) | b;
	return (shaded_color);
}
