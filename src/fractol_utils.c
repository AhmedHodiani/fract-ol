/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:08 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 16:39:15 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_complex	calc_newtons_method(t_complex z)
{
	t_complex	f;
	t_complex	df;

	f = complex_number_cubed(z);
	f.real -= 1.0;
	df = complex_number_squared(z);
	df.real = df.real * 3;
	df.imag = df.imag * 3;
	z = complex_number_subtract(z, complex_number_divide(f, df));
	return (z);
}

t_rgb	calc_newton_color(t_complex z)
{
	int			i;
	t_complex	roots[3];
	t_rgb		color;
	long double	distance;

	complex_get_roots_of_unity(roots);
	i = 1;
	while (i < 4)
	{
		distance = complex_get_distance(z, roots[i - 1]);
		if (distance < 0.1)
		{
			color.red = (int)(i * 70) % 256;
			color.green = (int)(i * 40) % 256;
			color.blue = (int)(i * 50) % 256;
			return (color);
		}
		i++;
	}
	color.red = 0;
	color.green = 0;
	color.blue = 0;
	return (color);
}
