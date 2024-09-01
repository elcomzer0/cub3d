/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:18 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/01 20:57:08 by jorgonca         ###   ########.fr       */
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

void handle_movement(t_data *data)
{
    double move_speed =  0.025; // data->move_speed;
    double rotation_speed = 0.02; // data->rotation_speed;

      // Rotation
       if (data->key_states[map_keycode(KEY_LEFTARROW)]) {
        // Rotate left
        double oldDirX = data->player[0]->dx;
        data->player[0]->dx = oldDirX * cos(rotation_speed) - data->player[0]->dy * sin(rotation_speed);
        data->player[0]->dy = oldDirX * sin(rotation_speed) + data->player[0]->dy * cos(rotation_speed);

        double oldPlaneX = data->raycast->plane[0]->x;
        data->raycast->plane[0]->x = oldPlaneX * cos(rotation_speed) - data->raycast->plane[0]->y * sin(rotation_speed);
        data->raycast->plane[0]->y = oldPlaneX * sin(rotation_speed) + data->raycast->plane[0]->y * cos(rotation_speed);
    }
    if (data->key_states[map_keycode(KEY_RIGHTARROW)]) {
        // Rotate right
        double oldDirX = data->player[0]->dx;
        data->player[0]->dx = oldDirX * cos(-rotation_speed) - data->player[0]->dy * sin(-rotation_speed);
        data->player[0]->dy = oldDirX * sin(-rotation_speed) + data->player[0]->dy * cos(-rotation_speed);

        double oldPlaneX = data->raycast->plane[0]->x;
        data->raycast->plane[0]->x = oldPlaneX * cos(-rotation_speed) - data->raycast->plane[0]->y * sin(-rotation_speed);
        data->raycast->plane[0]->y = oldPlaneX * sin(-rotation_speed) + data->raycast->plane[0]->y * cos(-rotation_speed);
    }

    // Movement with Collision Detection
/*     if (data->key_states[map_keycode(KEY_ANSI_W)]) {
        double new_x = data->player[0]->pos[0]->x + cos(data->player[0]->angle) * move_speed;
        double new_y = data->player[0]->pos[0]->y + sin(data->player[0]->angle) * move_speed;

        if (data->z_values[(int)new_y][(int)new_x] == 0) {
            data->player[0]->pos[0]->x = new_x;
            data->player[0]->pos[0]->y = new_y;
        }
    }
    if (data->key_states[map_keycode(KEY_ANSI_S)]) {
        double new_x = data->player[0]->pos[0]->x - cos(data->player[0]->angle) * move_speed;
        double new_y = data->player[0]->pos[0]->y - sin(data->player[0]->angle) * move_speed;

        if (data->z_values[(int)new_y][(int)new_x] == 0) {
            data->player[0]->pos[0]->x = new_x;
            data->player[0]->pos[0]->y = new_y;
        }
    } */

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
if (data->key_states[map_keycode(KEY_ANSI_A)]) { // Strafe Left (A key)
    double newX = data->player[0]->pos[0]->x - move_speed; // Move left along X-axis
    double newY = data->player[0]->pos[0]->y; // Y-coordinate remains unchanged

    if (data->z_values[(int)newY][(int)newX] == 0) {
        data->player[0]->pos[0]->x = newX;
        // data->player[0]->pos[0]->y = newY;  // No need to update Y
    }
}

if (data->key_states[map_keycode(KEY_ANSI_D)]) { // Strafe Right (D key)
    double newX = data->player[0]->pos[0]->x + move_speed; // Move right along X-axis
    double newY = data->player[0]->pos[0]->y; // Y-coordinate remains unchanged

    if (data->z_values[(int)newY][(int)newX] == 0) {
        data->player[0]->pos[0]->x = newX;
        // data->player[0]->pos[0]->y = newY;  // No need to update Y
    }
}


    mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
}
