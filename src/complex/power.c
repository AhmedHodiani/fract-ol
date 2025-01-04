/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:36:39 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 03:16:02 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fractol.h"

t_complex	complex_number_cubed(t_complex z)
{
	t_complex	result;

	result.real = z.real * z.real * z.real - 3 * z.real * z.imag * z.imag;
	result.imag = 3 * z.real * z.real * z.imag - z.imag * z.imag * z.imag;
	return (result);
}

t_complex	complex_number_squared(t_complex z)
{
	t_complex	result;

	result.real = z.real * z.real - z.imag * z.imag;
	result.imag = 2 * z.real * z.imag;
	return (result);
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
