/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strucures.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:29:49 by pthan             #+#    #+#             */
/*   Updated: 2019/12/04 15:59:12 by atyczyns         ###   ########.fr       */
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

typedef struct	s_ray
{
	int			mapX;
	int			mapY;
	int			hit;
	int			stepX;
	int			stepY;
	int			side;
	double		perpWallDist;
	t_vec2d		pos;
	t_vec2d		dir;
	t_vec2d		sideDist;
	t_vec2d		deltaDist;
	t_vec2d		end_in_map;
}				t_ray;

typedef struct	s_wall
{
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_wall;

typedef struct	s_texture
{
	void		*img;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_texture;

typedef struct	s_wolf
{
	t_texture	texture;
	int			x_texture;
	int			y_texture;
	int			color;
	int			fd;
	int			height;
	int			width;
	char		**map;
	double		move_speed;
	double		rot_speed;
    t_player    player;
	t_mlx		mlx;
}				t_wolf;

#endif
