/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:31 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/18 23:39:12 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"



/*IMAGE*/

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

/*(TEST)MAP ELEMENTS*/
void    draw_square(t_data *data, int x, int y, int size, int color)
{
    int i;
    int j;

    i = 0;
    //j = 0;

    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            my_mlx_pixel_put(data, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void    draw_circle(t_data *data, int xc, int yc, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put(data, xc + x, yc + y, color);
            }
        }
    }
}

void draw_triangle(t_data *data, int x, int y, int size, int color)
{

   for (int i = 0; i < size; i++)
   {
        for (int j = 0; j <= i; j++)
        {
            my_mlx_pixel_put(data, x + j, y + i, color);
        }
    }
}

void draw_hexagon(t_data *data, int xc, int yc, int size, int color)
{
    int y = -size;
    while (y <=  size)
    {
        int x = -size;
        while (x <= size)
        {
            if (abs(x) + abs(y) <= size)
            {
                my_mlx_pixel_put(data, xc + x, yc + y, color);
            }
            x++;
        }
        y++;
    }
}

void    draw_gradient(t_data *data)
{
    int y = 0;
    while (y < HEIGHT)
    {
        int x = 0;
        while (x < WIDTH)
        {
            int color = (x * 255 / WIDTH) << 16 | (y * 255 / HEIGHT) << 8;
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    
}

void    draw_rainbow(t_data *data)
{
    int colors[] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0x00FFFF00, 0x0000FFFF, 0x00FF00FF};
    int color_count = sizeof(colors) / sizeof(colors[0]);
    int stripe_height = HEIGHT / color_count;

    int y = 0;
    while (y < HEIGHT)
    {
        int color = colors[y / stripe_height];
        int x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
    
}

int ft_init(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
    //my_mlx_pixel_put(data, 10, 10, 0x00FF0000);
    //draw_gradient(data);
    draw_rainbow(data);
    draw_square(data, 1460, 540, 100, 0x00FF0000);
    draw_circle(data, 960, 540, 100, 0x0000FF00);
    draw_hexagon(data, 460, 540, 100, 0x000000FF);
    draw_triangle(data, 960, 740, 100, 0x000000FF);
    
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_loop(data->mlx);
    return (0);
}


/*FREE*/

int ft_clean(t_data *data)
{
    if(data)
    {
        free(data);
        data = NULL;
        return (0);
    }
    else
    {
        write(2, "Error: free failed\n", 20);
        return (1);
    }
    return (0);
}

int main(int ac, char **av)
{
    t_data *data;
    (void)av;
    (void)ac;
    
    data = (t_data *)calloc(1, sizeof(t_data));
    if (!data)
    {
        write(2, "Error: malloc failed\n", 20);
        free(data);
        data = NULL;
        return (1);
    }
    // if (ac != 2 || (strcmp(av[1] + strlen(av[1]) - 4, ".cub") != 0))   
    // {
    //     write(2, "Error: bad arguments\n", 20);
    //     ft_clean(data);
    //     return (1);
    // }
    // if (ac == 2)
    // {
    //     ft_init(data);
        
    // }
        ft_init(data);
    return (0);
}