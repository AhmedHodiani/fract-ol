/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:13:09 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 14:11:41 by ataher           ###   ########.fr       */
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

void send_fractol_type_is_not_valid(char *fractol_type)
{
	char *msgs[7];
	msgs[0] = "============================================\n";
	msgs[1] = "invalid fractol type\n\n";
	msgs[2] = "usage: ./fractol [ julia | mandelbrot | newton ] [x] [y]";
	msgs[3] = "x and y are only for julia set fractals\n";
	msgs[4] = ft_strjoin("invalid fractol type: ", fractol_type);
	msgs[5] = "\n============================================\n";
	msgs[6] = NULL;
	ft_print_strings(msgs);
}

void send_parameters_missing(void)
{
	char *msgs[6];
	msgs[0] = "============================================\n";
	msgs[1] = "wrong parameters\n\n";
	msgs[2] = "usage: ./fractol [ julia | mandelbrot | newton ] [x] [y]";
	msgs[3] = "x and y are only for julia set fractals\n";
	msgs[4] = "============================================\n";
	msgs[5] = NULL;
	ft_print_strings(msgs);
}

void send_numbers_are_not_valid(char *x, char *y)
{
	char *msgs[9];
	msgs[0] = "============================================\n";
	msgs[1] = "numbers are not valid\n\n";
	msgs[2] = "usage: ./fractol [ julia | mandelbrot | newton ] [x] [y]";
	msgs[3] = "some/all of the following values are not valid numbers for a julia set:\n";
	msgs[4] = x;
	msgs[5] = y;
	msgs[6] = "";
	msgs[7] = "============================================\n";
	msgs[8] = NULL;
	ft_print_strings(msgs);
}

int is_valid_double(char *str)
{
	int sign_count;
	int dot_count;
	int i;

	sign_count = 0;
	dot_count = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != '-' && str[i] != '+')
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
