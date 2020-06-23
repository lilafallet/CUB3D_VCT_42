/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:53:10 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/23 12:40:39 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> /*DEBUG*/

int			is_good_file(char *str)
{
	size_t	len;
	int		ret;

	ret = SUCCESS;
	len = ft_strlen(str);
	if (len <= 4)
		ret = FAILURE;
	if (ret != FAILURE)
	{
		if (ft_strequ(str + len - 4, ".cub") == FALSE)
			ret = FAILURE;
	}
	if (ret == FAILURE)
		printf_errors(ERR_FORMAT, 0, NULL);
	return (ret);
}

int			parser_savemode(char *argument, t_map *map)
{
	if (ft_strequ(argument, "--save") == FALSE)
	{
		map->utils.save_mode = FALSE;
		printf_errors(ERR_SAVE, 0, NULL);
		return (FAILURE);
	}	
	map->utils.save_mode = TRUE;
	return (SUCCESS);
}

static void	not_map(unsigned long flag, unsigned long nb_line, t_vector *line)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (flag == ERR_ARG_LITTLE)
		ft_dprintf(STDERR_FILENO,"%s", ERROR_ARGUMENTS_LITTLE);
	else if (flag == ERR_GLOBAL)
	{
		ft_dprintf(STDERR_FILENO, "[line %ld]: ", nb_line);
		vct_print_fd(line, STDERR_FILENO);
		ft_dprintf(STDERR_FILENO, " -> %s", ERROR_STR_GLOBAL);
	}
	else if (flag == ERR_FORMAT)
		ft_dprintf(STDERR_FILENO,"%s", ERROR_ARGUMENT_FORMAT);
	else if (flag == ERR_SAVE)
		ft_dprintf(STDERR_FILENO,"%s", ERROR_SAVE);
	else if (flag == ERR_ARG_BIG)
		ft_dprintf(STDERR_FILENO,"%s", ERROR_ARGUMENTS_BIG);
}

void		printf_errors(unsigned long flag, unsigned long nb_line, t_vector *line)
{
	const char		*error[NB_ERROR] = {ERR1, ERR2, ERR3, ERR4, ERR5, ERR6,
										ERR7, ERR8, ERR9, ERR10, ERR11, ERR12,
										ERR13};
	unsigned long	index;
	size_t			i;
	static size_t	loops_function = 0;
	
	i = 0;
	//vct_print(line);
	if (loops_function != 0)
		return ;
	if (flag == ERR_ARG_LITTLE || flag == ERR_SAVE || flag == ERR_FORMAT
		|| flag == ERR_GLOBAL || flag == ERR_ARG_BIG)
		not_map(flag, nb_line, line);
	index = flag >> 24;
	while (i < NB_ERROR)
	{
		if (index & (1 << i))
		{
			ft_dprintf(STDERR_FILENO, "Error\n");
			if (line != NULL && nb_line != 0)
			{
				ft_dprintf(STDERR_FILENO, "[line %ld]: ", nb_line);
				vct_print_fd(line, STDERR_FILENO);
				ft_dprintf(STDERR_FILENO, " -> ");
			}
			ft_dprintf(STDERR_FILENO, "%s", error[i]);
		}
		i++;
	}
	loops_function++;
}
