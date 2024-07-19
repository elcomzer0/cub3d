/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:31 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/20 00:40:14 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"
void cub_draw(t_data *data);
void cub_menu(t_data *data);

/* int ft_clean(t_data *data)
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
} */

/*destroy*/
/* int	ft_destroy(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	ft_clean(data);
	free(data);
	exit (0);
} */

/*KEY HOOKS*/


/* int key_hook_press(int keycode, t_data *data)
{
    if (keycode == KEY_ESCAPE)
    {
        ft_destroy(data);
    }
    
    else if (keycode == KEY_LEFTARROW)
    {
        data->arrow_angle -= 0.05;
    }
    else if (keycode == KEY_RIGHTARROW)
    {
        data->arrow_angle += 0.05;   
    }
    mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
    return (0);
}

int key_hook_release(int keycode, t_data *data)
{
    if (keycode == KEY_LEFTARROW)
    {
        data->arrow_angle -= 0.05;
    }
    else if (keycode == KEY_RIGHTARROW)
    {
        data->arrow_angle += 0.05;   
    }
    mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    cub_menu(data);
    return (0);
} */

/*IMAGE*/

/* void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
} */

/*(TEST)MAP ELEMENTS*/

/* void    draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
    
} */

/* void    draw_square(t_data *data, int x, int y, int size, int color)
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
} */

/* void    draw_circle(t_data *data, int xc, int yc, int radius, int color)
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
} */

/* void draw_triangle(t_data *data, int x, int y, int size, int color)
{

   for (int i = 0; i < size; i++)
   {
        for (int j = 0; j <= i; j++)
        {
            my_mlx_pixel_put(data, x + j, y + i, color);
        }
    }
} */

/* void draw_hexagon(t_data *data, int xc, int yc, int size, int color)
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
} */

/* void    draw_gradient(t_data *data)
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
    
} */

/* void    draw_rainbow(t_data *data)
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
    
} */

/* t_point rotate_point(t_point p, t_point center, float angle)
{
    t_point rotated;
    float radians = angle * M_PI / 18;

    rotated.x = (p.x - center.x) * cos(radians) - (p.y - center.y) * sin(radians) + center.x;
    rotated.y = (p.x - center.x) * sin(radians) + (p.y - center.y) * cos(radians) + center.y;

    return (rotated);
} */

/* void rot_draw_triangle(t_data *data, t_point p1, t_point p2, t_point p3, float angle)
{
    // Calculate the middpoint of the hypotenuse
    t_point hypotenuse_mid = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    
    // Rotate the points around the hypotenuse midpoint
    t_point rp1 = rotate_point(p1, hypotenuse_mid, angle);
    t_point rp2 = rotate_point(p2, hypotenuse_mid, angle);
    t_point rp3 = rotate_point(p3, hypotenuse_mid, angle);
    
    // Draw the rotated triangle
    draw_line(data, rp1.x, rp1.y, rp2.x, rp2.y, 0x00FF0000);
    draw_line(data, rp2.x, rp2.y, rp3.x, rp3.y, 0x0000FF00);
    draw_line(data, rp3.x, rp3.y, rp1.x, rp1.y, 0x000000FF);

} */

/* void  draw_arrow(t_data *data, t_point center, int line_length, int triangle_size, float angle)
{
    //calculate the end point of the line
    t_point line_end = {center.x, center.y - line_length};
    t_point rotated_line_end = rotate_point(line_end, center, angle);

    //calculate the vertices of the triangle
    t_point triangle_tip = rotated_line_end;
    t_point triangle_left = {triangle_tip.x - triangle_size / 2, triangle_tip.y + triangle_size};
    t_point triangle_right = {triangle_tip.x + triangle_size / 2, triangle_tip.y + triangle_size};

    triangle_left = rotate_point(triangle_left, triangle_tip, angle);
    triangle_right = rotate_point(triangle_right, triangle_tip, angle);
    
    //draw the circle
    draw_circle(data, center.x, center.y, 5, 0x00FF0000);
    
    //draw the line
    draw_line(data, center.x, center.y, rotated_line_end.x, rotated_line_end.y, 0x00FF0000);

    //draw the triangle
    draw_line(data, triangle_tip.x, triangle_tip.y, triangle_left.x, triangle_left.y, 0x0000FF00);
    draw_line(data, triangle_tip.x, triangle_tip.y, triangle_right.x, triangle_right.y, 0x000000FF);
    draw_line(data, triangle_left.x, triangle_left.y, triangle_right.x, triangle_right.y, 0x00FF0000);

    //draw the field of view lines
    t_point fov_left_end = rotate_point(line_end, center, angle - 67.5);
    t_point fov_right_end = rotate_point(line_end, center, angle + 67.5);
    draw_line(data, center.x, center.y, fov_left_end.x, fov_left_end.y, 0x00FFFF00);
    draw_line(data, center.x, center.y, fov_right_end.x, fov_right_end.y, 0x00FFFF00);

    //draw diagonal line
    t_point diagonal_left_end  = rotate_point(line_end, center, angle - 45);
    t_point diagonal_right_end = rotate_point(line_end, center, angle + 45);
    draw_line(data, center.x, center.y, diagonal_left_end.x, diagonal_left_end.y, 0x0000FFFF);
    draw_line(data, center.x, center.y, diagonal_right_end.x, diagonal_right_end.y, 0x0000FFFF);
} */

/* void    cub_draw(t_data *data)
{
    //Define the vertices of the triangle
    //t_point p1 = {960, 540};
    //t_point p2 = {960, 640};
    //t_point p3 = {1060, 640};
    
       //Define arrow inputs
    t_point center = {960, 540};
    int line_length = 300;
    int triangle_size = 30;
   // data->arrow_angle = 180;
    
        //draw_gradient(data);
   // draw_rainbow(data);
    //draw_square(data, 1460, 540, 100, 0x00FF0000);
//    draw_circle(data, 960, 540, 300, 0x00FF7F00);
    draw_circle(data, 960, 540, 300, 0x248A8D8F);
    //draw_hexagon(data, 460, 540, 100, 0x000000FF);
    //draw_triangle(data, 960, 740, 100, 0x000000FF);
    //draw_line(data, 960, 540, 960, 440, 0x00FF0000);
    //rot_draw_triangle(data, p1, p2, p3, angle);
    draw_arrow(data, center, line_length, triangle_size, data->arrow_angle);
} */
/* void display_angle(t_data *data)
{
    char angle_str[50];

    float_to_string(data->arrow_angle, angle_str);
    mlx_string_put(data->mlx, data->win, 10, 90, 0x00FFFFFF, angle_str);
}

void    cub_menu(t_data *data)
{
    mlx_string_put(data->mlx, data->win, 10, 10, 0x00FFFFFF, "CUB3D");
    mlx_string_put(data->mlx, data->win, 10, 30, 0x00FFFFFF, "Movement: WASD");
    mlx_string_put(data->mlx, data->win, 10, 50, 0x00FFFFFF, "Rotation: Arrows");
    mlx_string_put(data->mlx, data->win, 10, 70, 0x00FFFFFF, "Exit: ESC");
    display_angle(data);
} */




/* int ft_init(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);

    cub_draw(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    //mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 2, 1L<<0, key_hook_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_hook_release, data);
    cub_menu(data);
    mlx_hook(data->win, 17, 0, ft_destroy, data);
    mlx_loop(data->mlx);
    return (0);
} */


/*FREE*/


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