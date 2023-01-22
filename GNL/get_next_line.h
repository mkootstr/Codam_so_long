/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 16:30:40 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/19 14:57:37 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
//# include "../so_long.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef enum e_status
{
	NEWLINE_NOT_FOUND,
	NEWLINE_FOUND,
}	t_status;

typedef struct s_buf
{
	char	buf[BUFFER_SIZE];
	ssize_t	size;
}		t_buf;

char		*get_next_line(int	fd);
t_status	ft_prcsbuf(char **line, char *buf, ssize_t *br);
char		*ft_strndup(const char *src, size_t n);
char		*ft_join(char *s1, char *s2, char *s3, size_t l);
void		ft_append(char **line, char *buf, size_t l);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);

#endif
