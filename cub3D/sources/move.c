/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:18 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/12 16:08:39 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	map_keycode(int keycode)
{
	if (keycode == KEY_LEFTARROW)
		return (0);
	else if (keycode == KEY_RIGHTARROW)
		return (1);
	else if (keycode == KEY_ANSI_W)
		return (2);
	else if (keycode == KEY_ANSI_S)
		return (3);
	else if (keycode == KEY_ANSI_A)
		return (4);
	else if (keycode == KEY_ANSI_D)
		return (5);
	else
		return (-1);
}

int	key_hook_press(int keycode, t_data *data)
{
	int	mapped_key;

	mapped_key = map_keycode(keycode);
	if (mapped_key >= 0 && mapped_key < KEY_COUNT)
		data->key_states[mapped_key] = 1;
	if (keycode == KEY_ESCAPE)
		ft_destroy(data);
	return (0);
}

int	key_hook_release(int keycode, t_data *data)
{
	int	mapped_key;

	mapped_key = map_keycode(keycode);
	if (mapped_key >= 0 && mapped_key < KEY_COUNT)
		data->key_states[mapped_key] = 0;
	return (0);
}

void	strafe(t_data *data, int direction, double move_speed)
{
	double	strafe_dx;
	double	strafe_dy;
	double	new_x;
	double	new_y;

	strafe_dx = data->raycast->plane[0] * direction * move_speed;
	strafe_dy = data->raycast->plane[1] * direction * move_speed;
	new_x = data->player->pos[0] + strafe_dx;
	new_y = data->player->pos[1] + strafe_dy;
	if (data->z_values[(int)new_x][(int)data->player->pos[1]] == 0)
		data->player->pos[0] = new_x;
	if (data->z_values[(int)data->player->pos[0]][(int)new_y] == 0)
		data->player->pos[1] = new_y;
}

void	handle_movement(t_data *data)
{
	double	move_speed;
	double	rotation_speed;	

	move_speed = MOVE_SPEED;
	rotation_speed = ROT_SPEED;
	if (data->key_states[map_keycode(KEY_LEFTARROW)])
		left_rot_key(data, rotation_speed);
	if (data->key_states[map_keycode(KEY_RIGHTARROW)])
		right_rot_key(data, rotation_speed);
	if (data->key_states[map_keycode(KEY_ANSI_W)])
		up_key(data, move_speed);
	if (data->key_states[map_keycode(KEY_ANSI_S)])
		down_key(data, move_speed);
	if (data->key_states[map_keycode(KEY_ANSI_A)])
		strafe(data, -1, move_speed);
	if (data->key_states[map_keycode(KEY_ANSI_D)])
		strafe(data, 1, move_speed);
	rerender_frame(data);
}
