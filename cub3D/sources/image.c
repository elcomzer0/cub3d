/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:43 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/12 15:38:38 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	my_xpm_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->raycast->texture[4].tex_addr
		+ (y * data->raycast->texture[4].line_length + x
			* (data->raycast->texture[4].bpp / 8));
	*(unsigned int *)dst = color;
}

void	file_to_image(t_data *data, int i, int j, const char *text_path[5])
{
	while (i++, i < 4)
	{
		data->raycast->texture[i].path = ft_strdup(text_path[i]);
		if (!data->raycast->texture[i].path)
			return (ft_putstr_fd("Error:\nMalloc\n", 2));
		data->raycast->texture[i].tex_img = \
			mlx_xpm_file_to_image(data->mlx, data->raycast->texture[i].path,
				&data->raycast->texture[i].width,
				&data->raycast->texture[i].height);
		if (!data->raycast->texture[i].tex_img)
		{
			j = -1;
			while (j++, j < i)
				mlx_destroy_image(data->mlx,
					data->raycast->texture[j].tex_img);
			return ((ft_putstr_fd("Error:\nInvalid texture\n", 2)));
		}
	}
}

void	init_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->raycast->texture[i] = (t_tex)
		{
			.path = NULL,
			.tex_img = NULL,
			.tex_addr = NULL,
			.width = 0,
			.height = 0,
			.bpp = 0,
			.line_length = 0,
			.endian = 0
		};
		i++;
	}
}

int	init_rc(t_rc **rc)
{
	t_rc	*raycast;

	raycast = (t_rc *)malloc(sizeof(t_rc));
	if (raycast == NULL)
		return (ft_putstr_fd("Error:\nMalloc failed\n", 2), 1);
	if (!*rc)
		return (ft_putstr_fd("Error:\nMalloc failed\n", 2), 1);
	return (0);
}

void	free_raycast(t_rc *raycast)
{
	if (raycast)
		free(raycast);
}
