/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strucures.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:29:49 by pthan             #+#    #+#             */
/*   Updated: 2019/11/15 13:29:52 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_img
{
	int			size_l;
	int			bpp;
	int			endian;
	void		*ptr;
	int			*data;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_mlx;

typedef struct	s_vector2d
{
	double		x;
	double		y;
}				t_vec2d;

typedef struct s_matrix2_2d
{
	double		a;
	double		b;
	double		c;
	double		d;
}				t_mat2d;

typedef struct	s_player
{
	t_vec2d		pos;
	t_vec2d		dir;
	t_vec2d		plane;
}				t_player;

#endif
