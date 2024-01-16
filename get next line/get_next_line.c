/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:29:43 by dong-kim          #+#    #+#             */
/*   Updated: 2023/10/14 16:18:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(char *buffer)
{
	int	idx;
	int	found_nl;
	int	offset;

	idx = 0;
	found_nl = 0;
	offset = 0;
	while (buffer[idx])
	{
		if (found_nl == 1)
		{
			buffer[offset] = buffer[idx];
			offset++;
		}
		if (buffer[idx] == '\n')
			found_nl = 1;
		buffer[idx] = '\0';
		idx++;
	}
	return (found_nl);
}

char	*solve(int fd, char *buffer, char *next_line, int rd_bytes)
{
	while (1)
	{
		if (buffer[0])
		{
			next_line = ft_strjoin(next_line, buffer);
			if (!next_line)
				return (NULL);
		}
		else
		{
			rd_bytes = read(fd, buffer, BUFFER_SIZE);
			if (rd_bytes == -1)
				return (NULL);
			if (rd_bytes == 0)
				break ;
			else
				next_line = ft_strjoin(next_line, buffer);
			if (!next_line)
				return (NULL);
		}
		if (found_newline(buffer) == 1)
			break ;
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	int			start;
	int			rd_bytes;

	start = 0;
	rd_bytes = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		while (buffer[start])
			buffer[start++] = '\0';
		return (NULL);
	}
	next_line = NULL;
	return (solve(fd, buffer, next_line, rd_bytes));
}

#include <stdio.h>
int main()
{
	while (1)
	{
		char *line = get_next_line(0);
		if (line == NULL)
			return (1);
		printf("[%s]\n", line);	
	}
	return (0);
}
