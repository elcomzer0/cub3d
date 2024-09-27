/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:37:43 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/25 14:33:01 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	free_player(t_data *data)
{
	if (data->player)
	{
		free(data->player);
	}
}

int	ft_clean(t_data *data)
{
	if (data->fl_cl != NULL)
		(free(data->fl_cl), data->fl_cl = NULL);
	if (data->raycast != NULL)
		(free(data->raycast), data->raycast = NULL);
	if (data != NULL)
		(free(data), data = NULL);
	else
		return (ft_putstr_fd("Error\nFree failed\n", 2), 1);
	return (0);
}

/*destroy*/
int	ft_destroy(t_data *data)
{
	int	i;

	i = -1;
	while (i++, i < 5)
	{
		if (data->raycast->texture[i].tex_img && data->mlx)
			mlx_destroy_image(data->mlx, data->raycast->texture[i].tex_img);
		if (data->raycast->texture[i].path)
			free(data->raycast->texture[i].path);
	}
	if (data->mlx && data->win)
		mlx_clear_window(data->mlx, data->win);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		(mlx_destroy_display(data->mlx), mlx_loop_end(data->mlx));
	(free(data->mlx), free_z_values(data), ft_free(data->file));
	(free(data->file->text), free(data->file));
	(free(data->player), ft_clean(data));
	exit (1);
}

void	free_z_values(t_data *data)
{
	int	i;

	i = -1;
	while (i++, i < data->file->line_hei)
	{
		free(data->z_values[i]);
	}
	free(data->z_values);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	(free(array), array = NULL);
}
