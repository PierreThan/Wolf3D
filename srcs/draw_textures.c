/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:56:39 by atyczyns          #+#    #+#             */
/*   Updated: 2019/12/04 15:33:48 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	put_pxl_to_img(t_wolf *wolf, int x, int y, int color)
{
	if (x < WIDTH && y < HEIGHT)
		ft_memcpy(wolf->mlx.img.ptr + 4 * WIDTH * y + x * 4,
		/*la on met l'adress de l'image qu'on recupere de notrs BITMAP*/, sizeof(int));
}
