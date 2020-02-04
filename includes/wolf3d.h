/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:50:40 by pthan             #+#    #+#             */
/*   Updated: 2020/02/04 16:16:02 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include <fcntl.h>
# include "key_macos.h"
# include "structures.h"
# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <mlx.h>

# define WIDTH 640
# define HEIGHT 400
# define WHITE 0xFFFFFF
# define BLUE 0x1152CB
# define TEXT_HEIGHT 64
# define TEXT_WIDTH 64

/*
** https://lodev.org/cgtutor/raycasting.html
** http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/
**                  affichage/3d/raycasting/theorie/01-introduction
** https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
*/

/*
**		main.c
*/

int				free_wolf(t_wolf *wolf);
int				close_wolf(void *param);

/*
**		textures.c
*/

void			init_texture(t_wolf *wolf);
void            free_texture(t_wolf *wolf);
void			floor_ceiling(t_wolf *wolf);

/*
**		input_check.c
*/

int				init_player(t_wolf *wolf);
int				parse_file(t_wolf *wolf, char **argv);

/*
**		mlx.c
*/

int				ft_display_window(char *title, t_wolf *wolf);
void			setup_controls(t_wolf *wolf);

/*
**		vector2d.c
*/

t_vec2d			*vec2d_scalar_mult(t_vec2d a, double l);
double			vect2d_dot(t_vec2d a, t_vec2d b);
t_vec2d			*vec2d_sum(t_vec2d a, t_vec2d b);
void			vec2d_normalize(t_vec2d *vect);
void			vec2d_mat2d_mult(t_vec2d *vec, t_mat2d *mat);

void			ray_casting(t_wolf *wolf);

/*
**int				key_press(int key, void *param);
**int				mouse_press(int button, int x, int y, void *param);
**int				ft_display_window(t_mlx *mlx, char *title,
**									int img_width, int img_height);
**void			point_to_img(t_wolf *wolf, int x, int y, int color);
**void			setup_controls(t_wolf *wolf);
*/

#endif
