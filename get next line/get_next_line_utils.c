/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-kim <dong-kim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 01:24:57 by dong-kim          #+#    #+#             */
/*   Updated: 2023/04/06 23:48:42 by dong-kim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		return (len + 1);
	return (len);
}

size_t	find_size(char *data_line)
{
	if (data_line == NULL)
		return (0);
	return (ft_strlen(data_line));
}

char	*concat(char *str, char *data_line, int *idx)
{
	while (*data_line)
	{
		str[*idx] = *data_line++;
		*idx = *idx + 1;
	}
	return (str);
}

char	*ft_malloc_protection(char *to_free, int need_to_free)
{
	if (need_to_free)
		if (to_free)
			free(to_free);
	return (NULL);
}

char	*ft_strjoin(char *data_line, char *buffer)
{
	int		idx;
	char	*str;
	int		size;

	idx = 0;
	size = find_size(data_line);
	str = malloc((size + ft_strlen(buffer)) + 1);
	if (!str)
		return (ft_malloc_protection(data_line, 1));
	if (data_line != NULL)
	{
		str = concat(str, data_line, &idx);
		free(data_line);
	}
	while (*buffer)
	{
		str[idx++] = *buffer;
		if (*buffer++ == '\n')
			break ;
	}
	str[idx] = '\0';
	return (str);
}
