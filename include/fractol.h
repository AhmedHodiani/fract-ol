/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:33:14 by ataher            #+#    #+#             */
/*   Updated: 2024/11/19 09:41:02 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <X11/keysym.h>
#include "mlx.h"
#include "libft.h"

#define WIDTH 1000
#define HEIGHT 800

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*image;
	double	zoom_level;
	long double	position[2];
	int max_iterations;
	int type; // 0 = mandelbrot, 1 = julia
	long double julia[2];
} t_data;

int		key_hook(int keycode, t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);
void	ft_destory(t_data *data);
void	paint_canvas(t_data *data);

#endif
