/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 23:13:30 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 03:00:53 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	keyhook_up(char **map, t_data *data)
{
	if (data->y != 0 && map[data->y - 1][data->x] != '1')
	{
		data->player->instances[0].y -= 64;
		data->y--;
		checkposition((t_data *)data);
	}
}

void	keyhook_down(char **map, t_data *data)
{
	if (data->y != (data->check->height - 1) && \
	map[data->y + 1][data->x] != '1')
	{
		data->player->instances[0].y += 64;
		data->y++;
		checkposition(data);
	}
}

void	keyhook_left(char **map, t_data *data)
{
	if (data->x != 0 && map[data->y][data->x - 1] != '1')
	{
		data->player->instances[0].x -= 64;
		data->x--;
		checkposition(data);
	}
}

void	keyhook_right(char **map, t_data *data)
{
	if (data->x != (data->check->width - 1) && map[data->y][data->x + 1] != '1')
	{
		data->player->instances[0].x += 64;
		data->x++;
		checkposition(data);
	}
}

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}
