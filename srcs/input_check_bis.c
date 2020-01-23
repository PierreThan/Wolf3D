/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:32:38 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/23 15:34:04 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/wolf3d.h>

int		init_player(t_wolf *wolf)
{
	int i;
	int j;

	i = -1;
	while (++i < wolf->width)
	{
		j = -1;
		while (++j < wolf->height)
		{
			if (wolf->map[i][j] == '0')
			{
				wolf->player.pos.x = i;
				wolf->player.pos.x += 0.5;
				wolf->player.pos.y = j;
				wolf->player.pos.y += 0.5;
				wolf->player.dir.x = 1;
				wolf->player.dir.y = 1;
				wolf->player.plane.x = 0;
				wolf->player.plane.y = 0.66;
				return (1);
			}
		}
	}
	return (0);
}
