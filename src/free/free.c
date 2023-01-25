/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 00:56:56 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 04:36:34 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

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

void	free_grid(t_data *data)
{
	int	i;

	i = data->check->height - 1;
	while (data->check->instmap && i > -1 && data->check->instmap[i])
	{
		free(data->check->instmap[i]);
		i--;
	}
	free(data->check->instmap);
}

void	free_all(t_data *data)
{
	if (data->check->maparray)
		freemap(data->check->maparray);
	if (data->check->instmap)
		free_grid(data);
	free(data->check);
	free(data);
}

void	delete_all_images(t_data *data)
{
	if (data->bckgr)
		mlx_delete_image(data->so_long, data->bckgr);
	if (data->collect)
		mlx_delete_image(data->so_long, data->collect);
	if (data->player)
		mlx_delete_image(data->so_long, data->player);
	if (data->wall)
		mlx_delete_image(data->so_long, data->wall);
	if (data->ex)
		mlx_delete_image(data->so_long, data->ex);
}

void	delete_all_textures(t_data *data)
{
	if (data->b)
		mlx_delete_texture(data->b);
	if (data->c)
		mlx_delete_texture(data->c);
	if (data->p)
		mlx_delete_texture(data->p);
	if (data->w)
		mlx_delete_texture(data->w);
	if (data->e)
		mlx_delete_texture(data->e);
}
