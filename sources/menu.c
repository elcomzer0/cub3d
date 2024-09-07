/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:22 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/07 18:46:40 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void display_angle(t_data *data)
{
    char angle_str[50];

    double_to_string(data->player->angle, angle_str);
    mlx_string_put(data->mlx, data->win, 10, 90, 0x00FFFFFF, angle_str);
}
void display_player_position(t_data *data)
{
    char pos_str[50];
    
    double_to_string_x(data->player->pos[0], pos_str);
    mlx_string_put(data->mlx, data->win, 10, 110, 0x00FFFFFF, pos_str);
    double_to_string_y(data->player->pos[1], pos_str);
    mlx_string_put(data->mlx, data->win, 10, 130, 0x00FFFFFF, pos_str);
}

void    cub_menu(t_data *data)
{
    mlx_string_put(data->mlx, data->win, 10, 10, 0x00FFFFFF, "CUB3D");
    mlx_string_put(data->mlx, data->win, 10, 30, 0x00FFFFFF, "Movement: WASD");
    mlx_string_put(data->mlx, data->win, 10, 50, 0x00FFFFFF, "Rotation: Arrows");
    mlx_string_put(data->mlx, data->win, 10, 70, 0x00FFFFFF, "Exit: ESC");
    display_angle(data);
    display_player_position(data);
}