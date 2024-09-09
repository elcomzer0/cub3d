/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:18 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/09 15:50:57 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int map_keycode(int keycode)
{
    if (keycode == KEY_LEFTARROW)
        return 0;
    else if (keycode == KEY_RIGHTARROW)
        return 1;
    else if (keycode == KEY_ANSI_W)
        return 2;
    else if (keycode == KEY_ANSI_S)
        return 3;
    else if (keycode == KEY_ANSI_A)
        return 4;
    else if (keycode == KEY_ANSI_D)
        return 5;
    else
        return -1;
}

int key_hook_press(int keycode, t_data *data)
{
    int mapped_key;
    
    mapped_key = map_keycode(keycode);
    if (mapped_key >= 0 && mapped_key < KEY_COUNT)
        data->key_states[mapped_key] = 1;
    if (keycode == KEY_ESCAPE)
		ft_destroy(data);
    return (0);
}

int key_hook_release(int keycode, t_data *data)
{
    int mapped_key;
     
    mapped_key = map_keycode(keycode);
    if (mapped_key >= 0 && mapped_key < KEY_COUNT)
        data->key_states[mapped_key] = 0;
    return (0);
}

void strafe(t_data *data, int direction, double move_speed)
{
    double strafe_dx;
    double strafe_dy;
    double new_x;
    double new_y;
        
    strafe_dx = data->raycast->plane[0] * direction * move_speed;
    strafe_dy = data->raycast->plane[1] * direction * move_speed;
    new_x = data->player->pos[0] + strafe_dx;
    new_y = data->player->pos[1] + strafe_dy;

    if (data->z_values[(int)new_x][(int)data->player->pos[1]] == 0)
        data->player->pos[0] = new_x;
    if (data->z_values[(int)data->player->pos[0]][(int)new_y] == 0)
        data->player->pos[1] = new_y;
}

void down_key(t_data *data, double move_speed)
{
    double new_x;
    double new_y;
    
    new_x = data->player->pos[0] - data->player->dx * move_speed;
    new_y = data->player->pos[1] - data->player->dy * move_speed;
    if (data->z_values[(int)new_x][(int)data->player->pos[1]] == 0)
        data->player->pos[0] = new_x;
    if (data->z_values[(int)data->player->pos[0]][(int)new_y] == 0)
        data->player->pos[1] = new_y;
}

void up_key(t_data *data, double move_speed)
{
    double new_x;
    double new_y;

    new_x = data->player->pos[0] + data->player->dx * move_speed;
    new_y = data->player->pos[1] + data->player->dy * move_speed;

    if (data->z_values[(int)new_x][(int)data->player->pos[1]] == 0)
        data->player->pos[0] = new_x;
    if (data->z_values[(int)data->player->pos[0]][(int)new_y] == 0)
        data->player->pos[1] = new_y;
}

void right_rot_key(t_data *data, double rotation_speed)
{
    double old_dir_x;
    double old_plane_x;
    
    old_dir_x = data->player->dx;
    old_plane_x = data->raycast->plane[0];
    data->player->dx = old_dir_x * cos(rotation_speed) - data->player->dy * sin(rotation_speed);
    data->player->dy = old_dir_x * sin(rotation_speed) + data->player->dy * cos(rotation_speed);
    data->raycast->plane[0] = old_plane_x * cos(rotation_speed) - data->raycast->plane[1] * sin(rotation_speed);
    data->raycast->plane[1] = old_plane_x * sin(rotation_speed) + data->raycast->plane[1] * cos(rotation_speed);
    data->player->angle = atan2(data->player->dy, data->player->dx) * 180 / M_PI;
    if (data->player->angle < 0)
        data->player->angle += 360;
}

void left_rot_key(t_data *data, double rotation_speed)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = data->player->dx;
    old_plane_x = data->raycast->plane[0];
    data->player->dx = old_dir_x * cos(-rotation_speed) - data->player->dy * sin(-rotation_speed);
    data->player->dy = old_dir_x * sin(-rotation_speed) + data->player->dy * cos(-rotation_speed);
    data->raycast->plane[0] = old_plane_x * cos(-rotation_speed) - data->raycast->plane[1] * sin(-rotation_speed);
    data->raycast->plane[1] = old_plane_x * sin(-rotation_speed) + data->raycast->plane[1] * cos(-rotation_speed);
    data->player->angle = atan2(data->player->dy, data->player->dx) * 180 / M_PI;
    if (data->player->angle < 0)
        data->player->angle += 360;
}

void rerender_frame(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    ceiling_floor(data);
    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->raycast->texture[4].tex_img, 0, 0);
    cub_menu(data);
}

void handle_movement(t_data *data)
{
    double move_speed;
    double rotation_speed;

    move_speed =  MOVE_SPEED;
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
