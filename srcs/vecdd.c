/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecdd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:38:32 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/23 15:43:06 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_vecdd		*vecdd_create(double x, double y)
{
	t_vecdd	*vect;

	if (!(vect = ft_memalloc(sizeof(t_vecdd*))))
		return (NULL);
	vect->x = x;
	vect->y = y;
	return (vect);
}

t_vecdd		*vecdd_scalar_mult(t_vecdd a, double l)
{
	t_vecdd	*vect;

	if (!(vect = ft_memalloc(sizeof(t_vecdd*))))
		return (NULL);
	vect->x = l * a.x;
	vect->y = l * a.y;
	return (vect);
}

double		vect2d_dot(t_vecdd a, t_vecdd b)
{
	double	res;

	res = (a.x * b.x) + (a.y * b.y);
	return (res);
}

t_vecdd		*vecdd_sum(t_vecdd a, t_vecdd b)
{
	t_vecdd	*vect;

	if (!(vect = ft_memalloc(sizeof(t_vecdd*))))
		return (NULL);
	vect->x = a.x + b.x;
	vect->y = a.y + b.y;
	return (vect);
}

void		vecdd_normalize(t_vecdd *vect)
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
