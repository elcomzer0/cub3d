/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:00 by jorgonca          #+#    #+#             */
/*   Updated: 2024/07/29 18:48:34 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"


int	ft_wordcounter(char const *str, char c)
{
	int	i;
	int	wordcounter;

	i = 0;
	wordcounter = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			wordcounter++;
			while (str[i] != c && str[i])
			{
				i++;
			}
		}
		else
			i++;
	}
	return (wordcounter);
}

static int	ft_len_words(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	int		j;
	int		wordcounter;
	char	**dest;

	i = 0;
	j = -1;
	wordcounter = ft_wordcounter(s, c);
	dest = (char **)malloc(sizeof(char *) * (wordcounter + 1));
	if (!dest)
		return (NULL);
	while (++j < wordcounter)
	{
		while (s[i] == c)
		{
			i++;
		}
		len = ft_len_words(s, c, i);
		dest[j] = ft_substr(s, i, len);
		i += len;
	}
	dest[j] = 0;
	return (dest);
}

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

char	*ft_temp(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	free(stash);
	return (temp);
}

char	*ft_writeline(char *retainer)
{
	char	*written;
	int		counter;

	counter = 0;
	if (!retainer)
		return (NULL);
	while (retainer[counter] != '\n' && retainer[counter] != '\0')
	{
		counter++;
	}
	written = malloc(sizeof(char) * (counter + 2));
	if (!written)
		return (NULL);
	counter = 0;
	while (retainer[counter] != '\n' && retainer[counter] != '\0')
	{
		written[counter] = retainer[counter];
		counter++;
	}
	if (retainer[counter] == '\n')
		written[counter++] = '\n';
	written[counter] = '\0';
	return (written);
}

char	*ft_readnstash(int fd, char *retainer)
{
	int		valread;
	char	*buffer;

	if (!retainer)
		retainer = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	valread = 1;
	while (valread > 0)
	{
		valread = read(fd, buffer, BUFFER_SIZE);
		if (valread == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[valread] = '\0';
		retainer = ft_temp(retainer, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (retainer);
}

char	*ft_nextline(char *retainer, int i)
{
	char	*nl;
	int		j;

	j = 0;
	if (!retainer[i])
	{
		free (retainer);
		return (NULL);
	}
	nl = malloc(sizeof(char) * (ft_strlen(retainer) - i + 1));
	if (!nl)
		return (NULL);
	while (retainer[i] != '\0')
	{
		nl[j++] = retainer[i++];
	}
	nl[j] = '\0';
	free (retainer);
	retainer = NULL;
	return (nl);
}

char	*get_next_line(int fd)
{
	static char		*retainer;
	char			*written;
	int				i;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(retainer);
		retainer = NULL;
		return (NULL);
	}
	retainer = ft_readnstash(fd, retainer);
	if (retainer[0] == '\0')
	{
		free(retainer);
		retainer = NULL;
		return (NULL);
	}
	if (retainer == NULL)
		return (NULL);
	written = ft_writeline(retainer);
	i = ft_strlen(written);
	retainer = ft_nextline(retainer, i);
	return (written);
}
