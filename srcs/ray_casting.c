/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:46:34 by atyczyns          #+#    #+#             */
/*   Updated: 2019/12/04 16:06:22 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		init_ray(t_wolf *wolf, t_ray *ray, int x, double cam_x)
{
	double	tmp;

	tmp = 2.0 * (double)x / (double)WIDTH;
//	ft_printf("[1] x = [%d], tmp = [%f]\n", x, tmp);
	cam_x = -1.0 + tmp;
	//ft_printf("[1] x = [%d], cam_x = [%f]\n", x, cam_x);
	//ft_printf("[2] x = [%d], cam_x = [%f]\n", x, cam_x);
	ft_printf("[3] x = [%d], cam_x = [%f]\n", x, cam_x);
	ray->dir.x = wolf->player.dir.x + wolf->player.plane.x * cam_x;
	ray->dir.y = wolf->player.dir.y + wolf->player.plane.y * cam_x;
//	ft_printf("[1]ray->dir.x/y = (%f, %f)\n", ray->dir.x, ray->dir.y);
//	ft_printf("x = [%d], pos.x = [%f], pos.y = [%f]\n", x, wolf->player.pos.x, wolf->player.pos.y);
	ray->mapX = (int)wolf->player.pos.x;
	ray->mapY = (int)wolf->player.pos.y;
//	ft_printf("ray->mapX = [%d], ray->mapY = [%d]\n", ray->mapX, ray->mapY);
	ray->pos.x = wolf->player.pos.x;
	ray->pos.y = wolf->player.pos.y;
//	ft_printf("[1]ray->mapX/Y = (%d, %d)\n", ray->mapX, ray->mapY);
//	ft_printf("posX/Y = %f, %f\n", ray->pos.x, ray->pos.y);
	ray->deltaDist.x = fabs(1.0 / ray->dir.x);
	ray->deltaDist.y = fabs(1.0 / ray->dir.y);
//	ft_printf("[1]ray->deltaDist.x/y = (%f, %f)\n", ray->deltaDist.x, ray->deltaDist.y);
	ray->hit = 0;
	ray->stepX = (ray->dir.x >= 0) - (ray->dir.x < 0);
	ray->stepY = (ray->dir.y >= 0) - (ray->dir.y < 0);
//	ft_printf("[1]ray->stepX/Y = (%d, %d)\n", ray->stepX, ray->stepY);
	if (ray->dir.x < 0)
		ray->sideDist.x = (wolf->player.pos.x - ray->mapX) * ray->deltaDist.x;
	else
		ray->sideDist.x = (ray->mapX + 1.0 - wolf->player.pos.x) * ray->deltaDist.x;
	if (ray->dir.y < 0)
		ray->sideDist.y = (wolf->player.pos.y - ray->mapY) * ray->deltaDist.y;
	else
		ray->sideDist.y = (ray->mapY + 1.0 - wolf->player.pos.y) * ray->deltaDist.y;
	//ft_printf("[1]ray->sideDist.x/y = (%f, %f)\n", ray->sideDist.x, ray->sideDist.y);
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
		if (ray->mapX < wolf->width && ray->mapY < wolf->height)
		{
			//ft_printf("[1]ray->mapX/Y = (%d, %d)\n", ray->mapX, ray->mapY);
			if (wolf->map[ray->mapX][ray->mapY] == '1')
			{
				ray->hit = 1;
			//	ft_printf("ray->hit = 1\n");
			}
		}
		else
		{
			//ft_printf("bord de map atteint\n");
			break;
		}
		
	}
}

void		draw_wall(t_wolf *wolf, t_ray *ray, t_wall *wall, int x)
{
	int	h;

	h = 400;
//	ft_printf("x = [%d], ray->side = [%d]\n", x, ray->side);
	if (ray->side == 0)
	{
//		ft_printf("ray->mapX = [%d], player.pos.x = [%f], ray->stepX = [%d], ray->dir.x = [%f]\n", ray->mapX, wolf->player.pos.x, ray->stepX, ray->dir.x);
		ray->perpWallDist = (ray->mapX - wolf->player.pos.x + (1 - ray->stepX) / 2 ) / ray->dir.x;
	}
	else
	{
//		ft_printf("ray->mapY = [%d], player.pos.y = [%f], ray->stepY = [%d], ray->dir.y = [%f]\n", ray->mapY, wolf->player.pos.y, ray->stepY, ray->dir.y);
		ray->perpWallDist = (ray->mapY - wolf->player.pos.y + (1 - ray->stepY) / 2) / ray->dir.y;
	}
	//ft_printf("perpWallDist = %f\n", ray->perpWallDist);
	wall->line_height = (int)((double)h / ray->perpWallDist);
	//ft_printf("line_height = %d\n", wall->line_height);
	wall->draw_start = h / 2 - wall->line_height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = h / 2 + wall->line_height / 2;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end =  h - 1;
	//ft_printf("colonne de pixel x = %d : start/end = [%d][%d] allumé\n", x, wall->draw_start, wall->draw_end);
	while (wall->draw_start < wall->draw_end)
	{
		if (wall->draw_start > 0 && wall->draw_start < HEIGHT)
			if (x > 0 && x < WIDTH)
				wolf->mlx.img.data[wall->draw_start * WIDTH + x] = 145630;
		wall->draw_start++;
	}
	//PARTIE MLX
	/*il faut rajouter a la structure wall un "ID" pour les murs ainsi que des couleur
	et rajouter un fichier avec les BITMAP du mur, du sol et du ciel
	
	il faut initier wolf->x_texture ici
	
	while (wall->draw_start < wall->draw_end)
		put_pxl_to_img(wolf, x, wall->draw_start++, wolf->color);
	*/
}

void		ray_casting(t_wolf *wolf)
{
	int		x;
	double	cam_x;
	t_ray	ray;
	t_wall	wall;

	x = -1;
	cam_x = 0.000;
	while (++x < WIDTH)
	{
		init_ray(wolf, &ray, x, cam_x);
/*		ft_printf("[2] cam_x = %f\n", cam_x);
		ft_printf("[2]ray->dir.x/y = (%f, %f)\n", ray.dir.x, ray.dir.y);
		ft_printf("[2]ray->mapX/Y = (%d, %d)\n", ray.mapX, ray.mapY);
		ft_printf("[2]ray->deltaDist.x/y = (%f, %f)\n", ray.deltaDist.x, ray.deltaDist.y);
		ft_printf("[2]ray->stepX/Y = (%d, %d)\n", ray.stepX, ray.stepY);
		ft_printf("[2]ray->sideDist.x/y = (%f, %f)\n", ray.sideDist.x, ray.sideDist.y);
*/		sending_laser_beam(wolf, &ray);
		if (ray.hit == 0)
		{
			ft_printf("\tray casting : x = %d\n", x);
			ft_printf("[2]ray.hit = %d\n", ray.hit);
		}
		draw_wall(wolf, &ray, &wall, x);
	}
	mlx_put_image_to_window(wolf->mlx.mlx_ptr, wolf->mlx.win_ptr, wolf->mlx.img.ptr, 0, 0);
}
