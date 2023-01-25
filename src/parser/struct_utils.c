/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 01:53:41 by mkootstr      #+#    #+#                 */
/*   Updated: 2023/01/25 03:01:36 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

t_check	*makecheck(void)
{
	t_check	*check2;

	check2 = malloc(1 * sizeof(t_check));
	check2->background = 0;
	check2->player = 0;
	check2->wall = 0;
	check2->collect = 0;
	check2->exit = 0;
	return (check2);
}

void	set_null(t_data *data)
{
	data->b = NULL;
	data->p = NULL;
	data->e = NULL;
	data->c = NULL;
	data->w = NULL;
	data->bckgr = NULL;
	data->player = NULL;
	data->ex = NULL;
	data->collect = NULL;
	data->wall = NULL;
}
