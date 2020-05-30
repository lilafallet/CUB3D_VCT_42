/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 10:20:42 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/30 10:53:29 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	moove_up_down(t_graph *gr)
{
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
	{
		gr->mv.new_posx = gr->mv.log & MV_UP ? gr->rting.posx + gr->rting.dirx
							* SPEED_MV : gr->rting.posx - gr->rting.dirx
							*SPEED_MV;
		gr->mv.new_posy = gr->mv.log & MV_UP ? gr->rting.posy + gr->rting.diry
							* SPEED_MV : gr->rting.posy - gr->rting.diry
							*SPEED_MV;
	}
	if (gr->mv.log & MV_UP && gr->mv.log & MV_DOWN)
	{
		gr->mv.new_posx = gr->rting.posx;
		gr->mv.new_posy = gr->rting.posy;
	}
}

static void	moove_left_right(t_graph *gr)
{
	if (gr->mv.log & MV_LEFT || gr->mv.log & MV_RIGHT)
	{
		gr->mv.new_posx = gr->mv.log & MV_RIGHT ? gr->rting.posx
							- gr->rting.diry * SPEED_MV : gr->rting.posx
							+ gr->rting.diry * SPEED_MV;
		gr->mv.new_posy = gr->mv.log & MV_RIGHT ? gr->rting.posy
							+ gr->rting.dirx * SPEED_MV : gr->rting.posy
							- gr->rting.dirx * SPEED_MV;
	}
	if (gr->mv.log & MV_LEFT && gr->mv.log & MV_RIGHT)
	{
		gr->mv.new_posx = gr->rting.posx;
		gr->mv.new_posy = gr->rting.posy;
	}
}

void	init_moove_look(t_graph *gr, t_map *map)
{
	gr->rting.posx = gr->mv.new_posx;
	gr->rting.posy = gr->mv.new_posy;
	init_graph(gr, map);
	process_window(gr);	
}

int	moove(t_graph *gr)
{
	t_map	*map;
	double	tmp_dirx;
	double	tmp_planecamx;
	
	if (gr->update == FALSE)
		return (SUCCESS);
	if (gr->mv.log & LOOK && gr->mv.log & MOOVE)
		gr->update = TRUE;
	else
		gr->update = FALSE;
	tmp_dirx = gr->rting.dirx;
	tmp_planecamx = gr->rting.planecamx;
	map = get_map(NULL);
	if (gr->mv.log & LK_RIGHT || gr->mv.log & LK_LEFT)
		gr->mv.log & LK_RIGHT ? look_right(gr, tmp_dirx, tmp_planecamx)
									: look_left(gr, tmp_dirx, tmp_planecamx);	
	if (gr->mv.log & MV_UP || gr->mv.log & MV_DOWN)
		moove_up_down(gr);
	if (gr->mv.log & MV_RIGHT || gr->mv.log & MV_LEFT)
		moove_left_right(gr);
	if (is_wall(gr, map) == FALSE)
		init_moove_look(gr, map);
	return (SUCCESS);
}
