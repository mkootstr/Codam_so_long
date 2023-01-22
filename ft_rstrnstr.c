/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rstrnstr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marlou <marlou@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 17:09:02 by marlou        #+#    #+#                 */
/*   Updated: 2022/12/01 21:10:35 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>
#include <stdio.h>

char	*ft_rstrnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle == NULL || *needle == '\0')
		return ((char *)haystack);
	i = ft_strlen(haystack) - 1;
	j = 0;
	while (i >= 0 && len > 0)
	{
		j = ft_strlen(needle) - 1;
		while (haystack[i] == needle[j] && j >= 0)
		{
			if (j == 0)
				return ((char *)haystack + i);
			i--;
			j--;
		}
		i = i + j - 1;
		i--;
		len--;
	}
	return (NULL);
}
