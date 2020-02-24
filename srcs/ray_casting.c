/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:46:34 by atyczyns          #+#    #+#             */
/*   Updated: 2020/02/20 16:54:06 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		init_ray(t_wolf *wolf, t_ray *ray, int x, double cam_x)
{
	cam_x = 2 * x / (double)(WIDTH) - 1;
	ray->dir.x = wolf->player.dir.x + wolf->player.plane.x * cam_x;
	ray->dir.y = wolf->player.dir.y + wolf->player.plane.y * cam_x;
	ray->mapx = (int)wolf->player.pos.x;
	ray->mapy = (int)wolf->player.pos.y;
	ray->pos.x = wolf->player.pos.x;
	ray->pos.y = wolf->player.pos.y;
	ray->deltadist.x = sqrt(1 + (ray->dir.y * ray->dir.y)
		/ (ray->dir.x * ray->dir.x));
	ray->deltadist.y = sqrt(1 + (ray->dir.x * ray->dir.x)
		/ (ray->dir.y * ray->dir.y));
	ray->hit = 0;
	ray->stepx = (ray->dir.x >= 0) - (ray->dir.x < 0);
	ray->stepy = (ray->dir.y >= 0) - (ray->dir.y < 0);
	if (ray->dir.x < 0)
		ray->sidedist.x = (wolf->player.pos.x - ray->mapx) * ray->deltadist.x;
	else
		ray->sidedist.x = (ray->mapx + 1.0 - wolf->player.pos.x)
			* ray->deltadist.x;
	if (ray->dir.y < 0)
		ray->sidedist.y = (wolf->player.pos.y - ray->mapy) * ray->deltadist.y;
	else
		ray->sidedist.y = (ray->mapy + 1.0 - wolf->player.pos.y)
			* ray->deltadist.y;
}

void		sending_laser_beam(t_wolf *wolf, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (wolf->map[ray->mapx][ray->mapy] != '0')
			ray->hit = 1;
	}
}

void		init_wall(t_wolf *wolf, t_ray *ray, t_wall *wall)
{
	int		h;

	h = 480;
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - wolf->player.pos.x
			+ (1 - ray->stepx) / 2) / ray->dir.x;
	else
		ray->perpwalldist = (ray->mapy - wolf->player.pos.y
			+ (1 - ray->stepy) / 2) / ray->dir.y;
	wall->line_height = (int)((double)h / ray->perpwalldist);
	wall->draw_start = h / 2 - wall->line_height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = h / 2 + wall->line_height / 2;
	if (wall->draw_end >= h)
		wall->draw_end = h - 1;
}

static void	textures(t_wolf *wolf, t_ray *ray, t_wall *wall, int x)
{
	wolf->texture.h = 480;
	wolf->texture.text_num = wolf->map[ray->mapx][ray->mapy] - 49;
	if (ray->side == 0)
		wall->x_wall = wolf->player.pos.y + ray->perpwalldist * ray->dir.y;
	else
		wall->x_wall = wolf->player.pos.x + ray->perpwalldist * ray->dir.x;
	wall->x_wall -= floor((wall->x_wall));
	wolf->texture.x_text = (int)(wall->x_wall * (double)(TEXT_WIDTH));
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		wolf->texture.x_text = TEXT_WIDTH - wolf->texture.x_text - 1;
	wolf->texture.y = wall->draw_start - 1;
	while (++wolf->texture.y < wall->draw_end)
	{
		wolf->texture.d = wolf->texture.y * 256
			- wolf->texture.h * 128 + wall->line_height * 128;
		wolf->texture.y_text = ((wolf->texture.d * TEXT_HEIGHT)
			/ wall->line_height) / 256;
		wolf->texture.color =
			wolf->texture.img[wolf->texture.text_num].data[TEXT_HEIGHT
				* wolf->texture.y_text + wolf->texture.x_text];
		if (ray->side == 1)
			wolf->texture.color = (wolf->texture.color >> 1) & 8355711;
		wolf->mlx.img.data[wolf->texture.y * WIDTH + x] = wolf->texture.color;
	}
}

/*
** changer le calcule de color pour prendre le pixel correspondant dans le xml
** wolf->texture.data (prec. loader ds la fnc load_texture ds draw_textures.c)
** pour l'instant, on utilise une seule tex (il faut 1 struct tex par tex)
** du coup, faut changer les struct tex et wolf,
** pour mettre le nb de tex quon veut
** idée : faire un tableau de t_textures dans wolf ?
*/

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
	floor_ceiling(wolf);
	while (++x < WIDTH)
	{
		init_ray(wolf, &ray, x, cam_x);
		sending_laser_beam(wolf, &ray);
		init_wall(wolf, &ray, &wall);
		textures(wolf, &ray, &wall, x);
	}
	mlx_put_image_to_window(wolf->mlx.mlx_ptr
		, wolf->mlx.win_ptr, wolf->mlx.img.ptr, 0, 0);
}
