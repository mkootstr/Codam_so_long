/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:08:54 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 04:33:20 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	findpath(t_data *data)
{
	findstart(data);
	data->check->mapcpy = copymap(data->check->maparray);
	data->check->collect = 0;
	data->check->player = 0;
	checkchars(data->check);
	if (bcktrck(data->check, data->check->start_x, data->check->start_y) == 0)
		fatal("invalid path\n");
	freemap(data->check->mapcpy);
}

void	findstart(t_data *data)
{
	int	x;
	int	y;
	int	p;

	x = 0;
	y = 0;
	p = 0;
	while (data->check->maparray[y] != NULL)
	{
		while (data->check->maparray[y][x] != '\n' && \
		data->check->maparray[y][x] != '\0')
		{
			if (data->check->maparray[y][x] == 'P')
			{
				p++;
				save_start(data, x, y);
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (p != 1)
		fatal("wrong number of players\n");
}

int	bcktrck(t_check *check, int x, int y)
{
	if (check->cllct == 0 && check->exit == 0)
		return (1);
	if (check->mapcpy[y][x] == 'E')
		check->exit--;
	if (check->mapcpy[y][x] == '1')
		return (0);
	if (check->mapcpy[y][x] == 'C')
		check->cllct--;
	if (check->mapcpy[y][x] == '0' || check->mapcpy[y][x] == 'P' || \
	check->mapcpy[y][x] == 'C' || check->mapcpy[y][x] == 'E')
		check->mapcpy[y][x] = '1';
	if (bcktrck(check, x - 1, y))
		return (1);
	if (bcktrck(check, x, y - 1))
		return (1);
	if (bcktrck(check, x + 1, y))
		return (1);
	if (bcktrck(check, x, y + 1))
		return (1);
	return (0);
}
