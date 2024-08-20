/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:35 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/20 16:41:53 by jorgonca         ###   ########.fr       */
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

/* int rc_init(t_data *data)
{
    //printf("data->raycast->ray_dir[0]->x = %f\n", data->raycast->ray_dir[0]->x);
    data->raycast->ray_dir[0]->x = 0;
    data->raycast->ray_dir[0]->y = 0;
    data->raycast->step[0]->x = 0;
    data->raycast->step[0]->y = 0;
    data->raycast->side_dist[0]->x = 0;
    data->raycast->side_dist[0]->y = 0;
    data->raycast->delta_dist[0]->x = 0;
    data->raycast->delta_dist[0]->y = 0;
    data->raycast->plane[0]->x = 0;
    data->raycast->plane[0]->y = 0;
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
    //rc->time = 0;
    //rc->old_time = 0;
    return (0);
} */

/* int rc_init(t_data *data)
{
    //t_point **point;
    // Allocate memory for raycast structure

    t_point *point;
    t_rc *rc;

    rc = malloc(sizeof(t_rc));
    if (!rc)
        return (-1); // Handle allocation failure

    point = malloc(sizeof(t_point));
    if (!point)
        return (-1); // Handle allocation failure
    data->raycast = malloc(sizeof(t_rc));
    if (!data->raycast)
        return (-1); // Handle allocation failure

    // Allocate memory for each pointer in raycast
    data->raycast->ray_dir = malloc(sizeof(t_point));
    if (!data->raycast->ray_dir)
        return (-1); // Handle allocation failure
    data->raycast->step = malloc(sizeof(t_point));
    if (!data->raycast->step)
        return (-1); // Handle allocation failure
    data->raycast->side_dist = malloc(sizeof(t_point));
    if (!data->raycast->side_dist)
        return (-1); // Handle allocation failure
    data->raycast->delta_dist = malloc(sizeof(t_point));
    if (!data->raycast->delta_dist)
        return (-1); // Handle allocation failure
    data->raycast->plane = malloc(sizeof(t_point));
    if (!data->raycast->plane)
        return (-1); // Handle allocation failure

    if (!data->raycast->ray_dir || !data->raycast->step || !data->raycast->side_dist || !data->raycast->delta_dist || !data->raycast->plane)
        return (-1); // Handle allocation failure

    // Initialize values
  write(1, "segmentation fault\n", 19);
  (*data->raycast->ray_dir)->x = 0;
    (*data->raycast->ray_dir)->y = 0;
    (*data->raycast->step)->x = 0;
    (*data->raycast->step)->y = 0;
    (*data->raycast->side_dist)->x = 0;
    (*data->raycast->side_dist)->y = 0;
    (*data->raycast->delta_dist)->x = 0;
    (*data->raycast->delta_dist)->y = 0;
    (*data->raycast->plane)->x = 0;
    (*data->raycast->plane)->y = 0;
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

    return (0);
} */

int rc_init(t_data *data)
{
    // Allocate memory for raycast structure
    data->raycast = malloc(sizeof(t_rc));
    if (!data->raycast)
        return (-1); // Handle allocation failure

    // Allocate memory for each t_point structure in raycast
    data->raycast->ray_dir = malloc(sizeof(t_point *));
    if (!data->raycast->ray_dir)
        return (-1); // Handle allocation failure
    data->raycast->ray_dir[0] = malloc(sizeof(t_point));
    if (!data->raycast->ray_dir[0])
        return (-1); // Handle allocation failure

    data->raycast->step = malloc(sizeof(t_point *));
    if (!data->raycast->step)
        return (-1); // Handle allocation failure
    data->raycast->step[0] = malloc(sizeof(t_point));
    if (!data->raycast->step[0])
        return (-1); // Handle allocation failure

    data->raycast->side_dist = malloc(sizeof(t_point *));
    if (!data->raycast->side_dist)
        return (-1); // Handle allocation failure
    data->raycast->side_dist[0] = malloc(sizeof(t_point));
    if (!data->raycast->side_dist[0])
        return (-1); // Handle allocation failure

    data->raycast->delta_dist = malloc(sizeof(t_point *));
    if (!data->raycast->delta_dist)
        return (-1); // Handle allocation failure
    data->raycast->delta_dist[0] = malloc(sizeof(t_point));
    if (!data->raycast->delta_dist[0])
        return (-1); // Handle allocation failure

    data->raycast->plane = malloc(sizeof(t_point *));
    if (!data->raycast->plane)
        return (-1); // Handle allocation failure
    data->raycast->plane[0] = malloc(sizeof(t_point));
    if (!data->raycast->plane[0])
        return (-1); // Handle allocation failure

    // Initialize values
    data->raycast->ray_dir[0]->x = 0;
    data->raycast->ray_dir[0]->y = 0;
    data->raycast->step[0]->x = 0;
    data->raycast->step[0]->y = 0;
    data->raycast->side_dist[0]->x = 0;
    data->raycast->side_dist[0]->y = 0;
    data->raycast->delta_dist[0]->x = 0;
    data->raycast->delta_dist[0]->y = 0;
    data->raycast->plane[0]->x = 0;
    data->raycast->plane[0]->y = 0;
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
    write(1, "hello\n", 6);
    return (0);
}

/* int init_point(t_point ***point)
{
    *point = malloc(sizeof(t_point));
    if (!*point)
    {
        write(2, "Error: alloc point failed\n", 27);
        return (1);
    }
    return (0);
} */

int ft_init(t_data *data)
{

    //t_rc *rc;
    //t_color *color;
   // t_point **point;
    
    //rc = NULL;
    //color = NULL;
    //map_to_buf(data);
    //open_map(data, data->map_buf);
    /* if (init_point(&point) == 1)
        return (1); */
    if (init_color(&data->color) == 1)
        return (1);
    /* if (init_rc(&rc) == 1)
        return (1); */
    init_colors_test(data);
    if (rc_init(data) == -1)
        return (1);
    //rc_init(data);
    
    ft_info_read(data->map_name, data);
    
    //return (0);

    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
    //data->map_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    //data->map_addr = mlx_get_data_addr(data->map_img, &data->bpp, &data->line_length, &data->endian);

    //cub_draw(data);
    //map_test(data);
    //mlx_put_image_to_window(data->mlx, data->win, data->map_img, 0, 0);
    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    //mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 2, 1L<<0, key_hook_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_hook_release, data);

    cub_menu(data);
    
    mlx_hook(data->win, 17, 0, ft_destroy, data);
    mlx_loop(data->mlx);
    return (0);
}