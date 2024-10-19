/*
• open, close, read, write,
	malloc, free, perror,
	strerror, exit
• All functions of the math
	library (-lm compiler option,
	man 3 math)
• All functions of the MiniLibX
• ft_printf and any equivalent
	YOU coded
*/
#include "fractol.h"
#include <math.h>

#define WIDTH 1000
#define HEIGHT 800

typedef struct s_data
{
	void	*mlx;
	void	*window;
	double	zoom_level;
	long double	position[2];
} t_data;

typedef struct s_pixel
{
	int	color;
} t_pixel;

void	set_coordinates(long double *x, long double *y, int pixel_postion, long double center_position[2], double zoom_level)
{
	*x = (pixel_postion % WIDTH) - (WIDTH / 2);
	*y = (pixel_postion / WIDTH) - (HEIGHT / 2);
	*y *= -1;

	*x /= zoom_level;
	*y /= zoom_level;

	*x += center_position[0];
	*y += center_position[1];
}

void	reset_coordinates(long double *x, long double *y, long double center_position[2], double zoom_level)
{
	*x -= center_position[0];
	*y -= center_position[1];

	*x *= zoom_level;
	*y *= zoom_level;

	*y *= -1;
	*x += WIDTH / 2;
	*y += HEIGHT / 2;
}

void calc_pixel(t_data *data, long double x, long double y, t_pixel *pixel) {
	// red cross in the position center
	// if (x == data->position[0] && y == data->position[1])
	// {
	// 	pixel->color = 0xFF0000;
	// 	return;
	// }
	// // Black
	// //
    // if (x == 2 || x == -2)
    // {
    //     pixel->color = 0x00FF00; // Green for specific condition
    //     return;
    // }
	if (x == 0)
	{
		pixel->color = 0x0000FF; // Black
	}
	if (y == 0)
	{
		pixel->color = 0x0000FF; // Black
	}
	// printf("position : %f, %f\n", data->position[0], data->position[1]);
	// printf("position2 : %f, %f\n", x, y);

	if (x == data->position[0] || y == data->position[1])
	{
		pixel->color = 0x00FFFF; // Green
		return;
	}

    int iteration = 0;
    double zReal = 0.0;
    double zImag = 0.0;
    double tempReal;
    int max_iterations = 50;

    while (iteration < max_iterations)
    {
        // Save the current value of zReal before updating it
        tempReal = zReal;

        // Mandelbrot calculation: z = z^2 + c (where c is the point (x, y))
        zReal = tempReal * tempReal - zImag * zImag + x;
        zImag = 2.0 * tempReal * zImag + y;

        iteration++;

        // Check if point has "escaped" (distance from origin > 2)
        if (zReal * zReal + zImag * zImag > 4)
        {
            // Use a multi-color gradient based on the number of iterations
            int red   = (iteration * 10) % 256;  // Cycle red channel from 0 to 255
            int green = (iteration * 15) % 256; // Cycle green channel from 0 to 255
            int blue  = (iteration * 15) % 256; // Cycle blue channel from 0 to 255

            pixel->color = (red << 16) | (green << 8) | blue;  // Combine RGB into a single color value
            return;
        }
    }

    pixel->color = 0x000000;
}

void	paint_canvas(t_data *data)
{
	t_pixel grid[WIDTH][HEIGHT] = {0};

	int i = 0;
	while (i < WIDTH * HEIGHT)
	{
		long double x = 0.0;
		long double y = 0.0;
		set_coordinates(&x, &y, i, data->position, data->zoom_level);
		// printf("%d => x = %Lf, y = %Lf\n", i, x, y);

		calc_pixel(data, x, y, &grid[i % WIDTH][i / WIDTH]);

		reset_coordinates(&x, &y, data->position, data->zoom_level);

		mlx_pixel_put(data->mlx, data->window, x, y, grid[(int)x][(int)y].color);
		i++;
	}
}

int	key_hook(int keycode, t_data *data)
{
	double moving_interval = 350 / data->zoom_level;

	if (keycode == 119 || keycode == 65362)
		data->position[1] += moving_interval;
	if (keycode == 115 || keycode == 65364)
		data->position[1] -= moving_interval;
	if (keycode == 97 || keycode == 65361)
		data->position[0] -= moving_interval;
	if (keycode == 100 || keycode == 65363)
		data->position[0] += moving_interval;

	// printf("key pressed: %d\n", keycode);
	// printf("position : %f, %f\n", data->position[0], data->position[1]);

	mlx_clear_window(data->mlx, data->window);
	paint_canvas(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		data->zoom_level *= 2;
		data->position[0] += (x - WIDTH / 2) / data->zoom_level;
		data->position[1] += -(y - HEIGHT / 2) / data->zoom_level;
	}
	if (button == 5)
		data->zoom_level *= 0.5;

	mlx_clear_window(data->mlx, data->window);
	paint_canvas(data);
	return (0);
}

int	main(void)
{
	t_data data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "ataher");
	data.zoom_level = 200;
	data.position[0] = 0;
	data.position[1] = 0;


	paint_canvas(&data);

	mlx_mouse_hook(data.window, mouse_hook, &data);
	mlx_key_hook(data.window, key_hook, &data);
	mlx_loop(data.mlx);

	return (0);
}

// cc main.c -lm -Lminilibx-linux -lmlx_Linux -lX11 -lXext && ./a.out


/*
Whats left to do:
	- Fix the zooming (center thing)
	- Fix the exit program
	- Attempt to fix the image glitching
	- Fix the colors
	- Do the other fractolar (argc, argv)
*/


// keeps going to the center when I zoom
