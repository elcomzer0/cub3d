/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:37:43 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/07 21:12:32 by jorgonca         ###   ########.fr       */
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
    if (data->fl_cl)
    {
        free(data->fl_cl);
        data->fl_cl = NULL;
    }
    if (data->raycast)
    {
        
        free(data->raycast);
        data->raycast = NULL;
    }
    // if (data->color)
    // {
    //     free(data->color);
    //     data->color = NULL;
    //     return (0);
    // }
    if (data->z_values)
    {
        //free(data->z_values);
        free_z_values(data);
        data->z_values = NULL;
        
    }
    if (data->player)
    {
        free_player(data);
        data->player = NULL;
        
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
    int i = 0;
      while (i <= 4)
      {
        mlx_destroy_image(data->mlx,data->raycast->texture[i].tex_img);
        free(data->raycast->texture[i].path);
       // free(data->raycast->texture[i].tex_addr);
          //free(data->raycast->texture[i].tex_img);
        i++;
      }
  //  mlx_destroy_image(data->mlx, data->map_img);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	ft_clean(data);
	//free(data);
	exit (0);
}