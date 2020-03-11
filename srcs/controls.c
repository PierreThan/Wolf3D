/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:37:19 by pthan             #+#    #+#             */
/*   Updated: 2020/03/11 17:37:22 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	move_up(t_wolf *wolf)
{
	int	nex;
	int	ney;

	nex = (int)(wolf->player.pos.x + wolf->player.dir.x * wolf->move_speed);
	ney = (int)(wolf->player.pos.y + wolf->player.dir.y * wolf->move_speed);
	if ((wolf->map[nex][(int)wolf->player.pos.y] == '0') ||
		(wolf->map[nex][(int)wolf->player.pos.y] == '8'))
		wolf->player.pos.x += wolf->player.dir.x * wolf->move_speed;
	if ((wolf->map[(int)wolf->player.pos.x][ney] == '0') ||
		(wolf->map[(int)wolf->player.pos.x][ney] == '8'))
		wolf->player.pos.y += wolf->player.dir.y * wolf->move_speed;
}

void	move_down(t_wolf *wolf)
{
	int	nex;
	int	ney;

	nex = (int)(wolf->player.pos.x - wolf->player.dir.x * wolf->move_speed);
	ney = (int)(wolf->player.pos.y - wolf->player.dir.y * wolf->move_speed);
	if ((wolf->map[nex][(int)wolf->player.pos.y] == '0') ||
		(wolf->map[nex][(int)wolf->player.pos.y] == '8'))
		wolf->player.pos.x -= wolf->player.dir.x * wolf->move_speed;
	if ((wolf->map[(int)wolf->player.pos.x][ney] == '0') ||
		(wolf->map[(int)wolf->player.pos.x][ney] == '0'))
		wolf->player.pos.y -= wolf->player.dir.y * wolf->move_speed;
}

void	move(int key, t_wolf *wolf)
{
	if (key == ARROW_UP || key == MAIN_PAD_W)
		move_up(wolf);
	else if (key == ARROW_DOWN || key == MAIN_PAD_S)
		move_down(wolf);
	ray_casting(wolf);
}

void	rotate(int key, t_wolf *wolf, double old_dir_x, double old_plane_x)
{
	old_dir_x = wolf->player.dir.x;
	old_plane_x = wolf->player.plane.x;
	if (key == ARROW_LEFT || key == MAIN_PAD_A)
	{
		wolf->player.dir.x = wolf->player.dir.x * cos(-wolf->rot_speed)
			- wolf->player.dir.y * sin(-wolf->rot_speed);
		wolf->player.dir.y = old_dir_x * sin(-wolf->rot_speed)
			+ wolf->player.dir.y * cos(-wolf->rot_speed);
		wolf->player.plane.x = wolf->player.plane.x * cos(-wolf->rot_speed)
			- wolf->player.plane.y * sin(-wolf->rot_speed);
		wolf->player.plane.y = old_plane_x * sin(-wolf->rot_speed)
			+ wolf->player.plane.y * cos(-wolf->rot_speed);
	}
	else if (key == ARROW_RIGHT || key == MAIN_PAD_D)
	{
		wolf->player.dir.x = wolf->player.dir.x * cos(wolf->rot_speed)
			- wolf->player.dir.y * sin(wolf->rot_speed);
		wolf->player.dir.y = old_dir_x * sin(wolf->rot_speed)
			+ wolf->player.dir.y * cos(wolf->rot_speed);
		wolf->player.plane.x = wolf->player.plane.x * cos(wolf->rot_speed)
			- wolf->player.plane.y * sin(wolf->rot_speed);
		wolf->player.plane.y = old_plane_x * sin(wolf->rot_speed)
			+ wolf->player.plane.y * cos(wolf->rot_speed);
	}
	ray_casting(wolf);
}
