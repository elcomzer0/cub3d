/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgonca <jorgonca@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:46:00 by jorgonca          #+#    #+#             */
/*   Updated: 2024/08/06 19:10:03 by jorgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/cub3d.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	n;

	sign = 1;
	n = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1 * sign;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = 10 * n + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	temp;
	size_t	all;

	temp = size;
	all = ft_strlen(src) + ft_strlen(dst);
	while (*dst != 0 && size > 0)
	{
		dst++;
		size--;
	}
	if (size == 0)
	{
		return (ft_strlen(src) + temp);
	}
	while (*src != 0 && size > 1)
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (all);
	return (0);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	long unsigned int	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		len = 0;
	if (len > (ft_strlen(s) - start))
	{
		dest = (char *)malloc(ft_strlen(s) - start + 1);
	}
	else
		dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (len > 0 && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	char	*d;
	int		i;

	d = s;
	i = 0;
	while (n > 0)
	{
		d[i] = '\0';
		i++;
		n--;
	}
	return ;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len;
	char			*dest;

	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
	{
		return (NULL);
	}
	ft_strlcpy(dest, s1, len + 1);
	ft_strlcat(dest, s2, len + 1);
	return (dest);
}

void *ft_calloc(size_t count, size_t size)
{
	void *ptr;
	size_t total_size;

	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr)
		ft_bzero(ptr, total_size);
	return (ptr);
}

int ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
} */

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

void double_to_string(double value, char *buffer)
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

void double_to_string_x(double value, char *buffer)
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
    *ptr++ = 'X';
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
void double_to_string_y(double value, char *buffer)
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
    *ptr++ = 'Y';
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
