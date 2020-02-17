/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strucures.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:29:49 by pthan             #+#    #+#             */
/*   Updated: 2020/02/04 16:07:53 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define NB_TEXTURES 8

typedef struct		s_img
{
	int				size_l;
	int				bpp;
	int				endian;
	void			*ptr;
	int				*data;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
}					t_mlx;

typedef struct		s_vector2d
{
	double			x;
	double			y;
}					t_vec2d;

typedef struct		s_matrix2_2d
{
	double			a;
	double			b;
	double			c;
	double			d;
}					t_mat2d;

typedef struct		s_player
{
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			plane;
}					t_player;

typedef struct		s_ray
{
	int				mapx;
	int				mapy;
	int				hit;
	int				stepx;
	int				stepy;
	int				side;
	double			perpwalldist;
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			sidedist;
	t_vec2d			deltadist;
	t_vec2d			end_in_map;
}					t_ray;

typedef struct		s_wall
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			x_wall;
}					t_wall;

typedef struct		s_floor
{
	float			ray_dir_x0;
	float			ray_dir_y0;
	float			ray_dir_y1;
	float			ray_dir_x1;
	int				p;
	float			pos_z;;
	float			row_distance;
	float			floorstep_x;
	float			floorstep_y;
	float			floor_x;
	float			floor_y;
	int				cell_x;
	int				cell_y;
	int				t_x;
	int				t_y;
	int				floor_text;
	int				ceiling_text;
	unsigned int	color;
}					t_floor;

typedef struct		s_texture
{
	t_img			*img;
	int				width;
	int				height;
	int				x_text;
	int				y_text;
	int				text_num;
	int				d;
	int				h;
	int				y;
	unsigned int	color;
}					t_texture;

typedef struct		s_wolf
{
	int				fd;
	int				height;
	int				width;
	char			**map;
	double			move_speed;
	double			rot_speed;
	t_mlx			mlx;
	t_texture		texture;
	t_player		player;
	t_floor			floor;
}					t_wolf;

#endif
