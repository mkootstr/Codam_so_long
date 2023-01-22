/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 20:18:38 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/22 02:41:28 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//#include "so_long.h"
#define WIDTH 256
#define HEIGHT 256

typedef struct s_check
{
	char **maparray;
	char **mapcpy; //copy voor backtracken
	int **instmap;
	ssize_t	height;
	ssize_t	width;
	int	collect; //hoeveelheid collectibles
	int cllct;
	int	player; //hoeveelheid players
	int	start_x;
	int start_y;
	int exit; //hoeveelheid exits
	int wall;
	int background;
}		t_check;

typedef struct s_data
{
	mlx_t	*so_long;
	mlx_image_t	*player;
	mlx_image_t *wall;
	mlx_image_t *bckgr;
	mlx_image_t *collect;
	mlx_image_t *ex;
	mlx_texture_t *p;
	mlx_texture_t *w;
	mlx_texture_t *b;
	mlx_texture_t *c;
	mlx_texture_t *e;
	int	x;
	int y;
	int	moves;
	struct s_check	*check;
}		t_data;

void	so_long(t_data *data);
void	mlxfeest(t_data *data);
void	set_depth(t_data *data);
void	loopinstance(t_data *data, int depth, mlx_image_t *image);
void my_keyhook(mlx_key_data_t keydata, void* data);
void	checkposition(t_data *data);

char	*ft_rstrnstr(const char *haystack, const char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
char	*get_next_line(int	fd);

ssize_t	get_size(int fd);
char	**takemap(char **map, int fd);
void	checktype(char *file);
ssize_t	checkwidth(char **map);
void	findstart(t_data *data);
char **copymap(char **map);
void	findpath(t_data *data);
void	checkchars(t_check *check);
int	bcktrck(t_check *check, int x, int y);
int	checklength(char **map);
int	checkwalls(char **map, int width);
void	fatal(char *str);

void	freemap(char **maparray);
void	parsemap(t_data *data);
t_check *makecheck(void);

size_t	ft_strlen(const char *str);
char			*ft_strdup(const char *src);
void ft_putnbr_base(unsigned long num, unsigned long base, int cap);
void	ft_putchar_fd(char c, int fd);

//===========================TO DO==============================================

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void ft_putnbr_base(unsigned long num, unsigned long base, int cap)
{   
	if (num >= base)
	{
		ft_putnbr_base((num / base), base, cap);
        if (num % base < 10 && num >= 0)
		    ft_putchar_fd((num % base + 48), 1);
        else if (num % base > 9)
            ft_putchar_fd((num % base % 10 + cap), 1);
    }
    else if (num < base)
    {
	    if (num < 10 && num >= 0)
		    ft_putchar_fd((num + 48), 1);
        else if (num > 9)
            ft_putchar_fd((num % 10 + cap), 1);
    }
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

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

int	main(int argc, char *argv[])
{
	int		fd;
	t_check *check;
	t_data	*data;

	check = malloc(1 * sizeof(t_check));
	data = malloc(1 * sizeof(t_data));
	data->check = check;
	check->maparray = NULL;
	if (argc != 2)
	{
		ft_putstr_fd("wrong number of arguments", 2);
		exit(1);
	}
	checktype(argv[1]);
	fd = open(argv[1], O_RDONLY);
	check->height = get_size(fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	printf("height: %zd\n", check->height);
	check->maparray = malloc((check->height + 1)* sizeof(char *));
	check->maparray[check->height] = NULL;
	check->maparray = takemap(check->maparray, fd);
	close(fd);
	so_long(data);
	freemap(check->maparray);
}

ssize_t	get_size(int fd)
{
	char 	buf[100];
	ssize_t	rb;
	ssize_t	nl;
	size_t	i;

	nl = 1;
	rb = 1;
	i = 0;
	while (rb > 0)
	{
		rb = read(fd, buf, 100);
		while(i < rb && rb != -1)
		{
			if (buf[i] == '\n')
				nl++;
			i++;
		}
		i = 0;
	}
	printf("size map = %zd\n\n", nl);
	return (nl);
}

void	freemap(char **maparray)
{
	ssize_t	i;

	i = 0;
	while (maparray && maparray[i] != NULL)
	{
		free(maparray[i]);
		i++;
	}
	free(maparray);
}

char	**takemap(char **map, int fd)
{
	int i;
	int	check;

	i = 0;
	check = 1;
	//printf("%s", map[3]);
	while (check != 0)
	{
		map[i] = get_next_line(fd);
		if (map[i] == NULL)
			check = 0;
		//printf("%s", map[i]);
		i++;
	
	}
	// while (map[i] != NULL)
	// {
	// 	printf("%s", map[i]);
	// 	i++;
	// }
	return (map);
}

void	checktype(char *file)
{
	if (ft_rstrnstr(file, ".ber", 4) == NULL)
		fatal("so_long: invalid input file type\n");
}

void	fatal(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(1);
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

void	findstart(t_data *data)
{
	int x;
	int y;
	int p;

	x = 0;
	y = 0;
	p = 0;

	while (data->check->maparray[y] != NULL)
	{
		while (data->check->maparray[y][x] != '\n' && data->check->maparray[y][x] != '\0')
		{
			if (data->check->maparray[y][x] == 'P')
			{
				p++;
				data->check->start_x = x;
				data->check->start_y = y;
				data->x = x;
				data->y = y;
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (p != 1)
		fatal("wrong number of players");
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

void	findpath(t_data *data)
{
	findstart(data); //nog ff ingewikkeld
	data->check->mapcpy = copymap(data->check->maparray);
	write(1, "copymap\n", 9);
	checkchars(data->check);
	write(1, "checkchars\n", 12);
	if (bcktrck(data->check, data->check->start_x, data->check->start_y) == 0)
		fatal("invalid path");
	write(1, "hoi\n", 5);
	freemap(data->check->mapcpy);
}

void	checkchars(t_check *check)
{
	int	y;
	int	x;

	y = 0;
	check->collect = 0;
	check->player = 0;
	while (check->maparray && check->maparray[y] != NULL)
	{
		x = 0;
		while (check->maparray[y][x] == '1' || check->maparray[y][x] == '0' || \
		check->maparray[y][x] == 'P' || check->maparray[y][x] == 'C' || check->maparray[y][x] == 'E')
		{
			if (check->maparray[y][x] == 'C')
				check->collect++;
			if (check->maparray[y][x] == 'P')
				check->player++;
			if (check->maparray[y][x] == '1')
				check->wall++;
			if (check->maparray[y][x] == 'E')
				check->exit++;
			x++;
		}
		if (check->maparray[y][x] == '\n' || check->maparray[y][x] == '\0')
			y++;
		else
			fatal("invalid character in map");
	}
	if (check->collect == 0)
		fatal("no collectibles in map");
	if (check->exit != 1)
		fatal("wrong number of exits");
		check->cllct = check->collect;
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
	if (check->mapcpy[y][x] == '0' || check->mapcpy[y][x] == 'P' || check->mapcpy[y][x] == 'C' || check->mapcpy[y][x] == 'E')
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

void	so_long(t_data *data)
{
	int	i;
 
	i = 0;
	data->check->width = checkwidth(data->check->maparray);
	if (data->check->width == -1)
		fatal("invalid map size\n");
	if (checkwalls(data->check->maparray, data->check->width) == -1)
		fatal("map not closed");
	write(1, "waddup\n", 8);
	findpath(data);
	parsemap(data);
	mlxfeest(data);
}

t_check *makecheck(void)
{
	t_check *check2;

	check2 = malloc(1 * sizeof(t_check));
	check2->background = 0;
	check2->player = 0;
	check2->wall = 0;
	check2->collect = 0;
	check2->exit = 0;
	return (check2);
}

void	parsemap(t_data *data)
{
	int	x;
	int y;
	int **instmap;
	t_check *check2;

	x = 0;
	y = 0;
	instmap = malloc(data->check->height * sizeof(int *));
	while (data->check->maparray[y] != NULL)
	{
		instmap[y] = malloc(data->check->width * sizeof(int));
		y++;
	}
	y = 0;
	check2 = makecheck();
	while (data->check->maparray[y] != NULL)
	{
		while (x < data->check->width)
		{
			if (data->check->maparray[y][x] == '1')
				instmap[y][x] = check2->wall++;
			else if (data->check->maparray[y][x] == 'C')
				instmap[y][x] = check2->cllct++;
			else
				instmap[y][x] = 0;
			x++;
		}
		x = 0;
		y++;
	}
	data->check->instmap = instmap;
}

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_data *data;
	char **map;

	data = param;
	map = data->check->maparray;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		if (data->y != 0  && map[data->y - 1][data->x] != '1')
		{
			data->player->instances[0].y -= 64;
			data->y--;
			checkposition((t_data *)data);
		}
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		if (data->y != (data->check->height - 1) && map[data->y + 1][data->x] != '1')
		{
			data->player->instances[0].y += 64;
			data->y++;
			checkposition(data);
		}
	}

	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		if (data->x != 0 && map[data->y][data->x - 1] != '1')
		{
			data->player->instances[0].x -= 64;
			data->x--;
			checkposition(data);
		}
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		if (data->x != (data->check->width - 1) && map[data->y][data->x + 1] != '1')
		{
			data->player->instances[0].x += 64;
			data->x++;
			checkposition(data);
		}
	}
}

void	checkposition(t_data *data)
{
	int x;
	int y;
	char **map;
	int **map2;
	mlx_instance_t *inst;

	x = data->x;
	y = data->y;
	map = data->check->maparray;
	map2 = data->check->instmap;
	inst = &data->collect->instances[map2[y][x]];
	data->moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_base(data->moves, 10, 0);
	write(1, "\n", 1);
	if (map[y][x] == 'C')
	{
		if (map2[y][x] != -1)
		{
			mlx_set_instance_depth(inst, 0);
			map2[y][x] = -1;
			data->check->collect--;
		}
	}
	if (map[y][x] == 'E' && data->check->collect == 0)
		exit(0);

}

void	mlxfeest(t_data *data)
{
	// data->player = malloc(1 * (sizeof(mlx_image_t)));
	// data->wall = malloc(1 * (sizeof(mlx_image_t)));
	// data->ex = malloc(1 * (sizeof(mlx_image_t)));
	// data->bckgr = malloc(1 * (sizeof(mlx_image_t)));
	// data->collect = malloc(1 * (sizeof(mlx_image_t)));

	data->so_long = mlx_init((data->check->width * 64), (data->check->height * 64), "so_long", true);
	if (!data->so_long)
		exit(1);
	data->p = mlx_load_png("assets/barry_benson.png");
	//ft_memset(data->player->pixels, 0, (64*64));
	data->player = mlx_texture_to_image(data->so_long, data->p);
	
	data->w = mlx_load_png("assets/wall.png");
	//ft_memset(data->wall->pixels, 0, (64*64));
	data->wall = mlx_texture_to_image(data->so_long, data->w);
	
	data->c = mlx_load_png("assets/flower.png");
	//ft_memset(data->collect->pixels, 0, (64*64));
	data->collect = mlx_texture_to_image(data->so_long, data->c);
	
	data->e = mlx_load_png("assets/vanessa.png");
	//ft_memset(data->ex->pixels, 0, (64*64));
	data->ex = mlx_texture_to_image(data->so_long, data->e);
	
	data->b = mlx_load_png("assets/path.png");
	//ft_memset(data->bckgr->pixels, 0, (64*64));
	data->bckgr = mlx_texture_to_image(data->so_long, data->b);
	if(!data->p)
		exit(1);
	//	up = mlx_load_png("assets/rat_back.png");
	//	right = mlx_load_png("assets/rat_right.png");
	
	
	
	//mlx_image_to_window(data->so_long, data->wall, (0 * 64), (0 * 64));
	
	
	
	
	
	
	int x;
	int y;

	x = 0;
	y = 0;
	while (data->check->maparray[y] != NULL)
	{
		while (x < data->check->width)
		{
			if (data->check->maparray[y][x] == '1')
				mlx_image_to_window(data->so_long, data->wall, (x * 64), (y * 64));	
			else if (data->check->maparray[y][x] == 'C')
				mlx_image_to_window(data->so_long, data->collect, (x * 64), (y * 64));
			else if (data->check->maparray[y][x] == 'E')
				mlx_image_to_window(data->so_long, data->ex, (x * 64), (y * 64));
			else if (data->check->maparray[y][x] == 'P')
				mlx_image_to_window(data->so_long, data->player, (x * 64), (y * 64));
			mlx_image_to_window(data->so_long, data->bckgr, (x * 64), (y * 64));
			x++;
		}
		x = 0;
		y++;
	}
	data->moves = 0;
	set_depth(data);
	mlx_key_hook(data->so_long, &my_keyhook, data);
	mlx_loop_hook(data->so_long, &hook, data->so_long);
	mlx_loop(data->so_long);
	mlx_terminate(data->so_long);
	// (*mlx_keyfunc)(mlx_key_data_t keydata, void* param);

}

void	set_depth(t_data *data)
{
		loopinstance(data, 2, data->wall);
		loopinstance(data, 1, data->bckgr);
		loopinstance(data, 3, data->ex);
		loopinstance(data, 4, data->collect);
		loopinstance(data, 5, data->player);
}

void	loopinstance(t_data *data, int depth, mlx_image_t *image)
{
	int	i;

	i = 0;
	while (i < image->count)
	{
		mlx_set_instance_depth(&image->instances[i], depth);
		i++;
	}
}
//gcc main.c ../GNL/*.c MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit