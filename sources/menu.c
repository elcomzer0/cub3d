/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AVP <AVP@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:22 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/31 15:58:14 by AVP              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void display_angle(t_data *data)
{
    char angle_str[50];

    float_to_string(data->arrow_angle, angle_str);
    mlx_string_put(data->mlx, data->win, 10, 90, 0x00FFFFFF, angle_str);
}

void    cub_menu(t_data *data)
{
    mlx_string_put(data->mlx, data->win, 10, 10, 0x00FFFFFF, "CUB3D");
    mlx_string_put(data->mlx, data->win, 10, 30, 0x00FFFFFF, "Movement: WASD");
    mlx_string_put(data->mlx, data->win, 10, 50, 0x00FFFFFF, "Rotation: Arrows");
    mlx_string_put(data->mlx, data->win, 10, 70, 0x00FFFFFF, "Exit: ESC");
    display_angle(data);
}