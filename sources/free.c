/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:37:43 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/20 19:42:33 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int ft_clean(t_data *data)
{
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
    mlx_destroy_image(data->mlx, data->map_img);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	ft_clean(data);
	free(data);
	exit (0);
}