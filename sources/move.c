/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:18 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/27 16:56:43 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int key_hook_press(int keycode, t_data *data)
{
    if (keycode == KEY_ESCAPE)
    {
        ft_destroy(data);
    }
    
    else if (keycode == KEY_LEFTARROW)
    {
        data->arrow_angle -= 0.35;
    }
    else if (keycode == KEY_RIGHTARROW)
    {
        data->arrow_angle += 0.35;   
    }
	//mlx_destroy_image(data->mlx, data->map_img);
    mlx_destroy_image(data->mlx, data->img);
    //data->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    map_test(data);
    cub_draw(data);
    //mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
    return (0);
}

int key_hook_release(int keycode, t_data *data)
{
    if (keycode == KEY_LEFTARROW)
    {
        data->arrow_angle -= 0.05;
    }
    else if (keycode == KEY_RIGHTARROW)
    {
        data->arrow_angle += 0.05;   
    }
    mlx_destroy_image(data->mlx, data->img);
    //mlx_destroy_image(data->mlx, data->map_img);
    //data->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    map_test(data);
    cub_draw(data);
    //mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
    return (0);
}