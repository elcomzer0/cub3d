/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:46 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/27 19:41:32 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
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
# include <X11/X.h>
# include <X11/keysym.h>

# define BUFFER_SIZE 1024
# define HEIGHT 720
# define WIDTH  1024
# define TEXTURE_SIZE 64
# define MAP_SIZE 10
# define TILE_SIZE 50
# define FOV 90
# define NUM_RAYS WIDTH
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
# define EPSILON 1e-6
# define KEY_COUNT 256
# define ROT_SPEED -0.2
# define MOVE_SPEED -0.225

# define KEY_ANSI_A			0X61
# define KEY_ANSI_S			0X73
# define KEY_ANSI_D			0X64
# define KEY_ANSI_W			0X77
# define KEY_ESCAPE			0xff1b
# define KEY_LEFTARROW		0XFF51
# define KEY_RIGHTARROW		0XFF53
# define KEY_DOWNARROW		0XFF54
# define KEY_UPARROW		0XFF52

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

}					t_text;

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
	bool			stop;
	int				fd;
	int				i;
	t_text			*text;
}					t_file;

typedef struct s_player
{
	double			pos[2];
	double			dx;
	double			dy;
	double			angle;
}					t_player;

typedef struct s_fl_cl
{
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
}					t_fl_cl;

typedef struct s_data
{
	double			x;
	double			y;
	double			z;
	double			arrow_angle;
	double			start_angle;
	double			time;
	double			old_time;
	double			frame_time;
	double			fps;
	double			rotation_speed;
	double			move_speed;
	double			blend_factor;
	void			*mlx;
	void			*win;
	void			*img;
	void			*map_img;
	char			*map_name;
	char			**map_buf;
	char			*addr;
	char			*map_addr;
	int				**z_values;
	int				*line_z;
	int				map_height;
	int				map_width;
	int				current_line;
	int				fd;
	int				endian;
	int				line_length;
	int				bpp;
	int				map_offset_x;
	int				map_offset_y;
	int				map[MAP_SIZE][MAP_SIZE];
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
	struct s_point	**map_coord;
	struct s_rc		*raycast;
	t_player		*player;
	t_fl_cl			*fl_cl;
	t_file			*file;
}					t_data;

typedef struct s_tex
{
	char			*path;
	char			*tex_img;
	char			*tex_addr;
	int				width;
	int				height;
	int				bpp;
	int				line_length;
	int				endian;
}					t_tex;

typedef struct s_rc
{
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
}					t_rc;

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	int				magenta;
	int				yellow;
	int				grey;
	int				src_a;
	int				src_r;
	int				src_g;
	int				src_b;
}					t_color;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_vector
{
	int				x;
	int				y;
}					t_vector;

//get_next_line.c utils
char	*get_strchr(char *s, int c);
size_t	get_strlen(char *s);
char	*get_strjoin(char *s1, char *s2, int k);
char	*get_next_line(t_file *data);
char	*get_read_from_file_to_buffer(int fd, char **line_buffer);
char	*get_clean_buffer(char **line_buffer);
char	*get_read_from_buffer_newline(char **line_buffer);
char	*get_strdup(char *s);

//check_color.c
int		check_color(t_file *data);
int		color_f(t_file *data, char *s, char *tmp, int i);
int		color_c(t_file *data, char *s, char *tmp, int i);
int		color_num(char **s);

//draw_elements.c
int		create_trgb(int t, int r, int g, int b);
void	blend_colors_source(t_data *data, int source_color);
void	render_cl_shader(t_data *data);
void	render_cl_step(t_data *data, int p, int y);

//draw_utils.c
int		blend_colors_clfl(t_data *data, int color1,
			int color2, double blend_factor);
int		shading_color_ceiling(t_data *data, int color, double shading_factor);
int		shading_color_floor(t_data *data, int color, double shading_factor);
void	render_fl_step(t_data *data, int p, int y);
void	render_fl_shader(t_data *data);

//draw.c
void	render_pos_tex(t_data *data);
void	render_floor(t_data *data);
void	render_ceiling(t_data *data);
void	ceiling_floor(t_data *data);
int		cub_draw(t_data *data);

//file_reader.c
int		work_split(t_data *data, t_file *file, char **argv);
int		for_file(t_file *data, char **argv);
int		for_text(t_file *data);
int		for_map(t_file *data);
int		open_text(t_file *data);

//file_utils.c
int		check_name(char **argv);
int		check_access(t_file *data, char **argv);
char	**file_fill(t_file *data, char **argv, int j);
int		map_conversion(t_data *data, int i);

//free.c
void	free_player(t_data *data);
int		ft_clean(t_data *data);
int		ft_destroy(t_data *data);
void	free_z_values(t_data *data);
void	free_array(char **array);

//image.c
void	my_xpm_pixel_put(t_data *data, int x, int y, int color);
int		file_to_image(t_data *data, int i, int j, const char *text_path[5]);
void	init_textures(t_data *data);
int		init_rc(t_rc **rc);
void	free_raycast(t_rc *raycast);

//init.c
void	rc_help(t_data *data);
int		rc_init(t_data *data);
void	init_xpm(t_data *data, int i, int j);
int		init_fl_cl(t_data *data);
int		ft_init(t_data *data, int i);

//main.c
int		the_start(t_data *data, char **av);
void	the_handover(t_data *data);

//map_check.c
char	**list_map(t_file *data);
int		check_map(t_file *data, char *tmp, int i, int j);
int		square_map(t_file *data, int i, int j, int extra);
int		remove_newline(t_file *data, char *tmp, int i, int j);
int		valid_map(t_file *data, int i, int j);

//map_utils.c
int		is_player(char c);
int		smallcheck(char c);
int		short_check(t_file *data, int i, int j);
void	map_width(t_file *data);
int		change_value(int c);

//move_utils.c
void	down_key(t_data *data, double move_speed);
void	up_key(t_data *data, double move_speed);
void	right_rot_key(t_data *data, double rotation_speed);
void	left_rot_key(t_data *data, double rotation_speed);
void	rerender_frame(t_data *data);

//move.c
int		map_keycode(int keycode);
int		key_hook_press(int keycode, t_data *data);
int		key_hook_release(int keycode, t_data *data);
void	strafe(t_data *data, int direction, double move_speed);
void	handle_movement(t_data *data);

//parse_utils.c
void	init_file(t_file *data);
void	ft_free(t_file *data);
int		*player_pos(t_file *data);
int		file_check(t_file *data, int i, char *tmp);

//raycaster_2.c
void	perp_wall_dist(t_data *data);
void	calculate_ray_direction(t_data *data, int x);
void	calculate_map_position(t_data *data);
void	rc_delta_dist(t_data *data);
void	rc_side_step(t_data *data);

//raycaster.c
void	side_hit_x(t_data *data);
void	side_hit_y(t_data *data);
void	rc_loop_hit(t_data *data);
void	raycasting_loop(t_data *data, int line_height,
			int draw_start, int draw_end);
void	raycasting(t_data *data);

//read.c
void	fill_values(t_data *data, char *line);

//render_utils.c
int		retrieve_px_info(t_data *data, int x, int y, int texture_index);
int		xpm_switcher(t_data *data, int wall_type);
int		ft_floor(double x);
int		key_loop(t_data *data);

//render.c
void	draw_world(t_data *data, int x, int draw_start, int compass);
void	draw_end_to_start(t_data *data, int *line_height,
			int *draw_start, int *draw_end);
void	draw_texture(t_data *data, int draw_start, int line_height);
void	draw_loop(t_data *data, int x, int draw_start, int draw_end);

//shader.c
double	apply_shading(t_data *data, double shading_factor);
int		shading_color(int color, double shading_factor);
void	map_fail(t_file *data);
void	from_bot(char **s);

//text_utils.c
int		is_texture(t_file *data, int i, int x);
int		check_filelen(t_file *data);
int		check_filetype(t_file *data);
int		double_id(t_file *data, char *t1, char *t2, int i);

//texture_check.c
int		help(t_file *data, int i, int j, char *tmp);
char	**list_textures(t_file *data, int i, int j, char *tmp);
int		text_check(t_file *data);
int		check_textures(t_file *data, int i, char *tmp);
int		skip_textures(t_file *data);

//trim.c
char	*trim_until(char *s, char *tmp);
char	*trim(char *s, char *tmp);
int		call_color(t_file *data, char *s);
int		call_text(t_file *data, char *s);

//xpm_check.c
int		open_texture_file(const char *text);
ssize_t	read_texture_file(int fd, char *buffer, size_t buffer_size);
int		parse_texture_header(const char *header_line, int *width, int *height);
int		validate_texture_dimensions(int width, int height);
int		xpm_check(t_data *data, char *text, int width, int height);

#endif