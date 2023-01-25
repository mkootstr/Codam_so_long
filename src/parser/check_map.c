/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:12:08 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 04:33:09 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	checkchars(t_check *check)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (check->maparray && check->maparray[y] != NULL)
	{
		x = 0;
		while (check->maparray[y][x] == '1' || check->maparray[y][x] == '0' || \
		check->maparray[y][x] == 'P' || check->maparray[y][x] == 'C' || \
		check->maparray[y][x] == 'E')
		{
			count_chars(check, x, y);
			x++;
		}
		if (check->maparray[y][x] == '\n' || check->maparray[y][x] == '\0')
			y++;
		else
			fatal("invalid character in map\n");
	}
	if (check->collect == 0)
		fatal("no collectibles in map\n");
	if (check->exit != 1)
		fatal("wrong number of exits\n");
	check->cllct = check->collect;
}

int	checklength(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	checkwalls(char **map, int width)
{
	int	x;
	int	y;
	int	length;

	x = 0;
	y = 0;
	length = checklength(map);
	while (y != length)
	{
		x = 0;
		if (y == 0 || y == (length - 1))
		{
			while (map[y][x] == '1')
				x++;
			if (x == width)
				x = 0;
			else
				return (-1);
		}
		else if (map[y][0] != '1' || map[y][width - 1] != '1')
			return (-1);
		y++;
	}
	return (0);
}

ssize_t	checkwidth(char **map)
{
	int		i;
	size_t	check;
	size_t	len;

	i = 0;
	if (!map || !map[i])
		return (-1);
	check = ft_strlen(map[i]);
	len = check;
	while (map[i] && len == check)
	{
		len = ft_strlen(map[i]);
		i++;
	}
	if (len == check - 1 && map[i] == NULL && check > 3)
		return (check - 1);
	return (-1);
}

void	checktype(char *file)
{
	if (ft_rstrnstr(file, ".ber", 4) == NULL)
		fatal("so_long: invalid input file type\n");
}
