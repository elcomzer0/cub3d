/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:46 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/20 00:23:56 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <endian.h>
# include <mlx.h>

# define HEIGHT 1080
# define WIDTH 1920

typedef struct s_data {
	float		x;
	float		y;
	float		z;
    float		arrow_angle;
	int			**z_values;
    int			*line_z;
    int		color;
	int		map;
	int		fd;
    char    *addr;
    int     endian;
    int     line_length;
    int     bpp;
    void		*mlx;
    void		*win;
    void		*img;    
}				t_data;

typedef struct s_point {
	float			x;
	float			y;
}				t_point;

/*main.c*/
int ft_clean(t_data *data);
int ft_destroy(t_data *data);
int key_hook_press(int keycode, t_data *data);
int key_hook_release(int keycode, t_data *data);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);
void    draw_square(t_data *data, int x, int y, int size, int color);
void    draw_circle(t_data *data, int xc, int yc, int radius, int color);
void draw_triangle(t_data *data, int x, int y, int size, int color);
void draw_hexagon(t_data *data, int xc, int yc, int size, int color);
void    draw_gradient(t_data *data);
void    draw_rainbow(t_data *data);
t_point rotate_point(t_point p, t_point center, float angle);
void rot_draw_triangle(t_data *data, t_point p1, t_point p2, t_point p3, float angle);
void  draw_arrow(t_data *data, t_point center, int line_length, int triangle_size, float angle);
void    cub_draw(t_data *data);
void display_angle(t_data *data);
void    cub_menu(t_data *data);
int ft_init(t_data *data);


/*utils.c*/
void float_to_string(float value, char *buffer);


# define KEY_ANSI_A			0X61
# define KEY_ANSI_Q			0X71
# define KEY_ESCAPE			0xff1b
# define KEY_LEFTARROW		0XFF51
# define KEY_RIGHTARROW		0XFF53
# define KEY_DOWNARROW		0XFF54
# define KEY_UPARROW		0XFF52


#endif