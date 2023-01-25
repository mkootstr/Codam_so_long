/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 00:55:58 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 04:35:03 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_check	*check;
	t_data	*data;

	check = makecheck();
	data = malloc(1 * sizeof(t_data));
	data->check = check;
	check->maparray = NULL;
	if (argc != 2)
		fatal("wrong number of arguments\n");
	checktype(argv[1]);
	fd = ft_open(argv[1]);
	check->height = get_size(fd);
	ft_close(fd);
	fd = ft_open(argv[1]);
	check->maparray = malloc((check->height + 1) * sizeof(char *));
	check->maparray[check->height] = NULL;
	check->maparray = takemap(check->maparray, fd);
	ft_close(fd);
	prep_data(data);
	free_all(data);
	return (0);
}

void	prep_data(t_data *data)
{
	int	i;

	i = 0;
	data->check->width = checkwidth(data->check->maparray);
	if (data->check->width == -1)
		fatal("invalid map size\n");
	if (checkwalls(data->check->maparray, data->check->width) == -1)
		fatal("map not closed\n");
	findpath(data);
	parsemap(data);
	so_long(data);
}
