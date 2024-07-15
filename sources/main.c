/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:31 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/15 22:53:53 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

int main(int ac, char **av)
{
    t_data *data;
    (void)av;
    (void)ac;
    
    data = (t_data *)calloc(1, sizeof(t_data));
    if (!data)
        return (1);
    

    free(data);
    data = NULL;
    return (0);
}