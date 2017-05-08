/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <vpailhe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 17:54:39 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/13 12:54:53 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int				create_tab(t_ref_value *ref, int fd, int *max)
{
	int			i;
	int			rtn;
	char		*line;
	char		**tab_char;

	i = 0;
	if ((rtn = get_next_line(fd, &line)) <= 0)
		return (-1);
	if (ft_strlen(line) <= 1)
		return (-1);
	if (!(tab_char = ft_strsplit(line, ' ', &ref->nb_array)))
		return (-1);
	if (ref->nb_array < 1)
		return (-1);
	if (!(ref->tab = (int *)malloc(sizeof(ref->tab) * ref->nb_array)))
		return (-1);
	if (!*max || *max < ref->nb_array)
		*max = ref->nb_array;
	while (i < ref->nb_array)
	{
		ref->tab[i] = ft_atoi(tab_char[i]);
		i++;
	}
	return (rtn);
}

t_map			*create_map(int fd, t_display *display, int *max)
{
	int			i;
	int			j;
	int			tmp_max;
	t_map		*my_map;
	t_ref_value	*ref;

	i = 1;
	j = 0;
	ref = (t_ref_value *)malloc(sizeof(ref));
	if ((ref->rtn = create_tab(*(&ref), fd, &tmp_max)) == -1)
		return (NULL);
	my_map = lst_new(ref->tab[0], 0, 0, display);
	ref->nb_array -= 1;
	while (ref->rtn > 0)
	{
		while (ref->nb_array-- > 0)
			i += add_tail(&my_map, lst_new(ref->tab[i], i, j, display));
		add_tail(&my_map, lst_eol(0, i, j, display));
		i = 0;
		j++;
		ref->rtn = create_tab(*(&ref), fd, &tmp_max);
	}
	add_tail(&my_map, lst_eof(ref));
	*max = tmp_max;
	return (my_map);
}

t_map			*create_list(char *file, t_display *display)
{
	t_map		*my_map;
	int			fd;
	int			max;

	fd = open(file, 0);
	if (fd < 0)
		return (NULL);
	if ((my_map = create_map(fd, display, &max)) == NULL)
		return (NULL);
	fill_x(&my_map, max);
	remap(&my_map);
	close(fd);
	return (my_map);
}

void			xy_calculation(t_map **my_map, t_display *display)
{
	t_map		*l_ptr;

	l_ptr = *my_map;
	l_ptr->array = l_ptr->array * 20;
	l_ptr->line = l_ptr->line * 20;
	if (l_ptr && l_ptr->eol == 0)
	{
		l_ptr->x = ((sqrt(2) / 2) * (l_ptr->array - l_ptr->line))
			+ display->base_x;
		l_ptr->y = ((1 / sqrt(6) * (l_ptr->line + l_ptr->array)) -
				((sqrt(2) / 3) * (l_ptr->value * 3))) + display->base_y;
	}
}
