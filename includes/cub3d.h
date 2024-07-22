/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:46 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/22 22:53:42 by jorgonca         ###   ########.fr       */
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

# define HEIGHT 720
# define WIDTH  1280
# define MAP_SIZE 10
# define TILE_SIZE 50
# define FOV 90 // Field of view in degrees
# define NUM_RAYS WIDTH // Number of rays (one per screen column)

typedef struct s_data {
	float		x;
	float		y;
	float		z;
    float		arrow_angle;
	int			**z_values;
    int			*line_z;
    int		color;
	//int		map;
	int		fd;
    char    *addr;
    int     endian;
    int     line_length;
    int     bpp;
    void		*mlx;
    void		*win;
    void		*img;
    int			player_x;
    int			player_y;
    int map_offset_x;
    int map_offset_y;
    int map[MAP_SIZE][MAP_SIZE];
    void *map_img;
    char    *map_addr;
    //t_point		**points;
    //t_vector		**vector;
}				t_data;

typedef struct s_point {
	float			x;
	float			y;
}				t_point;

typedef struct s_vector {
	float			x;
	float			y;
}				t_vector;

/*main.c*/
int ft_clean(t_data *data);
int ft_destroy(t_data *data);
int key_hook_press(int keycode, t_data *data);
int key_hook_release(int keycode, t_data *data);
int create_trgb(int t, int r, int g, int b);
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
void draw_rectangle(t_data *data, int x, int y, int width, int height, int color);
void  draw_arrow(t_data *data, t_point center, int line_length, int triangle_size, float angle);
void    cub_draw(t_data *data);
void map_test(t_data *data);
void draw_map(t_data *data, int map[MAP_SIZE][MAP_SIZE], int offset_x, int offset_y);
void display_angle(t_data *data);
void    cub_menu(t_data *data);
int ft_init(t_data *data);

void my_map_pixel_put(t_data *data, int x, int y, int color);
void map_draw_rectangle(t_data *data, int x, int y, int width, int height, int color);
void   map_draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);
void draw_filled_rectangle(t_data *data, int x, int y, int width, int height, int color);
//void raycasting(t_data *data, int map[MAP_SIZE][MAP_SIZE], int map_offset_x, int map_offset_y);
//void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE], int map_offset_x, int map_offset_y);
//void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE]);
void raycasting_2D(t_data *data, int map[MAP_SIZE][MAP_SIZE], float arrow_angle);
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