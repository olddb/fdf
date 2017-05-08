/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <vpailhe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 23:04:52 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/13 12:13:09 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_display			*create_display(void)
{
	t_display		display;
	t_display		*ptr_display;

	ptr_display = (t_display *)malloc(sizeof(display));
	display.base_x = 960;
	display.base_y = 100;
	ptr_display = &display;
	return (ptr_display);
}

int					expose_hook(t_env *e)
{
	draw_fdf(&(*e->map), e);
	return (0);
}

int					key_hook(int keycode, t_env *e)
{
	if (keycode == 65307)
	{
		draw_fdf(&(*e->map), e);
		exit(0);
	}
	return (0);
}

int					main(int argc, char **argv)
{
	static t_env	e;

	if (argc != 2)
		return (0);
	if (!(e.display = create_display()))
		return (0);
	if ((e.map = create_list(argv[1], e.display)) == NULL)
		return (0);
	if ((e.mlx = mlx_init()) == NULL)
		return (0);
	if ((e.win = mlx_new_window(e.mlx, 1920, 1080, "42")) == NULL)
		return (0);
	e.argv = argv[1];
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
