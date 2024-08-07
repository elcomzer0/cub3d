/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:18 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/06 19:50:24 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int key_hook_press(int keycode, t_data *data)
{
    float move_speed = 0.35;
    float rotation_speed = 0.35;

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
}

int key_hook_release(int keycode, t_data *data)
{
    float move_speed = 0.1;
    float rotation_speed = 0.35;

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
}