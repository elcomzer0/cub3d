/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:35 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/21 00:42:21 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

int ft_init(t_data *data)
{
    // t_point center;
    
    // data->player_x = 1;
    // data->player_y = 1;
    
    // center = (t_point){data->map_offset_x + data->player_x * TILE_SIZE + TILE_SIZE / 2, data->map_offset_y + data->player_y * TILE_SIZE + TILE_SIZE / 2};

    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
    //data->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    //data->map_addr = mlx_get_data_addr(data->map_img, &data->bpp, &data->line_length, &data->endian);

    map_test(data);
    cub_draw(data);
    //mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    //mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 2, 1L<<0, key_hook_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_hook_release, data);

    cub_menu(data);
    
    mlx_hook(data->win, 17, 0, ft_destroy, data);
    mlx_loop(data->mlx);
    return (0);
}