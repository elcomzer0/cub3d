/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:35 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/09 14:37:29 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

int init_rc(t_rc **rc)
{
    t_rc *raycast;
	
	raycast = (t_rc *)malloc(sizeof(t_rc));
	if (raycast == NULL)
    if (!*rc)
        return (ft_putstr_fd("Error: Malloc failed\n", 2), 1);
    return (0);
    
}

void free_raycast(t_rc *raycast)
{
    if (raycast)
    {
        free(raycast);
    }
}

void init_textures(t_data *data)
{
    int i = 0;
    while (i < 5) {
        data->raycast->texture[i] = (t_tex){
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


int rc_init(t_data *data) 
{
	int i = -1;
	
	data->raycast = malloc(sizeof(t_rc));
	if (!data->raycast) return false;
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
	init_textures(data);
	return (true);
}

int key_loop(t_data *data)
{
    handle_movement(data);
    return (0);
}

void init_xpm(t_data *data)
{
    int i;
     const char *texture_paths[5] = {
		data->file->text->no,
		data->file->text->so,
	    data->file->text->ea,
		data->file->text->we
    };
    i = 0;
    while(i < 4)
    {
        data->raycast->texture[i].path = strdup(texture_paths[i]);
        if (!data->raycast->texture[i].path)
            return (ft_putstr_fd("Error: Memory allocation failed\n", 2));
        data->raycast->texture[i].tex_img = mlx_xpm_file_to_image(data->mlx, data->raycast->texture[i].path, &data->raycast->texture[i].width, &data->raycast->texture[i].height);
        if (!data->raycast->texture[i].tex_img)
        {
			ft_putstr_fd("Error: Failed to load image at path: ", 2);
            for (int j = 0; j < i; j++) {
                mlx_destroy_image(data->mlx, data->raycast->texture[j].tex_img);
            }
            return;
        }
        i++;
    }
    data->raycast->texture[4].tex_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    for (i = 0; i < 5; i++) {
        data->raycast->texture[i].tex_addr = mlx_get_data_addr(data->raycast->texture[i].tex_img,
            &data->raycast->texture[i].bpp, &data->raycast->texture[i].line_length, &data->raycast->texture[i].endian);
        if (!data->raycast->texture[i].tex_addr) {
            ft_putstr_fd("Error: Failed to get data address for texture: ", 2);
            mlx_destroy_image(data->mlx, data->raycast->texture[i].tex_img); 
        }
    }
}


void init_stars(t_data *data, int num_stars)
{
    for (int i = 0; i < num_stars; i++)
    {
        data->star_x[i] = rand() % WIDTH;
        data->star_y[i] = rand() % (HEIGHT / 2); // Top third of the screen
    }
}

void init_fl_cl(t_data *data)
{
	t_fl_cl	*fl_cl;

    fl_cl = (t_fl_cl *)malloc(sizeof(t_fl_cl));
	if (fl_cl == NULL)
		return ;
	data->fl_cl = fl_cl;
    if (!data->fl_cl)
    {
        write(2, "erroor: alloc fl_cl failed\n", 27);
        return ;
    }
}

int ft_init(t_data *data)
{

    init_fl_cl(data);
	if (rc_init(data) == false)
		return (false);
	int i = -1;
	while (i++, i < data->map_height)
    	fill_values(data, data->file->map[i]);

    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    init_xpm(data);
    ceiling_floor(data);
    mlx_loop_hook(data->mlx, &cub_draw, data);
    mlx_hook(data->win, 2, 1L<<0, key_hook_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_hook_release, data);
    mlx_loop_hook(data->mlx, key_loop, data);      
    cub_menu(data);
    mlx_hook(data->win, 17, 0, ft_destroy, data);
    mlx_loop(data->mlx);
    return (0);
}
