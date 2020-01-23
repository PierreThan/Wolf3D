/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:46:34 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/23 14:44:12 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		init_ray(t_wolf *wolf, t_ray *ray, int x, double cam_x)
{
	cam_x = 2 * x / (double)(WIDTH) - 1;
	ray->dir.x = wolf->player.dir.x + wolf->player.plane.x * cam_x;
	ray->dir.y = wolf->player.dir.y + wolf->player.plane.y * cam_x;
	ray->mapX = (int)wolf->player.pos.x;
	ray->mapY = (int)wolf->player.pos.y;
	ray->pos.x = wolf->player.pos.x;
	ray->pos.y = wolf->player.pos.y;
	ray->deltaDist.x = sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	ray->deltaDist.y = sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
	ray->hit = 0;
	ray->stepX = (ray->dir.x >= 0) - (ray->dir.x < 0);
	ray->stepY = (ray->dir.y >= 0) - (ray->dir.y < 0);
	if (ray->dir.x < 0)
		ray->sideDist.x = (wolf->player.pos.x - ray->mapX) * ray->deltaDist.x;
	else
		ray->sideDist.x = (ray->mapX + 1.0 - wolf->player.pos.x) * ray->deltaDist.x;
	if (ray->dir.y < 0)
		ray->sideDist.y = (wolf->player.pos.y - ray->mapY) * ray->deltaDist.y;
	else
		ray->sideDist.y = (ray->mapY + 1.0 - wolf->player.pos.y) * ray->deltaDist.y;
}

void		sending_laser_beam(t_wolf *wolf, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (wolf->map[ray->mapX][ray->mapY] == '1')
			ray->hit = 1;
	}
}

void		init_wall(t_wolf *wolf, t_ray *ray, t_wall *wall)
{
	int		h;

	h = 400;
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - wolf->player.pos.x + (1 - ray->stepX) / 2 ) / ray->dir.x;
	else
		ray->perpWallDist = (ray->mapY - wolf->player.pos.y + (1 - ray->stepY) / 2) / ray->dir.y;
	wall->line_height = (int)((double)h / ray->perpWallDist);
	wall->draw_start = h / 2 - wall->line_height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = h / 2 + wall->line_height / 2;
	if (wall->draw_end >= h)
		wall->draw_end =  h - 1;
}

static void	textures(t_wolf *wolf, t_ray *ray, t_wall *wall, int x)
{
	//double	step;
	//double	text_pos;
	int		y;
	int		text_num;
	unsigned int	color;
	int				d;
	int				h;

	h = 400;
	text_num = wolf->map[ray->mapX][ray->mapY] - 49;
	if (ray->side == 0)
		wall->x_wall = wolf->player.pos.y + ray->perpWallDist * ray->dir.y;
	else
		wall->x_wall = wolf->player.pos.x + ray->perpWallDist * ray->dir.x;
	wall->x_wall -= floor((wall->x_wall));
	wolf->texture.x_text = (int)(wall->x_wall * (double)(TEXT_WIDTH));
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		wolf->texture.x_text = TEXT_WIDTH - wolf->texture.x_text - 1;
	y = wall->draw_start - 1;
	//step = 1.0 * TEXT_HEIGHT / wall->line_height;
	//text_pos = (wall->draw_start - 400 / 2 + wall->line_height / 2) * step;
	while (++y < wall->draw_end)
	{
		d = y * 256 - h * 128 + wall->line_height * 128;
		wolf->texture.y_text = ((d * TEXT_HEIGHT) / wall->line_height) / 256;
	//	wolf->texture.y_text = (int)text_pos & (TEXT_HEIGHT - 1);
	//	text_pos += step;

				/// changer le calcule de color pour prendre le pixel correspondant dans
				/// on a deja le bon x_text et y_text
				/// wolf->texture.data (precedement loader dans la fonction load_texture dans draw_textures.c)
				/// pour l'instant, on utilise une seule texture (il faut 1 structure texture par texture (duh))
				/// du coup, faut changer la structure de texture, et de wolf, pour mettre autant de textures qu'on veut
				/// idée : faire un tableau de t_textures dans wolf ?
		color = wolf->texture.text_map[text_num][TEXT_HEIGHT
				* wolf->texture.y_text + wolf->texture.x_text];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		wolf->mlx.img.data[y * WIDTH + x] = color;
	}
}
void		ray_casting(t_wolf *wolf)
{
	int		x;
	double	cam_x;
	t_ray	ray;
	t_wall	wall;

	x = -1;
	cam_x = 0.000;
	if (wolf->mlx.mlx_ptr && wolf->mlx.img.ptr)
		mlx_destroy_image(wolf->mlx.mlx_ptr, wolf->mlx.img.ptr);
	wolf->mlx.img.ptr =
		mlx_new_image(wolf->mlx.mlx_ptr, WIDTH, HEIGHT);
	wolf->mlx.img.data =
	(int *)mlx_get_data_addr(wolf->mlx.img.ptr, &(wolf->mlx.img.bpp),
					&(wolf->mlx.img.size_l), &(wolf->mlx.img.endian));
	while (++x < WIDTH)
	{
		init_ray(wolf, &ray, x, cam_x);
		sending_laser_beam(wolf, &ray);
		init_wall(wolf, &ray, &wall);
		textures(wolf, &ray, &wall, x);
	}
	mlx_put_image_to_window(wolf->mlx.mlx_ptr, wolf->mlx.win_ptr, wolf->mlx.img.ptr, 0, 0);
}
