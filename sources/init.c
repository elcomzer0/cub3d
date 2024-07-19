/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:35 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/20 00:27:35 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

int ft_init(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);

    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    //mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 2, 1L<<0, key_hook_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_hook_release, data);
    cub_menu(data);
    mlx_hook(data->win, 17, 0, ft_destroy, data);
    mlx_loop(data->mlx);
    return (0);
}