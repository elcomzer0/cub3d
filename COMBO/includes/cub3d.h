/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:46 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/11 16:21:55 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <endian.h>
# include <mlx.h>
# include <float.h>
# include <sys/time.h>
# include <time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

# define HEIGHT 720
# define WIDTH  1024
# define TEXTURE_SIZE 64
# define MAP_SIZE 10
# define TILE_SIZE 50
# define FOV 90 // Field of view in degrees
# define NUM_RAYS WIDTH // Number of rays (one per screen column)
# define NORTH_FOV 0
# define EAST_FOV 90
# define SOUTH_FOV 180
# define WEST_FOV 270
# define COLOR_RED 1
# define COLOR_GREEN 2
# define COLOR_BLUE 3
# define COLOR_MAGENTA 4
# define COLOR_YELLOW 5
# define EA_LT_SHADER 0.011
# define EA_DK_SHADER 0.01
# define NO_LT_SHADER 0.031
# define NO_DK_SHADER 0.04
#define EPSILON 1e-6
#define KEY_COUNT 256
# define ROT_SPEED 0.2
# define MOVE_SPEED 0.225


typedef struct s_text
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*f;
	char			*c;
	char			**colorf;
	char			**colorc;
	int				fr;
	int				fg;
	int				fb;
	int				cr;
	int				cg;
	int				cb;

}				t_text;

typedef struct s_file
{
	char			**texture;
	char			**map;
	char			**file;
	char			player_direction;
	int				line_len;
	int				line_hei;
	int				pos[2];
	int				p_flag;
	int				i;
	t_text			*text;
}				t_file;

typedef struct s_player {
    double          pos[2]; //-> you need this
    double			dx;
    double			dy;
    double			angle;
}				t_player;

typedef struct s_fl_cl {
	double			ray_dy[2];
	double			ray_dx[2];
	double			pos_z;
	double			row_distance;
	double			floor_step[2];
	double			floor[2];
	double			shading_factor;
	int				cell[2];
	int				tex[2];
	int				floor_tex;
	int				ceiling_tex;
	int				color;
} t_fl_cl;

typedef struct s_data {
	double			x;
	double			y;
	double			z;
	double			arrow_angle;
	int				**z_values;
	int				*line_z;
	int				map_height;
	int				map_width;
	char			*map_name;
	char			**map_buf;
	int				current_line;
	int				fd;
	char			*addr;
	int				endian;
	int				line_length;
	int				bpp;
	void			*mlx;
	void			*win;
	void			*img;
	int 			map_offset_x;
	int 			map_offset_y;
	int				map[MAP_SIZE][MAP_SIZE];
	void			*map_img;
	char    		*map_addr;
	t_player		*player;
	struct s_rc		*raycast;
	struct s_point	**map_coord;
	t_fl_cl			*fl_cl;
	double			start_angle;
	double			time;
	double			old_time;
	double			frame_time;
	double			fps;
	double			rotation_speed;
	double			move_speed;
	int				key_states[KEY_COUNT];
	int				player_x;
	int				player_y;
	int				star_x[100];
	int				star_y[100];
	int				src_a;
    int				src_r;
    int				src_g;
    int				src_b;
	int				dest_r;
	int				dest_g;
	int				dest_b;
	int				blended_color;
	int				blend_color;
    double			blend_factor;
	t_file			*file;
}				t_data;

typedef struct s_tex {
	char			*path;
	char			*tex_img;
	char			*tex_addr;
	int				width;
	int				height;
	int				bpp;
	int				line_length;
	int				endian; 
} t_tex;

typedef struct s_rc {
	double			camera_x;
	double			perp_wall_dist;
	double			ray_dir[2];
	double			step[2];
	double			side_dist[2];
	double			delta_dist[2];
	double			plane[2];
	double			texture_pos;
	double			step_n;
	int				hit;
	int				side;
	int				map_x;
	int				map_y;
	int				texture_x;
	int				texture_y;
	int				texture_num;
	int				draw_start;
	int				draw_end;
	int				line_height;
	int				color;
	int				wall_type;
	struct s_tex	texture[5];
} t_rc;

typedef struct s_color {
	int				red;
	int				green;
	int				blue;
	int				magenta;
	int				yellow;
	int				grey;
	int src_a;
    int src_r;
    int src_g;
    int src_b;

}				t_color;

typedef struct s_point {
	double			x;
	double			y;
}				t_point;

typedef struct s_vector {
	int				x;
	int				y;
}				t_vector;

/*main.c*/
int		ft_clean(t_data *data);
int		ft_destroy(t_data *data);
int		key_hook_press(int keycode, t_data *data);
int		key_hook_release(int keycode, t_data *data);
int		ft_init(t_data *data);
int		create_trgb(int t, int r, int g, int b);
int		cub_draw(t_data *data);
void	handle_movement(t_data *data);
void	my_xpm_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	map_test(t_data *data);
void	draw_map(t_data *data, int map[MAP_SIZE][MAP_SIZE], int offset_x, int offset_y);
void	display_angle(t_data *data);
void	cub_menu(t_data *data);
void	fill_values(t_data *data, char *line);


/* raycaster */
void	ceiling_floor(t_data *data);
void	raycasting(t_data *data);
void	rc_delta_dist(t_data *data);
void	rc_side_step(t_data *data);
void	side_hit_x(t_data *data);
void	side_hit_y(t_data *data);
void	rc_loop_hit(t_data *data);
void	raycasting_loop(t_data *data, int line_height, int draw_start, int draw_end);
void	raycasting(t_data *data);
void	calculate_ray_direction(t_data *data, int x);
void	calculate_map_position(t_data *data);
void	perp_wall_dist(t_data *data);

/* render */
void	draw_loop(t_data *data, int x, int draw_start, int draw_end);
void	draw_texture(t_data *data, int draw_start, int line_height);
void	draw_end_to_start(t_data *data, int *line_height, int *draw_start, int *draw_end);
void	draw_world(t_data *data, int x, int draw_start, int compass);

/* render utils */
int		ft_floor(double x);
int		retrieve_px_info(t_data *data, int x, int y, int texture_index);
int		xpm_switcher(t_data *data, int wall_type);

/* shader */
int		shading_color(int color, double shading_factor);
double	apply_shading(t_data *data, double shading_factor);

/*utils.c*/
void	double_to_string(double value, char *buffer);
void	double_to_string_y(double value, char *buffer);
void	double_to_string_x(double value, char *buffer);


//file_reader.c
int		work_split(t_file *data, char **argv);
int		for_file(t_file *data, char **argv);
int		for_text(t_file *data);
int		for_map(t_file *data);
int		open_text(t_file *data);

//file_utils.c
int		check_name(char **argv);
int		check_access(t_file *data, char **argv);
char	**file_fill(t_file *data, char **argv, int j, char *tmp);
void	free_z_values(t_data *data);
int		map_conversion(t_data *data, int i);

//map_check.c
char	**list_map(t_file *data);
int		check_map(t_file *data, char *tmp, int i, int j);
int		square_map(t_file *data, int i, int j, int extra);
void	remove_newline(t_file *data);
int		valid_map(t_file *data, int i, int j);

//map_utils.c
int		is_player(char c);
int		smallcheck(char c);
int		short_check(t_file *data, int i, int j);
void	map_width(t_file *data);
int		change_value(int c);

//texture_check.c
int		help(t_file *data, int i, int j, char *tmp);
char	**list_textures(t_file *data, int i, int j, char *tmp);
int		text_check(t_file *data);
int		check_textures(t_file *data, int i, char *tmp);
int		skip_textures(t_file *data);

//text_utils.c
int		is_texture(t_file *data, int i, int x);
int		check_filelen(t_file *data);
int		check_filetype(t_file *data);
int		double_id(t_file *data, char *t1, char *t2, int i);

//trim.c
char 	*trim_until(char *s, char *tmp);
char	*trim(char *s, char *tmp);
int		call_color(t_file *data, char *s);
int		call_text(t_file *data, char *s);

//check_color.c
int		check_color(t_file *data);
int		color_f(t_file *data, char *s, char *tmp, int i);
int		color_c(t_file *data, char *s, char *tmp, int i);
int		color_num(char **s);

//utils.c
void	init_file(t_file *data);
void	ft_free(t_file *data);
void	free_array(char **array);
int		*player_pos(t_file *data);
int		file_check(t_file *data, int i, char *tmp);

//main.c
int		the_fail(t_data *data, t_file *file, t_text *text, t_player *player);
void	the_handover(t_data *data);
int		the_start(t_data *data, char **argv);

//xpm_check.c
int		open_texture_file(const char *text);
ssize_t	read_texture_file(int fd, char *buffer, size_t buffer_size);
int		parse_texture_header(const char *header_line, int *width, int *height);
int		validate_texture_dimensions(int width, int height);
int		xpm_check(t_data *data, char *text, int width, int height);

# define KEY_ANSI_A			0X61
# define KEY_ANSI_S			0X73
# define KEY_ANSI_D			0X64
# define KEY_ANSI_W			0X77
# define KEY_ESCAPE			0xff1b
# define KEY_LEFTARROW		0XFF51
# define KEY_RIGHTARROW		0XFF53
# define KEY_DOWNARROW		0XFF54
# define KEY_UPARROW		0XFF52

#endif