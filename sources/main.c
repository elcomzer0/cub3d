/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:31 by jorgonca          #+#    #+#             */
/*   Updated: 2024/09/07 18:27:44 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

int main(int ac, char **av)
{
    t_player *player;
    t_data *data;
    (void)av;
    (void)ac;
    
    player = (t_player *)calloc(1, sizeof(t_player));
    data = (t_data *)calloc(1, sizeof(t_data));
    data->player = player;
    
    if (!data)
    {
        write(2, "Error: malloc failed\n", 20);
        free(data);
        data = NULL;
        return (1);
    }
    if (ac != 2 || (strcmp(av[1] + strlen(av[1]) - 4, ".cub") != 0))   
    {
        write(2, "Error: bad arguments\n", 20);
        ft_clean(data);
        return (1);
    }
    if (ac == 2)
    {
        data->map_name = av[1];
        if (ft_init(data) == 1)
        {
            ft_clean(data);
            return (1);
        }
    }
        //ft_init(data);
    return (0);
}