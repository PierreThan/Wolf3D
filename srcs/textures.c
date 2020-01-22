/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:56:39 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/22 18:11:07 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_texture(t_wolf *wolf)
{
	int		x;
	int		y;
	int		xcolor;
	int		ycolor;
	int		xycolor;

	x = -1;
	if (!(wolf->texture.buffer = (unsigned int**)malloc(sizeof(unsigned int *) * HEIGHT + 1)))
		free_wolf(wolf);
	while (++x <= HEIGHT)
		if (!(wolf->texture.buffer[x] = (unsigned int*)malloc(sizeof(unsigned int) * WIDTH + 1)))
			free_wolf(wolf);
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			xcolor = (x * 256 / WIDTH) ^ (y * 256 / HEIGHT);
			ycolor = y * 256 / HEIGHT;
			xycolor = y * 128 / HEIGHT + x * 128 / WIDTH;
			wolf->texture.text_map[0][WIDTH * y + x] = 65536 * 254 * (x != y && x != WIDTH - y);
			wolf->texture.text_map[1][WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			wolf->texture.text_map[2][WIDTH * y + x] = 256 * xycolor + 65536 * xycolor;
			wolf->texture.text_map[3][WIDTH * y + x] = xcolor + 256 * xcolor + 65536 * xycolor;
			wolf->texture.text_map[4][WIDTH * y + x] = 256 * xcolor;
			wolf->texture.text_map[5][WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);;
			wolf->texture.text_map[6][WIDTH * y + x] = 65536 * ycolor;
			wolf->texture.text_map[7][WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;
		}
	}
}
