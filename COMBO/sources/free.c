/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:37:43 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/11 14:11:54 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void free_player(t_data *data)
{
    if (data->player) {
    
        free(data->player);
    }
}

// void free_map_coord(t_data *data)
// {
//     if (data->map_coord) {
//         for (int i = 0; i < data->map_height; i++) {
//             free(data->map_coord[i]);
//         }
//         free(data->map_coord);
//     }
// }

int ft_clean(t_data *data)
{
    if (data->fl_cl)
        (free(data->fl_cl), data->fl_cl = NULL);
    if (data->raycast)
        (free(data->raycast), data->raycast = NULL);
    // if (data->color)
    // {
    //     free(data->color);
    //     data->color = NULL;
    //     return (0);
    // }
    if(data)
        (free(data), data = NULL);
    else
        return (ft_putstr_fd("Error: Free failed\n", 2), 1);
    return (0);
}

/*destroy*/
int	ft_destroy(t_data *data)
{
    int i = -1;
	while (i++, i < 5)
	{
		mlx_destroy_image(data->mlx,data->raycast->texture[i].tex_img);
		free(data->raycast->texture[i].path);
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	free_z_values(data);
	ft_free(data->file);
	free(data->file->text);
	free(data->file);
	free(data->player);
	ft_clean(data);
	exit (0);
}
