/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/13 17:44:17 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_graph(t_map *map)
{
	t_graph	graph;
	t_rting rting;

	ft_bzero(&rting, sizeof(rting));
	ft_bzero(&graph, sizeof(graph));
	init_graph(&graph, map);
	init_map(map, &rting, &graph);
	start_raycasting(map, &graph, &rting);
	process_window(&graph);
}
