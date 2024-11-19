/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:00:05 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 12:10:34 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

t_complex complex_number_cubed(t_complex z)
{
	t_complex result;
	result.real = z.real * z.real * z.real - 3 * z.real * z.imag * z.imag;
	result.imag = 3 * z.real * z.real * z.imag - z.imag * z.imag * z.imag;
	return result;
}

t_complex complex_number_squared(t_complex z)
{
	t_complex result;
	result.real = z.real * z.real - z.imag * z.imag;
	result.imag = 2 * z.real * z.imag;
	return result;
}

t_complex complex_number_subtract(t_complex z1, t_complex z2)
{
	t_complex result;
	result.real = z1.real - z2.real;
	result.imag = z1.imag - z2.imag;
	return result;
}

t_complex complex_number_add(t_complex z1, t_complex z2)
{
	t_complex result;
	result.real = z1.real + z2.real;
	result.imag = z1.imag + z2.imag;
	return result;
}

t_complex complex_number_divide(t_complex z1, t_complex z2)
{
	t_complex result;
	result.real = (z1.real * z2.real + z1.imag * z2.imag) / (z2.real * z2.real + z2.imag * z2.imag);
	result.imag = (z2.real * z1.imag - z1.real * z2.imag) / (z2.real * z2.real + z2.imag * z2.imag);
	return result;
}
/*
	roots of unity are always 1, w, w^2
	note: omega = w = e^(2pi i / 3)
*/
void	complex_get_roots_of_unity(t_complex roots[3])
{
	roots[0].real = 1.0;
	roots[0].imag = 0.0;

	roots[1].real = -0.5;
	roots[1].imag = 0.866;

	roots[2].real = -0.5;
	roots[2].imag = -0.866;
}

long double complex_get_distance(t_complex z1, t_complex z2)
{
	return sqrt((z1.real - z2.real) * (z1.real - z2.real) + (z1.imag - z2.imag) * (z1.imag - z2.imag));
}
