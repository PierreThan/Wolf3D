/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:46:34 by atyczyns          #+#    #+#             */
/*   Updated: 2019/12/04 15:33:33 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		init_ray(t_wolf *wolf, t_ray *ray, int x, double cam_x)
{
	t_vec2d	*tmp;

	cam_x = 2 * x / (double)WIDTH - 1;
	tmp = vec2d_scalar_mult(wolf->player.dir, cam_x);
	ray->dir.x += tmp->x;
	ray->dir.y += tmp->y;
	if (tmp)
		ft_memdel(tmp);
	ray->mapX = (int)wolf->player.pos.x;
	ray->mapY = (int)wolf->player.pos.y;
	ray->deltaDist.x = abs(1 / ray->dir.x);
	ray->deltaDist.y = abs(1 / ray->dir.y);
	ray->hit = 0;
	ray->stepX = (ray->dir.x > 0) - (ray->dir.x < 0);
	ray->stepY = (ray->dir.y > 0) - (ray->dir.y < 0);
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
		ray->hit = (wolf->map[ray->mapX][ray->mapY] > 0);
	}
}

void		draw_wall(t_wolf *wolf, t_ray *ray, t_wall *wall, int x)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - ray->pos.x + (ray->stepX < 0)) / ray->dir.x;
	else
		ray->perpWallDist = (ray->mapY - ray->pos.y + (ray->stepY) < 0) / ray->dir.y;
	wall->line_height = (int)(HEIGHT / ray->perpWallDist);
	wall->draw_start = FT_MAX(0, -wall->line_height / 2 + HEIGHT / 2);
	wall->draw_end = wall->line_height / 2 + HEIGHT / 2;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
	//PARTIE MLX
	//il faut rajouter a la structure wall un "ID" pour les murs ainsi que des couleur
	//et rajouter un fichier avec les BITMAP du mur, du sol et du ciel
	while (wall->draw_start < wall->draw_end)
		put_pxl_to_img(wolf, x, wall->draw_start++, wolf->color);
}

void		ray_casting(t_wolf *wolf)
{
	int		x;
	double	cam_x;
	t_ray	ray;
	t_wall	wall;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(wolf, &ray, x, cam_x);
		sending_laser_beam(wolf, &ray);
		draw_wall(wolf, &ray, &wall, x);
	}
}
