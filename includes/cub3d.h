/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:46 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/15 21:29:21 by jorgonca         ###   ########.fr       */
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

# define HEIGHT 1080
# define WIDTH 1920

typedef struct s_data {
	float		x;
	float		y;
	float		z;
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

// # define KEY_ANSI_A			0X61
// # define KEY_ANSI_Q			0X71
// # define KEY_ESCAPE			0xff1b
// # define KEY_LEFTARROW		0XFF51
// # define KEY_RIGHTARROW		0XFF53
// # define KEY_DOWNARROW		0XFF54
// # define KEY_UPARROW		0XFF52


#endif