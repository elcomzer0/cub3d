/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:35 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/13 13:48:46 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	rc_help(t_data *data)
{
	data->raycast->plane[0] = 0;
	data->raycast->plane[1] = 0;
	data->raycast->hit = 0;
	data->raycast->side = 0;
	data->raycast->map_x = 0;
	data->raycast->map_y = 0;
	data->raycast->draw_start = 0;
	data->raycast->draw_end = 0;
	data->raycast->line_height = 0;
	data->raycast->color = 0;
	data->raycast->perp_wall_dist = 0;
	data->raycast->camera_x = 0;
	data->raycast->wall_type = 0;
}

int	rc_init(t_data *data)
{
	int	i;

	i = -1;
	data->raycast = ft_calloc(1, sizeof(t_rc));
	if (!data->raycast)
		return (false);
	while (i++, i != KEY_COUNT)
		data->key_states[i] = 0;
	data->raycast->ray_dir[0] = 0;
	data->raycast->ray_dir[1] = 0;
	data->raycast->step[0] = 0;
	data->raycast->step[1] = 0;
	data->raycast->side_dist[0] = 0;
	data->raycast->side_dist[1] = 0;
	data->raycast->delta_dist[0] = 0;
	data->raycast->delta_dist[1] = 0;
	rc_help(data);
	init_textures(data);
	return (true);
}

void	init_xpm(t_data *data, int i, int j)
{
	const char	*text_path[5] = {
		data->file->text->no,
		data->file->text->so,
		data->file->text->ea,
		data->file->text->we
	};

	file_to_image(data, -1, j, text_path);
	data->raycast->texture[4].tex_img = \
		mlx_new_image(data->mlx, WIDTH, HEIGHT);
	i = -1;
	while (i++, i < 5)
	{
		data->raycast->texture[i].tex_addr = \
			mlx_get_data_addr(data->raycast->texture[i].tex_img,
				&data->raycast->texture[i].bpp,
				&data->raycast->texture[i].line_length,
				&data->raycast->texture[i].endian);
		if (!data->raycast->texture[i].tex_addr)
		{
			mlx_destroy_image(data->mlx, data->raycast->texture[i].tex_img);
			return ((ft_putstr_fd("Error:\nInvalid texture\n", 2)));
		}
	}
}

void	init_fl_cl(t_data *data)
{
	t_fl_cl	*fl_cl;

	fl_cl = (t_fl_cl *)malloc(sizeof(t_fl_cl));
	if (fl_cl == NULL)
		return ;
	data->fl_cl = fl_cl;
	if (!data->fl_cl)
		return (free(fl_cl), ft_putstr_fd("Error:\nMalloc failed\n", 2));
}

int	ft_init(t_data *data, int i)
{
	init_fl_cl(data);
	if (rc_init(data) == false)
		return (free(data->fl_cl), false);
	while (i++, i < data->map_height)
		fill_values(data, data->file->map[i]);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (ft_putstr_fd("Error:\nmlx Fail\n", 2), free(data->raycast),
			free(data->fl_cl), false);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img == NULL || data->win == NULL)
		return (ft_putstr_fd("Error:\nnmlx Fail\n", 2), ft_destroy(data));
	init_xpm(data, -1, -1);
	(ceiling_floor(data), mlx_loop_hook(data->mlx, &cub_draw, data));
	mlx_hook(data->win, 2, 1L << 0, key_hook_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_hook_release, data);
	mlx_loop_hook(data->mlx, key_loop, data);
	(mlx_hook(data->win, 17, 0, ft_destroy, data), mlx_loop(data->mlx));
	return (0);
}
