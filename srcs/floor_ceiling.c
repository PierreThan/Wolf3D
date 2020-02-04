/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:31:26 by atyczyns          #+#    #+#             */
/*   Updated: 2020/02/04 16:24:32 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/wolf3d.h>

static void		draw_floor(t_wolf *wolf)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		wolf->floor.cell_x = (int)(wolf->floor.floor_x);
		wolf->floor.cell_y = (int)(wolf->floor.floor_y);
		wolf->floor.t_x = (int)(TEXT_WIDTH * (wolf->floor.floor_x
			- wolf->floor.cell_x)) & (TEXT_WIDTH - 1);
		wolf->floor.t_y = (int)(TEXT_HEIGHT * (wolf->floor.floor_y
			- wolf->floor.cell_y)) & (TEXT_HEIGHT - 1);
		wolf->floor.floor_x += wolf->floor.floorstep_x;
		wolf->floor.floor_y += wolf->floor.floorstep_y;
		wolf.floor.floor_text = ;
		wolf.floor.ceiling_text = ;

	}
}

void			floor_ceiling(t_wolf *wolf)
{
	int		y;

	wolf->texture.h = 400;
	while (++y < wolf->texture.h)
	{
		wolf->floor.ray_dir_x0 = wolf->player.dir.x - wolf->player.plane.x;
		wolf->floor.ray_dir_x1 = wolf->player.dir.x + wolf->player.plane.x;
		wolf->floor.ray_dir_y0 = wolf->player.dir.y - wolf->player.plane.y;
		wolf->floor.ray_dir_y1 = wolf->player.dir.y + wolf->player.plane.y;
		wolf->floor.p = y - HEIGHT / 2;
		wolf->floor.pos_z = 0.5 * HEIGHT;
		wolf->floor.row_distance = wolf->floor.pos_z / wolf->floor.p;
		wolf->floor.floorstep_x = wolf->floor.row_distance
			* (wolf->floor.ray_dir_x1 - wolf->floor.ray_dir_x0) / WIDTH;
		wolf->floor.floorstep_y = wolf->floor.row_distance 
			* (wolf->floor.ray_dir_y1 - wolf->floor.ray_dir_y0) / WIDTH;
		wolf->floor.floor_x = wolf->player.pos.x + wolf->floor.row_distance
			* wolf->floor.ray_dir_x0;
		wolf->floor.floor_y = wolf->player.pos.y + wolf->floor.row_distance
			* wolf->floor.ray_dir_y0;
		draw_floor(wolf);
	}
}
