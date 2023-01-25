/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 02:11:28 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 04:33:38 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	printinstmap(int **map, t_data *data);

char	**copymap(char **map)
{
	char	**copy;
	int		i;

	i = 0;
	while (map && map[i])
		i++;
	copy = malloc((i + 1) * sizeof(char *));
	copy[i] = NULL;
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			fatal("malloc error copymap\n");
		i++;
	}
	return (copy);
}

char	**takemap(char **map, int fd)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	while (check != 0)
	{
		map[i] = get_next_line(fd);
		if (map[i] == NULL)
			check = 0;
		i++;
	}
	return (map);
}

void	parsemap(t_data *data)
{
	int		y;
	int		**instmap;

	y = 0;
	instmap = malloc(data->check->height * sizeof(int *));
	if (!instmap)
		fatal("instance map malloc error\n");
	while (data->check->maparray[y] != NULL)
	{
		instmap[y] = malloc(data->check->width * sizeof(int));
		if (!instmap[y])
			fatal("instance map malloc error\n");
		y++;
	}
	count_w_c(data, instmap);
}

void	count_w_c(t_data *data, int **instmap)
{
	int		y;
	int		x;
	t_check	*check2;

	y = 0;
	x = 0;
	check2 = makecheck();
	while (data->check->maparray[y] != NULL)
	{
		while (x < data->check->width)
		{
			if (data->check->maparray[y][x] == '1')
				instmap[y][x] = check2->wall++;
			else if (data->check->maparray[y][x] == 'C')
				instmap[y][x] = check2->collect++;
			else
				instmap[y][x] = 0;
			x++;
		}
		x = 0;
		y++;
	}
	data->check->instmap = instmap;
	free(check2);
}
