/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:13:09 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 12:18:55 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fractol.h"

int	calc_color(t_data *data, t_complex z, int iteration, int pixel_bits)
{
	t_complex center;
	int pixel;

	center.real = 0;
	center.imag = 0;
	double smooth = iteration + 1 - log(log(complex_get_distance(z, center))) / log(2);
	int red   = (int)(smooth * 15) % 256;
	int green = (int)(smooth * 10) % 256;
	int blue  = (int)(smooth * 15) % 256;
	pixel = (red << 16) | (green << 8) | blue;

	if (pixel_bits != 32)
		pixel = mlx_get_color_value(data->mlx, pixel);
	return pixel;
}


