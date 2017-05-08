/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_funcs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <vpailhe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 15:18:20 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/13 12:14:56 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				add_tail(t_map **alst, t_map *new)
{
	t_map		*l_ptr;

	l_ptr = *alst;
	while (l_ptr->nxt != NULL)
		l_ptr = l_ptr->nxt;
	if (l_ptr && new)
		l_ptr->nxt = new;
	return (1);
}

void			remap(t_map **map)
{
	t_map		*my_map;
	t_map		*alter;

	my_map = *map;
	alter = *map;
	alter = alter->nxt;
	while (my_map->nxt != NULL)
	{
		while (alter->array != my_map->array)
		{
			if (!(alter = alter->nxt))
				return ;
		}
		while (alter->array == my_map->array && my_map && my_map->eol == 0)
		{
			if (!(my_map->nxt) || !(alter->nxt))
				return ;
			if (alter->array == my_map->array)
				my_map->nxt_y = alter;
			my_map = my_map->nxt;
			alter = alter->nxt;
		}
		if (!(my_map = my_map->nxt))
			return ;
	}
}

t_map			*lst_eof(t_ref_value *ref)
{
	t_map		*new;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	free(ref);
	new->eol = 2;
	return (new);
}

t_map			*lst_eol(int value, int array, int line, t_display *display)
{
	t_map		*new;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	new->value = value;
	new->eol = 1;
	new->line = line;
	new->array = array;
	new->nxt = NULL;
	new->nxt_y = NULL;
	new->is_print = 0;
	xy_calculation(&new, display);
	return (new);
}

t_map			*lst_new(int value, int array, int line, t_display *display)
{
	t_map		*new;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	new->value = value;
	new->eol = 0;
	new->line = line;
	new->array = array;
	new->nxt = NULL;
	new->nxt_y = NULL;
	new->is_print = 0;
	xy_calculation(&new, display);
	return (new);
}
