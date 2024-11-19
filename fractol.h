#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "minilibx-linux/mlx.h"

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
} t_data;

#endif
