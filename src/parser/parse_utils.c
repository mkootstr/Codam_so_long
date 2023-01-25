/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:10:31 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 03:01:31 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

ssize_t	get_size(int fd)
{
	char	buf[100];
	ssize_t	rb;
	ssize_t	nl;
	ssize_t	i;

	nl = 1;
	rb = 1;
	i = 0;
	while (rb > 0)
	{
		rb = read(fd, buf, 100);
		while (i < rb && rb != -1)
		{
			if (buf[i] == '\n')
				nl++;
			i++;
		}
		i = 0;
	}
	return (nl);
}

void	count_chars(t_check *check, int x, int y)
{
	if (check->maparray[y][x] == 'C')
		check->collect++;
	if (check->maparray[y][x] == 'P')
		check->player++;
	if (check->maparray[y][x] == '1')
		check->wall++;
	if (check->maparray[y][x] == 'E')
		check->exit++;
}

void	save_start(t_data *data, int x, int y)
{
	data->check->start_x = x;
	data->check->start_y = y;
	data->x = x;
	data->y = y;
}
