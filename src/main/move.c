/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:16:01 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 04:36:44 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	char	**map;

	data = param;
	map = data->check->maparray;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		keyhook_up(map, data);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		keyhook_down(map, data);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		keyhook_left(map, data);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		keyhook_right(map, data);
}

void	checkposition(t_data *data)
{
	char			**map;
	int				**map2;
	mlx_instance_t	*inst;
	int				i;

	map = data->check->maparray;
	map2 = data->check->instmap;
	i = data->check->instmap[data->y][data->x];
	inst = &data->collect->instances[i];
	data->moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_base(data->moves, 10, 0);
	write(1, "\n", 1);
	if (map[data->y][data->x] == 'C')
	{
		if (map2[data->y][data->x] != -1)
		{
			mlx_set_instance_depth(inst, 0);
			map2[data->y][data->x] = -1;
			data->check->collect--;
		}
	}
	if (map[data->y][data->x] == 'E' && data->check->collect == 0)
		mlx_close_window(data->so_long);
}

void	set_depth(t_data *data)
{
	loopinstance(2, data->wall);
	loopinstance(1, data->bckgr);
	loopinstance(3, data->ex);
	loopinstance(4, data->collect);
	loopinstance(5, data->player);
}

void	loopinstance(int depth, mlx_image_t *image)
{
	int	i;

	i = 0;
	while (i < image->count)
	{
		mlx_set_instance_depth(&image->instances[i], depth);
		i++;
	}
}
