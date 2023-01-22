#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char			*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	dest = (malloc((srclen + 1) * sizeof(char)));
	if (dest)
	{
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}

char **copymap(char **map)
{
	char **copy;
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	copy = malloc((i + 1) * sizeof(char *));
	copy[i] = NULL;
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	return (copy);
}

int	bcktrck(char **map, int x, int y)
{
	if (map[y][x] == 'E')
		return (1);
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == '0' || map[y][x] == 'P' || map[y][x] == 'C')
		map[y][x] = '1';
	if (bcktrck(map, x - 1, y))
		return (1);
	if (bcktrck(map, x, y - 1))
		return (1);
	if (bcktrck(map, x + 1, y))
		return (1);
	if (bcktrck(map, x, y + 1))
		return (1);
	return (0);
}

int main(void)
{
	char **map = NULL;
	map = malloc(6 * sizeof(char *));
	map[0] = strdup("1111111\n");
	map[1] = strdup("10000E1\n");
	map[2] = strdup("1111101\n");
	map[3] = strdup("1000P01\n");
	map[4] = strdup("1111111");
	map[5] = NULL;
	char **copy = copymap(map);
	printf("%d\n", bcktrck(copy, 4, 3));
	printf("%s", map[0]);
	printf("%s", map[1]);
	printf("%s", map[2]);
	printf("%s", map[3]);
	printf("%s", map[4]);
	return (0);
}