#include <mlx.h>
#include <libft.h>
#include <math.h>
#include <complex.h>
#include <stdio.h>

typedef struct s_specs
{
	size_t	width;
	size_t	height;
	char *title;

	void	*mlx;
	void	*mlx_win;

	float scale;
} t_specs;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	set_pixel(t_data *data, int x, int y, int color)
{
	void	*dst;

	// a annoter
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	compute_color(int iteration, int max_iteration)
{
	int	r;
	int	g;
	int	b;
	// int hue;

	// hue = 255 * (iteration / max_iteration);

	r = 255 * iteration / max_iteration;
	g = 255 * iteration / max_iteration;
	b = 100;
	// r = (hue / 255.0) * 255;
    // g = ((255 - hue) / 255.0) * 255;
    // b = 128	;
	return create_trgb(0, r, g, b);
}


void	draw_fractal(t_specs *specs)
{
	t_data	img;

	img.img = mlx_new_image(specs->mlx, specs->width, specs->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	float i = 0;
	float j = 0;
	size_t iteration = 0;
	size_t max_iteration = 500;
	float complex c;
	float complex z;

	int	threshold = 10;

	while (j < specs->height)
	{
		i = 0;
		while (i < specs->width)
		{
			c = ((i - specs->width / 2)) + (((j - specs->height / 2) * I));
			z = 0;
			iteration = 0;
			while (iteration < max_iteration)
			{
				if (cabsf(z) >= threshold)
					break;
				z = z*z + c * specs->scale;
				iteration++;
			}

			printf("iteration: %zu abs(x): %f\n", iteration, cabsf(z));
			set_pixel(&img, i, j, compute_color(iteration, max_iteration));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(specs->mlx, specs->mlx_win, img.img, 0, 0);
}


int	win_close(int code, t_specs *specs)
{
	if (code == 'q')
		mlx_destroy_window(specs->mlx, specs->mlx_win);
	if (code == 's')
	{
		specs->scale += .001f;
		draw_fractal(specs);
	}
	if (code == 'w')
	{
		specs->scale -= .001f;
		draw_fractal(specs);
	}
	return (0);
}

int main(void)
{

	t_specs	specs;

	specs.width = 720;
	specs.height = 420;
	specs.title = "HAAAAAA";

	specs.scale = .005f;

	specs.mlx = mlx_init();
	specs.mlx_win = mlx_new_window(specs.mlx, specs.width, specs.height, specs.title);

	mlx_hook(specs.mlx_win, 2, 1L<<0, win_close, &specs); //? 1L<<0 == keypress mask

	draw_fractal(&specs);

	mlx_loop(specs.mlx);


}