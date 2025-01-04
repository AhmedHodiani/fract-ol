/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:00:05 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 03:16:01 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_complex	complex_number_subtract(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.real = z1.real - z2.real;
	result.imag = z1.imag - z2.imag;
	return (result);
}

t_complex	complex_number_add(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.real = z1.real + z2.real;
	result.imag = z1.imag + z2.imag;
	return (result);
}

t_complex	complex_number_divide(t_complex z1, t_complex z2)
{
	t_complex	result;
	long double	temp;

	temp = z2.real * z2.real + z2.imag * z2.imag;
	result.real = (z1.real * z2.real + z1.imag * z2.imag) / temp;
	result.imag = (z2.real * z1.imag - z1.real * z2.imag) / temp;
	return (result);
}

long double	complex_get_distance(t_complex z1, t_complex z2)
{
	long double	real_delta;
	long double	imag_delta;

	real_delta = z1.real - z2.real;
	imag_delta = z1.imag - z2.imag;
	return (sqrt((real_delta) * (real_delta) + (imag_delta) * (imag_delta)));
}
