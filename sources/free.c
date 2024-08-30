/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:37:43 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/28 17:09:25 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"


void free_z_values(t_data *data)
{
    if (data->z_values) {
        for (int i = 0; i < data->map_height; i++) {
            free(data->z_values[i]);
        }
        free(data->z_values);
    }
}

void free_player(t_data *data)
{
    if (data->player) {
        if (data->player[0]) {
            if (data->player[0]->pos) {
                if (data->player[0]->pos[0]) {
                    free(data->player[0]->pos[0]);
                }
                free(data->player[0]->pos);
            }
            free(data->player[0]);
        }
        free(data->player);
    }
}

void free_map_coord(t_data *data)
{
    if (data->map_coord) {
        for (int i = 0; i < data->map_height; i++) {
            free(data->map_coord[i]);
        }
        free(data->map_coord);
    }
}

int ft_clean(t_data *data)
{
    if (data->raycast)
    {
        free(data->raycast->ray_dir);
        free(data->raycast->step);
        free(data->raycast->side_dist);
        free(data->raycast->delta_dist);
        free(data->raycast->plane);
        free(data->raycast);
        data->raycast = NULL;
        return (0);
    }
    if (data->color)
    {
        free(data->color);
        data->color = NULL;
        return (0);
    }
    if (data->z_values)
    {
        //free(data->z_values);
        free_z_values(data);
        data->z_values = NULL;
        return (0);
    }
    if (data->player)
    {
        free_player(data);
        data->player = NULL;
        return (0);
    }
/*     if (data->map_coord)
    {
        free_map_coord(data);
        data->map_coord = NULL;
        return (0);
    } */
    if(data)
    {
        free(data);
        data = NULL;
        return (0);
    }
    else
    {
        write(2, "Error: free failed\n", 20);
        return (1);
    }
    return (0);
}

/*destroy*/
int	ft_destroy(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
  //  mlx_destroy_image(data->mlx, data->map_img);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	ft_clean(data);
	free(data);
	exit (0);
}