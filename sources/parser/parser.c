/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:24:23 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/10 22:39:03 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

static int	parser_resolution(t_vector *vct, t_state_machine *machine)
{
	t_vector	*resol;
	int			count_num;
	int			ret;
	t_vector	*cpy_vct;

	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	count_num = 0;
	resol = vct_splitchr(cpy_vct, 'R');
	ft_printf("PARSER_RESOLUTION\n"); //
	ft_printf("resol->str = %s\n", resol->str); //
	if (vct_apply(resol, IS_WHITESPACE) == FALSE)
	{
		ft_printf("RENTRES ICI\n");
		ret = is_next_or_error_resolution(resol);
		ft_printf("RET = %d\n\n", ret); //
		if (ret == NEXT)	
			machine->state = TEXTURE;
		if (ret == ERROR)
			machine->information |= ERROR_RESOLUTION;
		vct_del(&resol);
		vct_del(&cpy_vct);
		return (ret);
	}
	vct_del(&resol);
	ret = resolution_details(resol, machine->info.str_resolution, cpy_vct);
	if (ret & NEXT && ret & TRUE)
	{
		ft_printf("AJOUTE MACHINE\n"); //
		machine->state = TEXTURE;
		machine->information |= BT_RESOLUTION;
	}
	if (ret & TRUE)
		ft_printf("TRUE\n"); //
	if (ret & NEXT)
		ft_printf("NEXT\n\n"); //
	if (ret & ERROR)
	{
		machine->information |= ERROR_RESOLUTION;
		ft_printf("ERROR\n\n"); //
	}
	return (ret);
}

static int	parser_texture(t_vector *vct, t_state_machine *machine)
{
	size_t	i;
	int		first_index;
	int		ret;

	i = 0;
	ret = FALSE;
	ft_printf("PARSER_TEXTURE\n"); //
	ft_printf("vct->str = %s\n", vct->str); //
	/*while (str[i] != '\0')
	{
		if (str[i] == SPACE || str[i] == TAB)
			i++;
		if ((first_index = is_texture(str[i])) != FAILURE)
		{
			ret = process_texture(first_index, str, i, machine);
			return (ret);
		}
		i++;
	}*/
	machine->state = COLOR;
	return (ret);
}

static int			parser_color(t_vector *vct, t_state_machine *machine)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = FALSE;
	ft_printf("PARSER_COLOR\n"); //
	/*while (str[i] != '\0')
	{
		if (str[i] == CHAR_F_COLOR)
		{
			ret = hub_recup_color(str, i, machine, str[i], COLOR_F);
			if (ret == FAILURE)
				machine->information |= ERROR_COLOR;
			return (ret);
		}
		else if (str[i] == CHAR_C_COLOR)
		{
			ret = hub_recup_color(str, i, machine, str[i], COLOR_C);
			if (ret == FAILURE)
				machine->information |= ERROR_COLOR;
			return (ret);
		}
		i++;
	}*/
	machine->state = MAP;
	return (ret);
}

static int			parser_map(t_vector *vct, t_state_machine *machine)
{
	int				ret;
	static size_t	index = 0;
	int				position;

	ret = TRUE;
	ft_printf("PARSER_MAP\n"); //
	/*machine->info.str_map[index] = ft_memdup(str, ft_strlen(str));
	printf("machine->info.str_map[%lu] = %s\n", index, machine->info.str_map[index]); //
	position = what_position(machine->info.str_map[index],
								machine->info.str_position);
	printf("position = %d\n\n", position); //
	if (position != FAILURE)
		machine->information |= (unsigned long)((1 << position) << 20);
	index++;*/
	return (ret);
}

int			first_parser(t_state_machine *machine, t_vector *line)
{
	static t_function	function[4] = {parser_resolution, parser_texture,
										parser_color, parser_map};
	static int	nb_line = 1; //
	int			ret;
	int			i;

	ft_printf("FIRST PARSER\n"); //
	ft_printf("TEST LINE %d: %s\n\n", nb_line, line->str); //
	i = 0;
	ret = 0;
	if (line->len == 0)
	{
		ft_printf("LEN LINE = 0\n"); //
		nb_line++;
		//what_state(machine);
		return (LEN_ZERO);
	}
	while (i < NB_STATE)
	{
		ret = function[machine->state](line, machine);
		if (ret & ERROR)
			return (FAILURE);
		if (ret & NEXT)
			i++;
		else
			break ;
	}
	nb_line++; /*debug*/
	return (ret);
}
