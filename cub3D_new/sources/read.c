/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:11 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/27 19:21:26 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	we(t_data *data)
{
	data->player->angle = 270;
	data->player->dx = 0;
	data->player->dy = -1;
	data->raycast->plane[0] = 0.66;
	data->raycast->plane[1] = 0;
}

void	ea(t_data *data)
{
	data->player->angle = 90;
	data->player->dx = 0;
	data->player->dy = 1;
	data->raycast->plane[0] = -0.66;
	data->raycast->plane[1] = 0;
}

void	no(t_data *data)
{
	data->player->angle = 180;
	data->player->dx = -1;
	data->player->dy = 0;
	data->raycast->plane[0] = 0;
	data->raycast->plane[1] = -0.66;
}

void	so(t_data *data)
{
	data->player->angle = 0;
	data->player->dx = 1;
	data->player->dy = 0;
	data->raycast->plane[0] = 0;
	data->raycast->plane[1] = 0.66;
}

void	fill_values(t_data *data, char *line)
{
	int	i;

	i = -1;
	while (i++, i < data->map_width)
	{
		if (line[i] == 'N')
			no(data);
		else if (line[i] == 'S')
			so(data);
		else if (line[i] == 'W')
			we(data);
		else if (line[i] == 'E')
			ea(data);
	}
}
