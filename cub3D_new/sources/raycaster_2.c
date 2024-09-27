/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:20:21 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/27 19:10:19 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

//  * Calculates the perpendicular distance from the player to the wall.
//  * This function determines the perpendicular
// 			 distance from the player's 
//  * position to the wall that the current ray 
// 			has intersected. 
//  * The calculation depends on whether the ray
// 			 intersected the wall on a vertical
//  * or horizontal grid line.
//  * @param data The main data structure containing the game state.

void	perp_wall_dist(t_data *data)
{
	int	step_shifted_x;
	int	step_shifted_y;

	step_shifted_x = (1 - data->raycast->step[0]);
	step_shifted_y = (1 - data->raycast->step[1]);
	if (data->raycast->side == 0)
		data->raycast->perp_wall_dist = (data->raycast->map_x
				- data->player->pos[0] + (step_shifted_x >> 1))
			/ data->raycast->ray_dir[0];
	else
		data->raycast->perp_wall_dist = (data->raycast->map_y
				- data->player->pos[1] + (step_shifted_y >> 1))
			/ data->raycast->ray_dir[1];
}

//  * Calculates the ray direction for 
// 		a given x-coordinate in the rendering loop.
//  * This function calculates the ray direction vector 
// 			based on the player's
//  * direction and the camera plane. The resulting ray 
// 			direction vector is stored
//  * in the `data->raycast->ray_dir[0]` struct.
//  * @param data The main data structure containing the game state.
//  * @param x The x-coordinate of the current ray being cast.

void	calculate_ray_direction(t_data *data, int x)
{
	data->raycast->camera_x = 2 * (WIDTH - 1 - x) / (double)WIDTH - 1;
	data->raycast->ray_dir[0] = data->player->dx + data->raycast->plane[0]
		* data->raycast->camera_x;
	data->raycast->ray_dir[1] = data->player->dy + data->raycast->plane[1]
		* data->raycast->camera_x;
}

//  * Calculates the map position for the current ray being cast.
//  *
//  * This function calculates the integer map coordinates 
// 		(map_x, map_y) based on
//  * the player's current position. These map coordinates 
// 		are used to determine
//  * which grid cell the ray is currently in during the raycasting process.
//  *
//  * @param data The main data structure containing the game state.

void	calculate_map_position(t_data *data)
{
	data->raycast->map_x = (int)data->player->pos[0];
	data->raycast->map_y = (int)data->player->pos[1];
}

//  * Calculates the delta distance values for the
// 		 ray casting algorithm.
//  * The delta distance values determine how far 
// 		the ray has to travel in the
//  *  x and y directions to reach the next grid line.
//  *
//  * @param data A pointer to the main data struct
// 		 containing the ray casting information.

void	rc_delta_dist(t_data *data)
{
	if (data->raycast->ray_dir[0] == 0)
		data->raycast->delta_dist[0] = 1e30;
	else
		data->raycast->delta_dist[0] = fabs(1 / data->raycast->ray_dir[0]);
	if (data->raycast->ray_dir[1] == 0)
		data->raycast->delta_dist[1] = 1e30;
	else
		data->raycast->delta_dist[1] = fabs(1 / data->raycast->ray_dir[1]);
}

//  * Calculates the step values and side distance
// 		 values for the ray casting algorithm.
//  * The step values determine the direction the 
// 		ray moves (left/right, up/down) in the map grid.
//  * The side distance values determine how far 
// 		the ray has to travel to reach the next grid line.
//  *
//  * @param data A pointer to the main data struct 
// 			containing the ray casting information.

void	rc_side_step(t_data *data)
{
	if (data->raycast->ray_dir[0] < 0)
	{
		data->raycast->step[0] = -1;
		data->raycast->side_dist[0] = (data->player->pos[0]
				- data->raycast->map_x) * data->raycast->delta_dist[0];
	}
	else
	{
		data->raycast->step[0] = 1;
		data->raycast->side_dist[0] = (data->raycast->map_x
				+ 1.0 - data->player->pos[0]) * data->raycast->delta_dist[0];
	}
	if (data->raycast->ray_dir[1] < 0)
	{
		data->raycast->step[1] = -1;
		data->raycast->side_dist[1] = (data->player->pos[1]
				- data->raycast->map_y) * data->raycast->delta_dist[1];
	}
	else
	{
		data->raycast->step[1] = 1;
		data->raycast->side_dist[1] = (data->raycast->map_y
				+ 1.0 - data->player->pos[1]) * data->raycast->delta_dist[1];
	}
}
