/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:35 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/07 21:03:31 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"


// void init_colors_test(t_data *data)
// {
//     data->color.red = create_trgb(0, 235, 64, 52);
//     data->color.yellow = create_trgb(0, 235, 229, 52);
//     data->color.green = create_trgb(0, 67, 235, 52);
//     data->color.blue = create_trgb(0, 52, 85, 235);
//     data->color.magenta = create_trgb(0, 235, 10, 210);
//     data->color.grey = create_trgb(0, 171, 167, 167);
// }

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
// int init_color(t_color **color)
// {
//     *color = calloc(1, sizeof(t_color));
//     if (!*color)
//     {
//         write(2, "Error: alloc color failed\n", 27);
//         free(*color);
//         return (1);
//     }
//     return (0);
// }




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

        // Print the texture information for the current index (i)
        // printf("Texture %d: path: %p, tex_img: %p, tex_addr %p, width %d, height %d, bpp %d, line_length %d, endian %d\n", 
        //        i,
        //        data->raycast->texture[i].path, 
        //        data->raycast->texture[i].tex_img, 
        //        data->raycast->texture[i].tex_addr, 
        //        data->raycast->texture[i].width, 
        //        data->raycast->texture[i].height, 
        //        data->raycast->texture[i].bpp, 
        //        data->raycast->texture[i].line_length, 
        //        data->raycast->texture[i].endian);

        i++;
    }
}


int rc_init(t_data *data) {
    data->raycast = malloc(sizeof(t_rc));
    if (!data->raycast) return -1; // Handle allocation failure

    // Initialize values
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

    write(1, "hello\n", 6);

    return 0;
}


int key_loop(t_data *data)
{
    //mlx_loop_hook(data->mlx, key_loop, data);
    handle_movement(data);
    return (0);
}





void init_xpm(t_data *data)
{
    int i;
     const char *texture_paths[5] = {
        "textures/pipes.xpm",
        "textures/console.xpm", 
        "textures/supports_space.xpm", 
        "textures/wall_space.xpm"  
    };
    //textures from the file
    //int i;
    //const char *texture_paths[5] = {
//    data->file->text->no,
    //    data->file->text->so,
    //    data->file->text->ea;
    //    data->file->text->we;

    

    i = 0;
    while(i < 4)
    {
    //      data->raycast->texture[i].path = malloc(strlen(texture_paths[i] + 1)); // +1 for null terminator
    //     if (!data->raycast->texture[i].path)
    //     {
    //         // Handle malloc error
    //         fprintf(stderr, "Error: Memory allocation failed\n");
    //         // Free previously allocated resources if any and exit
    //         return; 
    //     }
    //    //strcpy(data->raycast->texture[i].path, texture_paths[i]);
    //     strncpy(data->raycast->texture[i].path, texture_paths[i], strlen(texture_paths[i]));
        data->raycast->texture[i].path = strdup(texture_paths[i]);
        if (!data->raycast->texture[i].path)
        {
            // Handle malloc error
            fprintf(stderr, "Error: Memory allocation failed\n");
            
            // Free previously allocated resources if any and exit
            return;
        }
        data->raycast->texture[i].tex_img = mlx_xpm_file_to_image(data->mlx, data->raycast->texture[i].path, &data->raycast->texture[i].width, &data->raycast->texture[i].height);
        if (!data->raycast->texture[i].tex_img)
        {
            fprintf(stderr, "Error: Failed to load image at path: %s\n", data->raycast->texture[i].path);
            // Handle error: Free previously loaded textures and exit or use a default texture
            for (int j = 0; j < i; j++) {
                mlx_destroy_image(data->mlx, data->raycast->texture[j].tex_img);
            }
            return; // Exit the function after error handling
        }
        i++;
    }
    
    data->raycast->texture[4].tex_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    for (i = 0; i < 5; i++) {
        data->raycast->texture[i].tex_addr = mlx_get_data_addr(data->raycast->texture[i].tex_img,
            &data->raycast->texture[i].bpp, &data->raycast->texture[i].line_length, &data->raycast->texture[i].endian);
        if (!data->raycast->texture[i].tex_addr) {
            fprintf(stderr, "Error: Failed to get data address for texture: %s\n", data->raycast->texture[i].path);
            // Handle error: Free loaded image and potentially exit
            mlx_destroy_image(data->mlx, data->raycast->texture[i].tex_img); 
            // Additional error handling as needed
        }
        // printf("Texture %d: path: %s, tex_img: %p, tex_addr %p, width %d, height %d, bpp %d, line_length %d, endian %d\n", 
        //        i,
        //        data->raycast->texture[i].path, 
        //        data->raycast->texture[i].tex_img, 
        //        data->raycast->texture[i].tex_addr, 
        //        data->raycast->texture[i].width, 
        //        data->raycast->texture[i].height, 
        //        data->raycast->texture[i].bpp, 
        //        data->raycast->texture[i].line_length, 
        //        data->raycast->texture[i].endian);
    }
   // printf("addr: %p\n", data->raycast->texture[0].tex_addr);
    //
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
    data->fl_cl = malloc(sizeof(t_fl_cl));
    if (!data->fl_cl)
    {
        write(2, "erroor: alloc fl_cl failed\n", 27);
        return ;
    }
}

int ft_init(t_data *data)
{

    init_fl_cl(data);
    // if (init_color(&data->color) == 1)
    //     return (1);

    //init_colors_test(data);
    if (rc_init(data) == -1)
        return (1);
    //init_stars(data, 100);
    
    ft_info_read(data->map_name, data);
    

    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    init_xpm(data);
   // data->old_time = get_time();
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