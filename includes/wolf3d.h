/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:50:40 by pthan             #+#    #+#             */
/*   Updated: 2019/11/18 17:50:43 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "key_macos.h"
# include "structures.h"
# include <stdlib.h>
# include <mlx.h>

# define WIDTH 1200
# define HEIGHT 900
# define WHITE 0xFFFFFF
# define BLUE 0x1152CB

// https://lodev.org/cgtutor/raycasting.html
// https://zestedesavoir.com/tutoriels/1014/utiliser-la-sdl-en-langage-c/la-sdl/#1-presentation-de-la-sdl
// http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting/theorie/01-introduction
// https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/

typedef struct	s_wolf
{
	int			fd;
	int			height;
	int			width;
	char		**map;
    t_player    player;
	t_mlx		mlx;
}				t_wolf;

/*
**		input_check.c
*/
int				parse_file(t_wolf *wolf, char **argv);

/*
**		mlx.c
*/
void			ft_display_window(char *title, t_wolf *wolf);
void			setup_controls(t_wolf *wolf);

/*
**		vector2d.c
*/
t_vec2d			*vec2d_scalar_mult(t_vec2d a, double l);
double			vect2d_dot(t_vec2d a, t_vec2d b);
t_vec2d			*vec2d_sum(t_vec2d a, t_vec2d b);
void			vec2d_normalize(t_vec2d *vect);
void			vec2d_mat2d_mult(t_vec2d *vec, t_mat2d *mat);

/*
int				key_press(int key, void *param);
int				mouse_press(int button, int x, int y, void *param);
void			ft_display_window(t_mlx *mlx, char *title,
									int img_width, int img_height);
void			point_to_img(t_wolf *wolf, int x, int y, int color);
void			setup_controls(t_wolf *wolf);
*/

#endif