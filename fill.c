/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 00:26:49 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/13 14:47:35 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map		*lst_blank(int array)
{
	t_map	*new;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	new->value = 0;
	new->eol = 0;
	new->line = 0;
	new->array = (((array + 1) * 20) - 20);
	new->nxt = NULL;
	new->nxt_y = NULL;
	new->is_print = 1;
	return (new);
}

void		fill_x(t_map **map, int max)
{
	t_map	*curr;
	t_map	*new;
	int		array;

	curr = *map;
	array = 0;
	max -= 2;
	while (curr->nxt)
	{
		array = curr->eol == 1 ? 0 : array;
		curr = curr->eol == 1 ? curr->nxt : curr;
		if (!curr->nxt || curr->eol == 2)
			break ;
		curr = curr->nxt;
		array++;
		if (curr->nxt->eol != 0)
			while ((array - 1) < max)
			{
				new = lst_blank(array + 1);
				new->nxt = curr->nxt;
				curr->nxt = new;
				curr = curr->nxt;
				array++;
			}
	}
}
