/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 20:18:38 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 03:14:57 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	load_pngs(t_data *data)
{
	data->p = mlx_load_png("assets/rat_front.png");
	if (!data->p)
		fatal("failed to load png");
	data->player = mlx_texture_to_image(data->so_long, data->p);
	data->w = mlx_load_png("assets/wall.png");
	if (!data->w)
		fatal("failed to load png");
	data->wall = mlx_texture_to_image(data->so_long, data->w);
	data->c = mlx_load_png("assets/collectible.png");
	if (!data->c)
		fatal("failed to load png");
	data->collect = mlx_texture_to_image(data->so_long, data->c);
	data->e = mlx_load_png("assets/exit.png");
	if (!data->e)
		fatal("failed to load png");
	data->ex = mlx_texture_to_image(data->so_long, data->e);
	data->b = mlx_load_png("assets/path.png");
	if (!data->b)
		fatal("failed to load png");
	data->bckgr = mlx_texture_to_image(data->so_long, data->b);
}

void	prcs_image(t_data *data, int x, int y)
{
	if (!data->bckgr || !data->collect || !data->player || \
	!data->wall || !data->ex)
		fatal("couldn't create image from texture");
	mlx_image_to_window(data->so_long, data->bckgr, (x * 64), (y * 64));
	if (data->check->maparray[y][x] == '1' && data->wall)
		mlx_image_to_window(data->so_long, data->wall, (x * 64), (y * 64));
	else if (data->check->maparray[y][x] == 'C' && data->collect)
		mlx_image_to_window(data->so_long, data->collect, (x * 64), (y * 64));
	else if (data->check->maparray[y][x] == 'E' && data->ex)
		mlx_image_to_window(data->so_long, data->ex, (x * 64), (y * 64));
	else if (data->check->maparray[y][x] == 'P' && data->player)
		mlx_image_to_window(data->so_long, data->player, (x * 64), (y * 64));
}

void	so_long(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->so_long = mlx_init((data->check->width * 64), \
	(data->check->height * 64), "so_long", true);
	if (!data->so_long)
		exit(1);
	set_null(data);
	load_pngs(data);
	while (data->check->maparray[y] != NULL)
	{
		while (x < data->check->width)
		{
			prcs_image(data, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	data->moves = 0;
	set_depth(data);
	loop(data);
}

void	loop(t_data *data)
{
	mlx_key_hook(data->so_long, &my_keyhook, data);
	mlx_loop_hook(data->so_long, &hook, data->so_long);
	mlx_loop(data->so_long);
	delete_all(data);
	mlx_terminate(data->so_long);
}

void	delete_all(t_data *data)
{
	delete_all_images(data);
	delete_all_textures(data);
}
