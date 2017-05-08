/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <vpailhe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 01:26:54 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/13 14:37:47 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				get_color(int crr_value, int nxt_value, int i)
{
	int			color;

	color = 0xFFFFFF;
	i = i * 10;
	if (crr_value > nxt_value)
		return (color -= (crr_value - nxt_value) * i);
	if (crr_value < nxt_value)
		return (color -= (crr_value + nxt_value) * i);
	else
		return (color -= (crr_value + nxt_value) * 10);
	return (color);
}

void			line(int start, int end, t_env e, t_pixel *pix)
{
	t_bresenham	b;
	int			i;

	i = 0;
	bresenham_maker(&b, pix);
	while (42)
	{
		mlx_pixel_put(e.mlx, e.win, pix->nxt_x, pix->nxt_y,
				get_color(start, end, i));
		i++;
		if (pix->nxt_x == pix->crr_x && pix->nxt_y == pix->crr_y)
			break ;
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			pix->nxt_x += -b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			pix->nxt_y += b.sy;
		}
	}
}

int				draw_x(t_map **my_map, t_env e)
{
	t_map		*next;
	t_map		*curr;
	t_pixel		pix;

	curr = *my_map;
	next = curr;
	while (next->nxt != NULL)
	{
		if (!(next = curr->nxt))
			return (0);
		if (next->nxt->eol == 2)
			return (0);
		if (next->eol == 1)
		{
			curr = curr->nxt->nxt;
			next = curr->nxt;
		}
		if (curr->is_print != 1 && next->is_print != 1)
		{
			pixel_maker(&pix, curr, next);
			line(pix.crr_value, pix.nxt_value, e, &pix);
		}
		curr = curr->nxt;
	}
	return (0);
}

int				draw_y(t_map **my_map, t_env e)
{
	t_map		*next;
	t_map		*curr;
	t_map		*ref;
	t_pixel		pix;

	curr = *my_map;
	next = curr->nxt_y;
	ref = *my_map;
	while (ref->eol == 0)
	{
		if (next && curr)
			if (next->is_print == 0 && curr->is_print == 0)
				if (pixel_maker(&pix, curr, next) == 1 && pix.nxt_y != 0)
					line(pix.crr_value, pix.nxt_value, e, &pix);
		if (!(curr = curr->nxt_y) || curr->nxt_y == NULL)
		{
			ref = ref->nxt;
			if (ref->eol != 0)
				return (0);
			curr = ref;
		}
		next = curr->nxt_y;
	}
	return (0);
}

int				draw_fdf(t_map *my_map, t_env *e)
{
	if (draw_x(&my_map, *e) == -1 || draw_y(&my_map, *e) == -1)
		return (-1);
	return (0);
}
