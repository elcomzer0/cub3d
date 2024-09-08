/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:31 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/08 16:32:32 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

int	the_fail(t_data *data, t_file *file, t_text *text, t_player *player)
{
	int	x;

	x = 0;
	if (text == NULL)
		(ft_putstr_fd("Error: Malloc failed\n", 2), x++);
	if (file == NULL)
		(ft_putstr_fd("Error: Malloc failed\n", 2), x++);
	if (player == NULL)
		(ft_putstr_fd("Error: Malloc failed\n", 2), x++);
	if (data == NULL)
		(ft_putstr_fd("Error: Malloc failed\n", 2), x++);
	if (x != 0)
	{
		if (data != NULL)
			free(data);
		if (file != NULL)
			free(file);
		if (text != NULL)
			free(text);
		return (false);
	}
	return (true);
}

int main(int ac, char **av)
{
	t_player *player;
   	t_text	*text;
	t_file	*file;
	t_data	*data;

    text = (t_text *)malloc(sizeof(t_text));
	file = (t_file *)malloc(sizeof(t_file));
	player = (t_player *)malloc(sizeof(t_player));
	data = (t_data *)malloc(sizeof(t_data));
	if (the_fail(data, file, text, player) == false)
		return (1);
	file->text = text;
	data->file = file;
	data->player = player;;
	if (ac != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if (work_split(file, av) == false)
		return (free(text), free(player), free(file), free(data), 1);
	data->z_values = NULL;
	if (map_conversion(data, 0) == false)
		return (ft_free(file),
			free(player), free(text), free(file), free(data), 1);
	the_handover(data);
	if (ft_init(data) == false)
		return (ft_free(file),
			ft_clean(data), free(text), free(file), free(player), free(data), 1);
	ft_free(file);
	free_z_values(data->z_values, data->file->line_hei);
	(free(text), free(player), free(file), free(data));
	return (0);
}

void the_handover(t_data *data)
{
	// KEEP WHAT YOU NEED AND DELETE THE REST
	// DONT FORGET TO CHECK IF THE WIDTH AND HEIGHT OF THE XMP ARE THE SAME AND 64x64
	// z_values are already calculated in the map_conversion function -> player position is converted to 0 in the z_values
	// so you can use the z_values as the map
	// the z_values are stored as int ** so you can use it as a 2d array
	// /*(write your var)*/ = data->file->map; // this is the map in char ** format
	data->map_width = data->file->line_len; // this is the width of the map
	data->map_height = data->file->line_hei; // this is the height of the map
	printf("data->file->pos[0]: %d\n", data->file->pos[0]);
	printf("data->file->pos[1]: %d\n", data->file->pos[1]);
	data->player->pos[0] = (double)data->file->pos[0]; // this is the x position of the player add plus 1 if needed.
	data->player->pos[1] = (double)data->file->pos[1]; // this is the y position of the player add plus 1 if needed.
	printf("data->player->pos[0]: %f\n", data->player->pos[0]);
	printf("data->player->pos[1]: %f\n", data->player->pos[1]);
	// data->player-> = data->file->player_direction; // this is the direction of the player N, S, W, E its stored as a char
	// /*(write your var)*/ = data->file->text->no; // this is the path to the north texture stored as a char *
	// /*(write your var)*/ = data->file->text->so; // this is the path to the south texture stored as a char *
	// /*(write your var)*/ = data->file->text->we; // this is the path to the west texture stored as a char *
	// /*(write your var)*/ = data->file->text->ea; // this is the path to the east texture stored as a char *
	// /*(write your var)*/ = data->file->text->f; // this is the floor color stored as a char *
	// /*(write your var)*/ = data->file->text->c; // this is the ceiling color stored as a char *
	// /*(write your var)*/ = data->file->text->colorf; // this is the floor color stored as a char ** used to get the rgb values 
	// /*(write your var)*/ = data->file->text->colorc; // this is the ceiling color stored as a char ** used to get the rgb values
	// // /*(write your var)*/ = data->file->text->fr; // this is the red value of the floor color
	// /*(write your var)*/ = data->file->text->fg; // this is the green value of the floor color
	// /*(write your var)*/ = data->file->text->fb; // this is the blue value of the floor color
	// /*(write your var)*/ = data->file->text->cr; // this is the red value of the ceiling color
	// /*(write your var)*/ = data->file->text->cg; // this is the green value of the ceiling color
	// /*(write your var)*/ = data->file->text->cb; // this is the blue value of the ceiling color
	// /*(write your var)*/ = data->file->texture; // this is the path to the textures stored as a char **     -> his might not be needed
}
