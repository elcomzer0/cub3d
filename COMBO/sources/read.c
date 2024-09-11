/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:11 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/11 13:08:01 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

void N(t_data *data)
{
	data->player->angle = 270;
	data->player->dx = 0;
	data->player->dy = -1;
	data->raycast->plane[0] = 0.66;
	data->raycast->plane[1] = 0; 
}

void	S(t_data *data)
{
	data->player->angle = 90;
	data->player->dx = 0;
	data->player->dy = 1;
	data->raycast->plane[0] = -0.66;
	data->raycast->plane[1] = 0;
}

void W(t_data *data)
{
	data->player->angle = 180;
	data->player->dx = -1;
	data->player->dy = 0;
	data->raycast->plane[0] = 0; 
	data->raycast->plane[1] = -0.66;
}

void E(t_data *data)
{
	data->player->angle = 0;
	data->player->dx = 1;
	data->player->dy = 0;
	data->raycast->plane[0] = 0;
	data->raycast->plane[1] = 0.66;
}

void fill_values(t_data *data, char *line)
{
    int i;

    i = -1;
    while (i++, i < data->map_width)
    {
		if (line[i] == 'N')
			N(data);
		else if (line[i] == 'S')
			S(data);
		else if (line[i] == 'W')
			W(data);
		else if (line[i] == 'E')
			E(data);
    }
}
