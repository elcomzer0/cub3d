/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:45:49 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/26 19:36:44 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

//  * Retrieves the color of a pixel from a texture at 
// 		the specified coordinates.
//  * This function checks if the given coordinates are
// 		 within the bounds of the texture,
//  * and if so, it retrieves the color of the pixel at
// 		 those coordinates. The function
//  * assumes the texture is in XRGB format (little-endian).
//  * @param data The main data structure containing the game state.
//  * @param x The x-coordinate of the pixel within the texture.
//  * @param y The y-coordinate of the pixel within the texture.
//  * @param texture_index The index of the texture to retrieve the
// 		 pixel from.
//  * @return The color of the pixel at the specified coordinates, 
// 		or 0 if the coordinates are out of bounds.

int	retrieve_px_info(t_data *data, int x, int y, int texture_index)
{
	char	*pixel_data;
	int		pixel_index;
	int		color;

	if (x < 0 || x >= data->raycast->texture[texture_index].width
		|| y < 0 || y >= data->raycast->texture[texture_index].height)
		return (0);
	pixel_index = (y * data->raycast->texture[texture_index].line_length)
		+ (x * (data->raycast->texture[texture_index].bpp >> 3));
	pixel_data = data->raycast->texture[texture_index].tex_addr + pixel_index;
	color = (pixel_data[3] << 24) | (pixel_data[2] << 16)
		| (pixel_data[1] << 8) | pixel_data[0];
	return (color);
}

//  * Determines the index of the texture to use for a given wall type.
//  * This function takes a wall type value and returns the 
// 		corresponding texture index.
//  * The wall type values are expected to be in the range of 1 to 4.
//  * @param data The main data structure containing the game state.
//  * @param wall_type The type of the wall, ranging from 1 to 4.
//  * @return The index of the texture to use for the given wall type.

int	xpm_switcher(t_data *data, int wall_type)
{
	(void)data;
	if (wall_type == 1)
		return (0);
	else if (wall_type == 2)
		return (1);
	else if (wall_type == 3)
		return (2);
	else
		return (3);
}

//  * Calculates the floor of a given floating-point number.
//  *
//  * This function takes a floating-point number `x` and 
// 		returns the largest integer
//  * that is less than or equal to `x`. If `x` is already
// 		 an integer, the function
//  * simply returns `x`.
//  * @param x The floating-point number to calculate the floor for.
//  * @return The largest integer that is less than or equal to `x`.

int	ft_floor(double x)
{
	int	result;

	result = (int)x;
	if (x >= 0 || (double)result == x)
		return (result);
	else
		return (result - 1);
}

int	key_loop(t_data *data)
{
	handle_movement(data);
	return (0);
}
