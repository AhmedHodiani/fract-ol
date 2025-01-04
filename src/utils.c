/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:13:09 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 03:16:05 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	calc_color(t_data *data, t_complex z, int iteration, int pixel_bits)
{
	t_complex	center;
	int			pixel;
	double		smooth;
	t_rgb		color;

	center.real = 0;
	center.imag = 0;
	smooth = iteration + 1 - log(log(complex_get_distance(z, center))) / log(2);
	color.red = (int)(smooth * 15) % 256;
	color.green = (int)(smooth * 10) % 256;
	color.blue = (int)(smooth * 15) % 256;
	pixel = (color.red << 16) | (color.green << 8) | color.blue;
	if (pixel_bits != 32)
		pixel = mlx_get_color_value(data->mlx, pixel);
	return (pixel);
}

void	send_fractol_type_is_not_valid(char *fractol_type)
{
	ft_printf("============================================\n\n" \
			"invalid fractol type: %s\n\n" \
			"usage: ./fractol [ julia | mandelbrot | newton ] [x] [y]" \
			"x and y are only for julia set fractals\n\n" \
			"============================================\n", fractol_type);
}

void	send_parameters_missing(void)
{
	ft_printf("============================================\n\n" \
			"wrong parameters\n\n" \
			"usage: ./fractol [ julia | mandelbrot | newton ] [x] [y]" \
			"x and y are only for julia set fractals\n\n" \
			"============================================\n");
}

void	send_numbers_are_not_valid(char *x, char *y)
{
	ft_printf("============================================\n\n" \
			"wrong parameters\n\n" \
			"usage: ./fractol [ julia | mandelbrot | newton ] [x] [y]" \
			"some/all of the following values are not valid for a julia:\n" \
			"%s\n%s\n\n" \
			"============================================\n", x, y);
}

int	is_valid_double(char *str)
{
	int	sign_count;
	int	dot_count;
	int	i;

	sign_count = 0;
	dot_count = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i])
			&& str[i] != '.'
			&& str[i] != '-'
			&& str[i] != '+')
			return (0);
		if (str[i] == '.' && dot_count++)
			return (0);
		if ((str[i] == '+' || str[i] == '-') && sign_count++)
			return (0);
		if ((str[i] == '+' || str[i] == '-') && i != 0)
			return (0);
		i++;
	}
	return (1);
}
