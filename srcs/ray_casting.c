/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:46:34 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/17 15:22:19 by atyczyns         ###   ########.fr       */
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

static int	direction(t_wolf *wolf, t_ray *ray, t_wall *wall)
{
	(void)wolf;
	(void)wall;
	if (ray->side == 0)
	{
		
		if (ray->dir.x > 0)
			return (10100000);
		else
			return (12100000);
		/*
		wall->x_wall = wolf->player.pos.y + ray->perpWallDist * ray->dir.y;
		wall->x_wall -= floor((wall->x_wall));
		wolf->texture.x_text = wall->x_wall * WIDTH;
		if (ray->dir.x > 0)
			return (wolf->texture.text_map[1][WIDTH - wolf->texture.x_text - 1]);
		else
			return (wolf->texture.text_map[1][wolf->texture.x_text]);*/
	}
	/*wall->x_wall = wolf->player.pos.x + ray->perpWallDist * ray->dir.x;
	wall->x_wall -= floor((wall->x_wall));
	wolf->texture.x_text = wall->x_wall + WIDTH;
	return (wolf->texture.text_map[1][wolf->texture.x_text]);*/
	return (11100000);
}

void		draw_wall(t_wolf *wolf, t_ray *ray, t_wall *wall, int x)
{
	int	h;

	h = 400;
//	init_texture(wolf);
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
	while (wall->draw_start < wall->draw_end)
	{
		if (wall->draw_start > 0 && wall->draw_start < HEIGHT)
			if (x > 0 && x < WIDTH)
				wolf->mlx.img.data[wall->draw_start * WIDTH + x] = direction(wolf, ray, wall);
		wall->draw_start++;
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
		draw_wall(wolf, &ray, &wall, x);
	}
	mlx_put_image_to_window(wolf->mlx.mlx_ptr, wolf->mlx.win_ptr, wolf->mlx.img.ptr, 0, 0);

}
