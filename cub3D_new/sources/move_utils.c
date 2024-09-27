/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:06:07 by miturk            #+#    #+#             */
/*   Updated: 2024/09/27 19:12:42 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	down_key(t_data *data, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos[0] - data->player->dx * -move_speed;
	new_y = data->player->pos[1] - data->player->dy * -move_speed;
	if (data->z_values[(int)new_x][(int)data->player->pos[1]] == 0)
		data->player->pos[0] = new_x;
	if (data->z_values[(int)data->player->pos[0]][(int)new_y] == 0)
		data->player->pos[1] = new_y;
}

void	up_key(t_data *data, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos[0] + data->player->dx * -move_speed;
	new_y = data->player->pos[1] + data->player->dy * -move_speed;
	if (data->z_values[(int)new_x][(int)data->player->pos[1]] == 0)
		data->player->pos[0] = new_x;
	if (data->z_values[(int)data->player->pos[0]][(int)new_y] == 0)
		data->player->pos[1] = new_y;
}

void	right_rot_key(t_data *data, double rotation_speed)
{
	double	rad_to_deg;
	double	old_dir_x;
	double	old_plane_x;	

	rad_to_deg = 180 / M_PI;
	old_dir_x = data->player->dx;
	old_plane_x = data->raycast->plane[0];
	data->player->dx = old_dir_x * cos(rotation_speed)
		- data->player->dy * sin(rotation_speed);
	data->player->dy = old_dir_x * sin(rotation_speed)
		+ data->player->dy * cos(rotation_speed);
	data->raycast->plane[0] = old_plane_x * cos(rotation_speed)
		- data->raycast->plane[1] * sin(rotation_speed);
	data->raycast->plane[1] = old_plane_x * sin(rotation_speed)
		+ data->raycast->plane[1] * cos(rotation_speed);
	data->player->angle = atan2(data->player->dy, data->player->dx)
		* rad_to_deg;
	if (data->player->angle < 0)
		data->player->angle += 360;
}

void	left_rot_key(t_data *data, double rotation_speed)
{
	double	rad_to_deg;
	double	old_dir_x;
	double	old_plane_x;	

	rad_to_deg = 180 / M_PI;
	old_dir_x = data->player->dx;
	old_plane_x = data->raycast->plane[0];
	data->player->dx = old_dir_x * cos(-rotation_speed)
		- data->player->dy * sin(-rotation_speed);
	data->player->dy = old_dir_x * sin(-rotation_speed)
		+ data->player->dy * cos(-rotation_speed);
	data->raycast->plane[0] = old_plane_x * cos(-rotation_speed)
		- data->raycast->plane[1] * sin(-rotation_speed);
	data->raycast->plane[1] = old_plane_x * sin(-rotation_speed)
		+ data->raycast->plane[1] * cos(-rotation_speed);
	data->player->angle = atan2(data->player->dy, data->player->dx)
		* rad_to_deg;
	if (data->player->angle < 0)
		data->player->angle += 360;
}

void	rerender_frame(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	ceiling_floor(data);
	cub_draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win,
		data->raycast->texture[4].tex_img, 0, 0);
}
