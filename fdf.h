/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <vpailhe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 17:42:57 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/13 14:47:11 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stddef.h>
# include <mlx.h>
# include "get_next_line.h"

typedef struct		s_map
{
	int				value;
	int				x;
	int				y;
	int				array;
	int				line;
	int				eol;
	int				is_print;
	struct s_map	*nxt;
	struct s_map	*nxt_y;
}					t_map;

typedef struct		s_ref_value
{
	int				rtn;
	int				nb_array;
	int				*tab;
}					t_ref_value;

typedef struct		s_display{
	int				base_x;
	int				base_y;
}					t_display;

typedef	struct		s_env{
	void			*mlx;
	void			*win;
	char			*argv;
	t_map			*map;
	t_display		*display;
}					t_env;

typedef struct		s_bresenham{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_bresenham;

typedef	struct		s_pixel{
	int				crr_x;
	int				crr_y;
	int				nxt_x;
	int				nxt_y;
	int				crr_value;
	int				nxt_value;
}					t_pixel;

int					add_tail(t_map **alst, t_map *new);
void				xy_calculation(t_map **my_map, t_display *display);
void				remap(t_map **map);
t_map				*lst_new(int value, int array, int line, t_display
					*display);
t_map				*lst_eol(int value, int array, int line, t_display
					*display);
t_map				*lst_eof(t_ref_value *ref);

int					draw_x(t_map **my_map, t_env e);
int					draw_y(t_map **my_map, t_env e);
int					draw_fdf(t_map *my_map, t_env *e);

int					create_tab(t_ref_value *ref, int fd, int *max);
t_map				*create_map(int fd, t_display *display, int *max);
t_map				*create_list(char *file, t_display *display);

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strlen(const char *s);
char				*ft_strncpy(char *dst, const char *src, int n);

unsigned int		ft_tablen(const char *s, char c);
unsigned int		ft_wordlen(const char *s, char c);
char				*ft_strndup(const char *s1, size_t n);
char				**ft_strsplit(const char *s, char c, int *p);

void				ft_putstr(char *str);
t_display			*create_display();

int					pixel_maker(t_pixel *pix, t_map *curr, t_map *next);
void				bresenham_maker(t_bresenham *bre, t_pixel *pix);

void				fill_x(t_map **map, int max);
void				add_blank(t_map *curr, int array);

#endif
