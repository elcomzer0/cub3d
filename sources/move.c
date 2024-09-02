/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:18 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/02 18:21:41 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int map_keycode(int keycode)
{
    if (keycode == KEY_LEFTARROW)
    {
        return 0;
    }
    else if (keycode == KEY_RIGHTARROW)
    {
        return 1;
    }
    else if (keycode == KEY_ANSI_W)
    {
        return 2;
    }
    else if (keycode == KEY_ANSI_S)
    {
        return 3;
    }
    else if (keycode == KEY_ANSI_A)
    {
        return 4;
    }
    else if (keycode == KEY_ANSI_D)
    {
        return 5;
    }
    else
    {
        return -1; // Invalid key
    }
}


int key_hook_press(int keycode, t_data *data)
{
    int mapped_key = map_keycode(keycode);
    if (mapped_key >= 0 && mapped_key < KEY_COUNT)
        data->key_states[mapped_key] = 1;
    if (keycode == KEY_ESCAPE)
    {
        ft_destroy(data);
    }
    return (0);
}

int key_hook_release(int keycode, t_data *data)
{
    int mapped_key = map_keycode(keycode);
    if (mapped_key >= 0 && mapped_key < KEY_COUNT)
        data->key_states[mapped_key] = 0;
    return (0);
}

void strafe(t_data *data, int direction, double move_speed)
{
    double strafe_dx = data->raycast->plane[0]->x * direction * move_speed;
    double strafe_dy = data->raycast->plane[0]->y * direction * move_speed;

    double new_x = data->player[0]->pos[0]->x + strafe_dx;
    double new_y = data->player[0]->pos[0]->y + strafe_dy;

    if (data->z_values[(int)new_y][(int)new_x] == 0)
    {
        data->player[0]->pos[0]->x = new_x;
        data->player[0]->pos[0]->y = new_y;
    }
}

void handle_movement(t_data *data)
{
    double move_speed =  0.015; // data->move_speed;
    double rotation_speed = 0.01; // data->rotation_speed;

      // Rotation
       if (data->key_states[map_keycode(KEY_LEFTARROW)])
       {
        double oldDirX = data->player[0]->dx;
        data->player[0]->dx = oldDirX * cos(-rotation_speed) - data->player[0]->dy * sin(-rotation_speed);
        data->player[0]->dy = oldDirX * sin(-rotation_speed) + data->player[0]->dy * cos(-rotation_speed);

        double oldPlaneX = data->raycast->plane[0]->x;
        data->raycast->plane[0]->x = oldPlaneX * cos(-rotation_speed) - data->raycast->plane[0]->y * sin(-rotation_speed);
        data->raycast->plane[0]->y = oldPlaneX * sin(-rotation_speed) + data->raycast->plane[0]->y * cos(-rotation_speed);
    }
    if (data->key_states[map_keycode(KEY_RIGHTARROW)])
    {
        // Rotate right
        // Rotate left
        double oldDirX = data->player[0]->dx;
        data->player[0]->dx = oldDirX * cos(rotation_speed) - data->player[0]->dy * sin(rotation_speed);
        data->player[0]->dy = oldDirX * sin(rotation_speed) + data->player[0]->dy * cos(rotation_speed);

        double oldPlaneX = data->raycast->plane[0]->x;
        data->raycast->plane[0]->x = oldPlaneX * cos(rotation_speed) - data->raycast->plane[0]->y * sin(rotation_speed);
        data->raycast->plane[0]->y = oldPlaneX * sin(rotation_speed) + data->raycast->plane[0]->y * cos(rotation_speed);
    }
     if (data->key_states[map_keycode(KEY_ANSI_W)]) {
        double newX = data->player[0]->pos[0]->x + data->player[0]->dx * move_speed;
        double newY = data->player[0]->pos[0]->y + data->player[0]->dy * move_speed;

        if (data->z_values[(int)newY][(int)newX] == 0) {
            data->player[0]->pos[0]->x = newX;
            data->player[0]->pos[0]->y = newY;
        }
    }
    if (data->key_states[map_keycode(KEY_ANSI_S)]) {
        double newX = data->player[0]->pos[0]->x - data->player[0]->dx * move_speed;
        double newY = data->player[0]->pos[0]->y - data->player[0]->dy * move_speed;

        if (data->z_values[(int)newY][(int)newX] == 0) {
            data->player[0]->pos[0]->x = newX;
            data->player[0]->pos[0]->y = newY;
        }
    }
    if (data->key_states[map_keycode(KEY_ANSI_A)])
        strafe(data, -1, move_speed);
    if (data->key_states[map_keycode(KEY_ANSI_D)])
        strafe(data, 1, move_speed);
    mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
}
