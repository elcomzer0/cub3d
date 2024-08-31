/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:18 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/31 13:27:05 by jorgonca         ###   ########.fr       */
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
/* int key_hook_press(int keycode, t_data *data)
{
    double move_speed = 0.35;
    double rotation_speed = 0.35;

    if (keycode == KEY_ESCAPE)
    {
        ft_destroy(data);
    }
    else if (keycode == KEY_LEFTARROW)
    {
        data->player[0]->angle -= rotation_speed;
    }
    else if (keycode == KEY_RIGHTARROW)
    {
        data->player[0]->angle += rotation_speed;
    }
    else if (keycode == KEY_ANSI_W)
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle) * move_speed;
    }
    else if (keycode == KEY_ANSI_S)
    {
        data->player[0]->pos[0]->x -= cos(data->player[0]->angle) * move_speed;
        data->player[0]->pos[0]->y -= sin(data->player[0]->angle) * move_speed;
    }
    else if (keycode == KEY_ANSI_A)
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle - M_PI/2) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle - M_PI/2) * move_speed;
    }
    else if (keycode == KEY_ANSI_D)
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle + M_PI/2) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle + M_PI/2) * move_speed;
    }
	//mlx_destroy_image(data->mlx, data->map_img);
    mlx_destroy_image(data->mlx, data->img);
    //data->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    cub_draw(data);
    //mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
    return (0);
} */

int key_hook_press(int keycode, t_data *data)
{
    int mapped_key = map_keycode(keycode);
    if (mapped_key >= 0 && mapped_key < KEY_COUNT)
        data->key_states[mapped_key] = 1;
    if (keycode == KEY_ESCAPE)
    {
        ft_destroy(data);
    }
    /* if(keycode < KEY_COUNT)
        data->key_states[keycode] = 1; */
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
    double move_speed = 0.5;
    double rotation_speed = 0.5;

    if (data->key_states[map_keycode(KEY_LEFTARROW)])
    {
        data->player[0]->angle -= rotation_speed;
        data->player[0]->pos[0]->x += cos(data->player[0]->angle) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle) * move_speed;
    }
    if (data->key_states[map_keycode(KEY_RIGHTARROW)])
    {
        data->player[0]->angle += rotation_speed;
        data->player[0]->pos[0]->x += cos(data->player[0]->angle);
        data->player[0]->pos[0]->y += sin(data->player[0]->angle);
    }
    if (data->key_states[map_keycode(KEY_ANSI_W)])
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle) * move_speed;
    }
    if (data->key_states[map_keycode(KEY_ANSI_S)])
    {
        data->player[0]->pos[0]->x -= cos(data->player[0]->angle) * move_speed;
        data->player[0]->pos[0]->y -= sin(data->player[0]->angle) * move_speed;
    }
    if (data->key_states[map_keycode(KEY_ANSI_A)])
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle - M_PI/2) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle - M_PI/2) * move_speed;
    }
    if (data->key_states[map_keycode(KEY_ANSI_D)])
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle + M_PI/2) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle + M_PI/2) * move_speed;
    }

    mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
}

/* int key_hook_release(int keycode, t_data *data)
{
    double move_speed = 0.1;
    double rotation_speed = 0.35;

    if (keycode == KEY_LEFTARROW)
    {
        data->player[0]->angle -= rotation_speed;
    }
    else if (keycode == KEY_RIGHTARROW)
    {
        data->player[0]->angle += rotation_speed;
    }
    else if (keycode == KEY_ANSI_W)
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle) * move_speed;
    }
    else if (keycode == KEY_ANSI_S)
    {
        data->player[0]->pos[0]->x -= cos(data->player[0]->angle) * move_speed;
        data->player[0]->pos[0]->y -= sin(data->player[0]->angle) * move_speed;
    }
    else if (keycode == KEY_ANSI_A)
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle - M_PI/2) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle - M_PI/2) * move_speed;
    }
    else if (keycode == KEY_ANSI_D)
    {
        data->player[0]->pos[0]->x += cos(data->player[0]->angle + M_PI/2) * move_speed;
        data->player[0]->pos[0]->y += sin(data->player[0]->angle + M_PI/2) * move_speed;
    }
    mlx_destroy_image(data->mlx, data->img);
    //mlx_destroy_image(data->mlx, data->map_img);
    //data->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    cub_draw(data);
    //mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
    return (0);
} */