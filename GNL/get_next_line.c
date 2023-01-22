/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 11:14:17 by mkootstr      #+#    #+#                 */
/*   Updated: 2021/10/25 18:10:19 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int	fd)
{
	static t_buf	buf = (t_buf){.size = 0};
	char			*line;
	t_status		status;

	line = NULL;
	while (1)
	{
		if (!buf.size)
			buf.size = read(fd, buf.buf, BUFFER_SIZE);
		buf.buf[buf.size] = '\0';
		if (buf.size == 0)
			return (line);
		else if (buf.size < 0)
		{
			if (line)
				free(line);
			return (NULL);
		}
		else if (buf.size > 0)
		{	
			status = ft_prcsbuf(&line, buf.buf, &buf.size);
			if (status == NEWLINE_FOUND)
				return (line);
		}
	}
}

t_status	ft_prcsbuf(char **line, char *buf, ssize_t *br)
{
	ssize_t		n;
	size_t		i;
	t_status	status;

	n = *br;
	i = 0;
	while (n > 1 && buf[i] != '\n')
	{
		i++;
		n--;
	}
	if (!(*line))
		*line = ft_strndup(buf, (i + 1));
	else
		ft_append(line, buf, (i + 1));
	if (buf[i] == '\n' || !(*line))
		status = NEWLINE_FOUND;
	else
		status = NEWLINE_NOT_FOUND;
	ft_memmove(buf, &buf[i + 1], (*br - i));
	*br -= (i + 1);
	return (status);
}
