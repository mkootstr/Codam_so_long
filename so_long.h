/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 20:32:32 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/19 14:41:53 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"


void	so_long(t_check *map);

size_t	ft_strlen(const char *str);
char	*ft_rstrnstr(const char *haystack, const char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
char	*get_next_line(int	fd);

ssize_t	get_size(int fd);
char	**takemap(char **map, int fd);
void	checktype(char *file);

void	freemap(char **maparray);

#endif
