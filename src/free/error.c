/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 00:58:34 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 04:29:04 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	fatal(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

int	ft_open(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		fatal("can't open file\n");
	return (fd);
}

int	ft_close(int fd)
{
	int	rv;

	rv = 0;
	if (fd != -1)
	{
		rv = close(fd);
		if (rv == -1)
			fatal("close error\n");
	}
	return (rv);
}
