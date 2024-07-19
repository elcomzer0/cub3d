/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:00 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/19 23:53:53 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

void float_to_string(float value, char *buffer)
{
    int whole_part;
    int fractional_part;
    char *ptr;
    char temp[10];
    int i;
    
    whole_part = (int)value;
    fractional_part = (int)((value - whole_part) * 100);

    if  (fractional_part < 0)
        fractional_part = -fractional_part;
    
    //create the string manually
    ptr = buffer;
    *ptr++ = 'A';
    *ptr++ = 'N';
    *ptr++ = 'G';
    *ptr++ = 'L';
    *ptr++ = 'E';
    *ptr++ = ':';
    *ptr++ = ' ';
    if (whole_part < 0)
    {
        *ptr++ = '-';
        whole_part = -whole_part;
    }

    i = 0;
    do {
        temp[i++] = whole_part % 10 + '0';
        whole_part /= 10;
    } while (whole_part > 0);
    
    while (i > 0)
    {
        *ptr++ = temp[--i];
    }
    
    *ptr++ = '.';
    temp[0] = fractional_part / 10 + '0';
    temp[1] = fractional_part % 10 + '0';
    *ptr++ = temp[0];
    *ptr++ = temp[1];
    *ptr++ = '\0';
    
}
