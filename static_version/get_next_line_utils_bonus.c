/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:38:55 by lbuisson          #+#    #+#             */
/*   Updated: 2024/11/27 10:14:15 by lbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *content)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s_temp;

	s_temp = (char *)s;
	while (*s_temp)
	{
		if (*s_temp == (char)c)
			return (s_temp);
		s_temp++;
	}
	if (*s_temp == '\0' && (char)c == '\0')
		return (s_temp);
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	unsigned const char	*str;
	size_t				i;

	if (!dest && !src)
		return (dest);
	dst = (unsigned char *)dest;
	str = (unsigned const char *)src;
	i = 0;
	if (dst < str)
	{
		while (i < n)
		{
			dst[i] = str[i];
			i++;
		}
	}
	else
	{
		while (i < n--)
			dst[n] = str[n];
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (n > i)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

size_t	ft_strlen_c(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (s[len] && s[len] == c)
		len++;
	return (len);
}
