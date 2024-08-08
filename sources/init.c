/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:35 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/09 00:23:22 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"


void init_colors_test(t_data *data)
{
    data->color->red = create_trgb(0, 235, 64, 52);
    data->color->yellow = create_trgb(0, 235, 229, 52);
    data->color->green = create_trgb(0, 67, 235, 52);
    data->color->blue = create_trgb(0, 52, 85, 235);
    data->color->magenta = create_trgb(0, 235, 10, 210);
    data->color->grey = create_trgb(0, 171, 167, 167);
}
//void init_textures(t_data *data)

//void init_math(t_data *data)
int init_rc(t_rc **rc)
{
    *rc = calloc(1, sizeof(t_rc));
    if (!*rc)
    {
        write(2, "Error: alloc rc failed\n", 24);
        return (1);
    }

    return (0);
    
}
int init_color(t_color **color)
{
    *color = calloc(1, sizeof(t_color));
    if (!*color)
    {
        write(2, "Error: alloc color failed\n", 27);
        return (1);
    }
    return (0);
}

int ft_init(t_data *data)
{
    t_rc *rc;
    //t_color *color;
    
    rc = NULL;
    //color = NULL;
    //map_to_buf(data);
    //open_map(data, data->map_buf);
    if (init_color(&data->color) == 1)
        return (1);
    if (init_rc(&rc) == 1)
        return (1);
    init_colors_test(data);
    
    ft_info_read(data->map_name, data);
    
    
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
    //data->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    //data->map_addr = mlx_get_data_addr(data->map_img, &data->bpp, &data->line_length, &data->endian);

    //map_test(data);
    cub_draw(data);
    //mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    //mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 2, 1L<<0, key_hook_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_hook_release, data);

    cub_menu(data);
    
    mlx_hook(data->win, 17, 0, ft_destroy, data);
    mlx_loop(data->mlx);
    return (0);
}