/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:07:25 by miturk            #+#    #+#             */
/*   Updated: 2024/09/10 14:41:55 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	is_texture(t_file *data, int i, int x)
{
	char	*tmp;

	tmp = ft_strtrim(data->file[i], " ");
	if (tmp == NULL)
		return (ft_putstr_fd("Error: Malloc failed_\n", 2), false);
	if (tmp[x] == 'N' && tmp[x + 1] == 'O'
		&& tmp[x + 2] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'S' && tmp[x + 1] == 'O'
		&& tmp[x + 2] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'W' && tmp[x + 1] == 'E'
		&& tmp[x + 2] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'E' && tmp[x + 1] == 'A'
		&& data->file[i][x + 2] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'F' && tmp[x + 1] == ' ')
		return (free(tmp), true);
	else if (tmp[x] == 'C' && tmp[x + 1] == ' ')
		return (free(tmp), true);
	else
		return (free(tmp), false);
}

int	skip_textures(t_file *data)
{
	int	i;

	i = 0;
	while (data->file[i] != NULL)
	{
		if ((is_texture(data, i, 0) == false) && data->file[i][0] != '\n')
			break ;
		i++;
	}
	if (i < 6)
		return (-1);
	return (i);
}

int	check_filelen(t_file *data)
{
	if ((int)ft_strlen(data->text->no) < 4)
		return (ft_putstr_fd("Error: Invalid texture: NO\n", 2), false);
	if ((int)ft_strlen(data->text->so) < 4)
		return (ft_putstr_fd("Error: Invalid texture: SO\n", 2), false);
	if ((int)ft_strlen(data->text->ea) < 4)
		return (ft_putstr_fd("Error: Invalid texture: EA\n", 2), false);
	if ((int)ft_strlen(data->text->we) < 4)
		return (ft_putstr_fd("Error: Invalid texture: WE\n", 2), false);
	return (true);
}

int	check_filetype(t_file *data)
{
	int		i;
	char	*sub;

	if (check_filelen(data) == false)
		return (false);
	i = ((int)ft_strlen(data->text->no) - 4);
	sub = ft_substr(data->text->no, i, 4);
	if (ft_strncmp(sub, ".xpm", 4) != 0)
		return (free(sub), ft_putstr_fd("Error: Invalid texture: NO\n", 2), false);
	i = ((int)ft_strlen(data->text->so) - 4);
	(free(sub), sub = ft_substr(data->text->so, i, 4));
	if (ft_strncmp(sub, ".xpm", 4) != 0)
		return (free(sub), ft_putstr_fd("Error: Invalid texture: SO\n", 2), false);
	i = ((int)ft_strlen(data->text->we) - 4);
	(free(sub), sub = ft_substr(data->text->we, i, 4));
	if (ft_strncmp(sub, ".xpm", 4) != 0)
		return (free(sub), ft_putstr_fd("Error: Invalid texture: WE\n", 2), false);
	i = ((int)ft_strlen(data->text->ea) - 4);
	(free(sub), sub = ft_substr(data->text->ea, i, 4));
	if (ft_strncmp(sub, ".xpm", 4) != 0)
		return (free(sub), ft_putstr_fd("Error: Invalid texture: EA\n", 2), false);
	return (free(sub), true);
}

int	open_text(t_file *data)
{
	int	fd;

	fd = open(data->text->no, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error: Cannot open NO texture\n", 2), false);
	close(fd);
	fd = open(data->text->so, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error: Cannot open SO texture\n", 2), false);
	close(fd);
	fd = open(data->text->we, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error: Cannot open WE texture\n", 2), false);
	close(fd);
	fd = open(data->text->ea, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error: Cannot open EA texture\n", 2), false);
	close(fd);
	return (true);
}

int	double_id(t_file *data, char *t1, char *t2, int i)
{
	while (i++, is_texture(data, i, 0) == true)
	{	
		t1 = ft_strtrim(data->texture[i], " ");
		if (t1 == NULL)
			return (ft_putstr_fd("Error: Malloc failed_\n", 2), false);
		if (ft_strncmp(t1, "NO ", 3) == 0)
		{
			t2 = ft_strtrim(data->texture[i], data->text->no);
			if (t2 == NULL || ft_strlen(t2) > 3)
				return (ft_putstr_fd("Error: Duplicate texture: NO\n", 2), false);
		}
		else if (ft_strncmp(t1, "SO ", 3) == 0)
		{
			t2 = ft_strtrim(data->texture[i], data->text->so);
			if (t2 == NULL || ft_strlen(t2) > 3)
				return (ft_putstr_fd("Error: Duplicate texture: SO\n", 2), false);
		}
		else if (ft_strncmp(t1, "EA ", 3) == 0)
		{
			t2 = ft_strtrim(data->texture[i], data->text->ea);
			if (t2 == NULL || ft_strlen(t2) > 3)
				return (ft_putstr_fd("Error: Duplicate texture: EA\n", 2), false);
		}
		else if (ft_strncmp(t1, "WE ", 3) == 0)
		{
			t2 = ft_strtrim(data->texture[i], data->text->we);
			if (t2 == NULL || ft_strlen(t2) > 3)
				return (ft_putstr_fd("Error: Duplicate texture: WE\n", 2), false);
		}
		(free(t1), free(t2));
	}
	return (true);
}
