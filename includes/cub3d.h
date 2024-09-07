/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:46 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/07 22:51:29 by jorgonca         ###   ########.fr       */
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
# include <limits.h>
# include <endian.h>
# include <mlx.h>
# include <float.h>
# include <sys/time.h>
# include <time.h>

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

# define BUFFER_SIZE 1

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
# define MOVE_SPEED 0.15




typedef struct s_player {
	//struct s_point	**pos;  //-> you dont need this
    double          pos[2]; //-> you need this
    double			dx;
    double			dy;
    double			angle;
}				t_player;

typedef struct s_fl_cl {
    double ray_dy[2];
    double ray_dx[2];
    double pos_z;
    double row_distance;
    double floor_step[2];
    double floor[2];
    int    cell[2];
    int    tex[2];
    int    floor_tex;
    int    ceiling_tex;
    double    shading_factor;
    int    color;
} t_fl_cl;

typedef struct s_data {
    double		x;
    double		y;
    double		z;
    double		arrow_angle;
	int			**z_values;
    int			*line_z;
    int map_height;
    int map_width;
    //int		color;
    char *map_name;
    char **map_buf;

    int current_line;

	int		fd;
    char    *addr;
    int     endian;
    int     line_length;
    int     bpp;
    void		*mlx;
    void		*win;
    void		*img;
 
    int map_offset_x;
    int map_offset_y;
    int map[MAP_SIZE][MAP_SIZE];
    void *map_img;
    char    *map_addr;
    t_player	*player;
   // struct s_color		color;
    struct s_rc	    *raycast;
    struct s_point		**map_coord;
    struct s_fl_cl *fl_cl;
    //t_fireball fireball;
    double start_angle;
    
    
    double time;
    double old_time;
    double frame_time;
    double fps;
    double rotation_speed;
    double move_speed;

    int key_states[KEY_COUNT];
    int player_x;
    int player_y;

    int star_x[100];
    int star_y[100];
}				t_data;

typedef struct s_tex {
    char *path;
    char *tex_img;
    char *tex_addr;
    int width;
    int height;
    int bpp;
    int line_length;
    int endian; 
} t_tex;



// typedef struct s_rc {
//     double camera_x;
//     double perp_wall_dist;
//     struct s_point	**ray_dir;
//     struct s_point	**step;
//     struct s_point	**side_dist;
//     struct s_point	**delta_dist;
//     struct s_point  **plane;
//     int hit;
//     int		side;
//     int		map_x;
//     int		map_y;
//     int     texture_x;
//     int     texture_y;
//     double  texture_pos;
//     int     texture_num;
//     struct s_tex texture[5];
//     double  step_n;
//     int draw_start;
//     int draw_end;
//     int line_height;
//     int color;
//     int wall_type;
// } t_rc;

typedef struct s_rc {
    double camera_x;
    double perp_wall_dist;
    // struct s_point	**ray_dir;
    // struct s_point	**step;
    // struct s_point	**side_dist;
    // struct s_point	**delta_dist;
    // struct s_point  **plane;
    double ray_dir[2];
    double step[2];
    double side_dist[2];
    double delta_dist[2];
    double plane[2];
    int hit;
    int		side;
    int		map_x;
    int		map_y;
    int     texture_x;
    int     texture_y;
    double  texture_pos;
    int     texture_num;
    struct s_tex texture[5];
    double  step_n;
    int draw_start;
    int draw_end;
    int line_height;
    int color;
    int wall_type;
} t_rc;

typedef struct s_color {
	int			red;
	int			green;
	int			blue;
    int			magenta;
    int			yellow;
    int			grey;
    //uint32_t    color32;
}				t_color;

/*new player position with direction and angle*/
// data->player->pos[0]   -> this is your X
// data->player->pos[1]   -> this is your Y   
// typedef struct s_player {
// 	struct s_point	**pos;  //-> you dont need this
//     // double             pos[2]; -> you need this
//     double			dx;
//     double			dy;
//     double			angle;
// }				t_player;



typedef struct s_point {
	double			x;
	double			y;
}				t_point;



typedef struct s_vector {
    int			x;
    int			y;
}				t_vector;

/*main.c*/
int ft_clean(t_data *data);
int ft_destroy(t_data *data);
int key_hook_press(int keycode, t_data *data);
int key_hook_release(int keycode, t_data *data);
void handle_movement(t_data *data);
int create_trgb(int t, int r, int g, int b);

void my_xpm_pixel_put(t_data *data, int x, int y, int color);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int cub_draw(t_data *data);
void map_test(t_data *data);
void draw_map(t_data *data, int map[MAP_SIZE][MAP_SIZE], int offset_x, int offset_y);
void display_angle(t_data *data);
void    cub_menu(t_data *data);
int ft_init(t_data *data);

// void draw_filled_rectangle(t_data *data, int x, int y, int width, int height, int color);

/* raycaster */
void    ceiling_floor(t_data *data);
void raycasting(t_data *data);
void rc_delta_dist(t_data *data);
void rc_side_step(t_data *data);
void side_hit_x(t_data *data);
void side_hit_y(t_data *data);
void rc_loop_hit(t_data *data);
void raycasting_loop(t_data *data, int line_height, int draw_start, int draw_end);
void raycasting(t_data *data);
void calculate_ray_direction(t_data *data, int x);
void  calculate_map_position(t_data *data);
void perp_wall_dist(t_data *data);

/* render */
void draw_loop(t_data *data, int x, int draw_start, int draw_end);
void draw_texture(t_data *data, int draw_start, int line_height);
void draw_end_to_start(t_data *data, int *line_height, int *draw_start, int *draw_end);
void draw_world(t_data *data, int x, int draw_start, int compass);

/* render utils */
int ft_floor(double x);
int retrieve_px_info(t_data *data, int x, int y, int texture_index);
int  xpm_switcher(t_data *data, int wall_type);

/* shader */
int shading_color(int color, double shading_factor);
double apply_shading(t_data *data, double shading_factor);

/* move*/

/* key_hook*/

/* draw */

/* game info */


//sting_v2(t_data *data, int map[MAP_SIZE][MAP_SIZE], double arrow_angle);

/*utils.c*/
void    double_to_string(double value, char *buffer);
void    double_to_string_y(double value, char *buffer);
void    double_to_string_x(double value, char *buffer);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
int	ft_wordcounter(char const *str, char c);
int ft_strchr(const char *s, int c);
void *ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int	ft_atoi(const char *str);

// void update_fireball(t_data *data);
// void launch_fireball(t_data *data);
/*read.c*/

int	ft_open(char *file, int fd, t_data *data);
void	ft_info_read(char *file, t_data *data);

/* key mapping */
//# define KEY_ANSI_Q			0X71

# define KEY_ANSI_A			0X61
# define KEY_ANSI_S			0X73
# define KEY_ANSI_D			0X64
# define KEY_ANSI_W			0X77
// # define KEY_SPACE			0X20
# define KEY_ESCAPE			0xff1b
# define KEY_LEFTARROW		0XFF51
# define KEY_RIGHTARROW		0XFF53
# define KEY_DOWNARROW		0XFF54
# define KEY_UPARROW		0XFF52


#endif