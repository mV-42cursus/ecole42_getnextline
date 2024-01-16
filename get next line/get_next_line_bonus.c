/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-kim <dong-kim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:29:43 by dong-kim          #+#    #+#             */
/*   Updated: 2023/06/12 14:20:07 by dong-kim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	buffer[ULIMIT_N][BUFFER_SIZE + 1];
	char		*next_line;
	int			start;
	int			rd_bytes;

	start = 0;
	rd_bytes = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > ULIMIT_N)
	{
		start = 0;
		while ((fd >= 0 && fd <= ULIMIT_N) && buffer[fd][start])
			buffer[fd][start++] = '\0';
		return (NULL);
	}
	next_line = NULL;
	next_line = solve(fd, buffer[fd], next_line, rd_bytes);
	return (next_line);
}

#include <stdio.h>
int main()
{
	while (1)
	{
		char *line = get_next_line(0);
		if (line == NULL)
			return (1);
		printf("%s", line);	
	}
	return (0);
}