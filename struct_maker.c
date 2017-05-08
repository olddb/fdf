/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <vpailhe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 00:35:26 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/13 12:57:15 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				pixel_maker(t_pixel *pix, t_map *curr, t_map *next)
{
	if (curr->is_print != 0 || next->is_print != 0)
		return (0);
	pix->crr_x = curr->x;
	pix->crr_y = curr->y;
	pix->nxt_x = next->x;
	pix->nxt_y = next->y;
	pix->crr_value = curr->value;
	pix->nxt_value = next->value;
	return (1);
}

void			bresenham_maker(t_bresenham *bre, t_pixel *pix)
{
	bre->dx = abs(pix->nxt_x - pix->crr_x);
	bre->sx = pix->crr_x < pix->nxt_x ? 1 : -1;
	bre->dy = abs(pix->nxt_y - pix->crr_y);
	bre->sy = pix->nxt_y < pix->crr_y ? 1 : -1;
	bre->err = (bre->dx > bre->dy ? bre->dx : -(bre->dy)) / 2;
}
