/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:36:41 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 11:55:21 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "Libft/libft.h"

typedef struct s_check
{
	char	**maparray;
	char	**mapcpy;
	int		**instmap;
	ssize_t	height;
	ssize_t	width;
	int		collect;
	int		cllct;
	int		player;
	int		start_x;
	int		start_y;
	int		exit;
	int		wall;
	int		background;
}		t_check;

typedef struct s_data
{
	mlx_t			*so_long;
	mlx_image_t		*player;
	mlx_image_t		*wall;
	mlx_image_t		*bckgr;
	mlx_image_t		*collect;
	mlx_image_t		*ex;
	mlx_texture_t	*p;
	mlx_texture_t	*w;
	mlx_texture_t	*b;
	mlx_texture_t	*c;
	mlx_texture_t	*e;
	int				x;
	int				y;
	int				moves;
	struct s_check	*check;
}		t_data;

int		main(int argc, char *argv[]);
void	prep_data(t_data *data);

void	load_pngs(t_data *data);
void	prcs_image(t_data *data, int x, int y);
void	so_long(t_data *data);
void	loop(t_data *data);
void	delete_all(t_data *data);

void	my_keyhook(mlx_key_data_t keydata, void *param);
void	checkposition(t_data *data);
void	set_depth(t_data *data);
void	loopinstance(int depth, mlx_image_t *image);

void	keyhook_up(char **map, t_data *data);
void	keyhook_down(char **map, t_data *data);
void	keyhook_left(char **map, t_data *data);
void	keyhook_right(char **map, t_data *data);
void	hook(void *param);

char	**copymap(char **map);
char	**takemap(char **map, int fd);
void	parsemap(t_data *data);
void	count_w_c(t_data *data, int **instmap);

void	findpath(t_data *data);
void	findstart(t_data *data);
int		bcktrck(t_check *check, int x, int y);

void	checkchars(t_check *check);
int		checklength(char **map);
int		checkwalls(char **map, int width);
ssize_t	checkwidth(char **map);
void	checktype(char *file);

void	freemap(char **maparray);
void	free_grid(t_data *data);
void	free_all(t_data *data);
void	delete_all_images(t_data *data);
void	delete_all_textures(t_data *data);

ssize_t	get_size(int fd);
void	count_chars(t_check *check, int x, int y);
void	save_start(t_data *data, int x, int y);

t_check	*makecheck(void);
void	set_null(t_data *data);

void	fatal(char *str);
int		ft_open(char *str);
int		ft_close(int fd);
void	*ft_malloc(size_t size);

#endif