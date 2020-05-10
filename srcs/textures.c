/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:56:39 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/22 18:50:52 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		init_texture4(t_wolf *wolf)
{
	t_img	*tmp;
	int		*w;
	int		*h;

	w = &(wolf->texture.width);
	h = &(wolf->texture.height);
	tmp = wolf->texture.img;
	while (tmp && tmp->ptr != NULL)
		tmp++;
	if (!(tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, BLUESTONE, w, h)))
		return (0);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	if (!(tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, PURPLESTO, w, h)))
		return (0);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	return (1);
}

int		init_texture3(t_wolf *wolf)
{
	t_img	*tmp;
	int		*w;
	int		*h;

	w = &(wolf->texture.width);
	h = &(wolf->texture.height);
	tmp = wolf->texture.img;
	while (tmp && tmp->ptr != NULL)
		tmp++;
	if (!(tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, MOSSY, w, h)))
		return (0);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	if (!(tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, COLORSTON, w, h)))
		return (0);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	if (!(tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, GREYSTONE, w, h)))
		return (0);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	return (init_texture4(wolf));
}

int		init_texture2(t_wolf *wolf)
{
	t_img	*tmp;
	int		*w;
	int		*h;

	wolf->texture.width = 64;
	wolf->texture.height = 64;
	w = &(wolf->texture.width);
	h = &(wolf->texture.height);
	tmp = wolf->texture.img;
	if (!(tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, BRICK, w, h)))
		return (0);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	if (!(tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, REDBRICK, w, h)))
		return (0);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	if (!(tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, WOOD, w, h)))
		return (0);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	return (init_texture3(wolf));
}

int		init_texture(t_wolf *wolf)
{
	int		fd[NB_TEXTURES];

	if (!(wolf->texture.img =
		(t_img *)ft_memalloc(sizeof(t_img) * NB_TEXTURES)))
		return (0);
	if ((fd[0] = open(BRICK, O_RDONLY) == -1)
		|| (fd[1] = open(REDBRICK, O_RDONLY)) == -1
		|| (fd[2] = open(WOOD, O_RDONLY)) == -1
		|| (fd[3] = open(MOSSY, O_RDONLY)) == -1
		|| (fd[4] = open(COLORSTON, O_RDONLY)) == -1
		|| (fd[5] = open(GREYSTONE, O_RDONLY)) == -1
		|| (fd[6] = open(BLUESTONE, O_RDONLY)) == -1
		|| (fd[7] = open(PURPLESTO, O_RDONLY)) == -1)
		return (0);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	close(fd[4]);
	close(fd[5]);
	close(fd[6]);
	close(fd[7]);
	return (init_texture2(wolf));
}

void	free_textures(t_wolf *wolf)
{
	t_img	*tmp;
	int		i;

	i = -1;
	if (wolf)
	{
		if (wolf->texture.img)
		{
			while (++i < NB_TEXTURES)
			{
				tmp = wolf->texture.img[NB_TEXTURES - 1 - i].ptr;
				if (tmp)
					mlx_destroy_image(wolf->mlx.mlx_ptr,
						wolf->texture.img[NB_TEXTURES - 1 - i].ptr);
			}
			ft_memdel((void**)(&wolf->texture.img));
		}
	}
}
