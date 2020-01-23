/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:38:32 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/23 15:43:06 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_vec2d		*vec2d_create(double x, double y)
{
	t_vec2d	*vect;

	if (!(vect = ft_memalloc(sizeof(t_vec2d*))))
		return (NULL);
	vect->x = x;
	vect->y = y;
	return (vect);
}

t_vec2d		*vec2d_scalar_mult(t_vec2d a, double l)
{
	t_vec2d	*vect;

	if (!(vect = ft_memalloc(sizeof(t_vec2d*))))
		return (NULL);
	vect->x = l * a.x;
	vect->y = l * a.y;
	return (vect);
}

double		vect2d_dot(t_vec2d a, t_vec2d b)
{
	double	res;

	res = (a.x * b.x) + (a.y * b.y);
	return (res);
}

t_vec2d		*vec2d_sum(t_vec2d a, t_vec2d b)
{
	t_vec2d	*vect;

	if (!(vect = ft_memalloc(sizeof(t_vec2d*))))
		return (NULL);
	vect->x = a.x + b.x;
	vect->y = a.y + b.y;
	return (vect);
}

void		vec2d_normalize(t_vec2d *vect)
{
	if (vect->x >= vect->y)
	{
		vect->y /= vect->x;
		vect->x = 1.00000;
	}
	else
	{
		vect->x /= vect->y;
		vect->y = 1.00000;
	}
}
