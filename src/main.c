#include <mlx.h>
#include <libft.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <fractol.h>
#include <complex.h>
typedef enum e_fractal
{
	NONE,
	MANDLEBROT,
	JULIA,
	BURNING_SHIP
} t_fractal;

typedef	struct s_colors
{
	int r;
	int g;
	int b;
	float power;
} t_colors;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_specs
{
	size_t	width;
	size_t	height;
	char *title;

	void	*mlx;
	void	*mlx_win;
	t_data	img;

	t_colors colors;

	t_fractal	type;
	float scale;
	int x_offset;
	int y_offset;
	float	threshold;
	size_t	max_iteration;
	t_complex c;

} t_specs;


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

double	dabs(double n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	set_color_palette(int id, t_specs *specs)
{
	// 0 = default
	if (id == 0)
	{
		specs->colors.r = 200;
		specs->colors.g = 200;
		specs->colors.b = 200;
		specs->colors.power = 1.3f;
	}
	if (id == 1)
	{
		specs->colors.r = 150;
		specs->colors.g = 50;
		specs->colors.b = 255;
		specs->colors.power = 1.4f;
	}
	if (id == 2)
	{
		specs->colors.r = 220;
		specs->colors.g = 20;
		specs->colors.b = 50;
		specs->colors.power = 1.5f;
	}
}

int	compute_color(t_colors colors, int iteration, int max_iteration)
{
	int	r;
	int	g;
	int	b;

	r = colors.r * iteration / max_iteration * colors.power;
	g = colors.g * iteration / max_iteration * colors.power;
	b = colors.b * iteration / max_iteration * colors.power;
	return create_trgb(0, r, g, b);
}

//? Zn+1 = Zn^2 + c
t_complex mandelbrot(t_complex z, t_complex c, t_specs *specs)
{
	return (cadd(cpower(z, 2), cmultr(c, specs->scale)));
}

t_complex julia(t_complex z, t_complex c, t_specs *specs)
{
	(void)specs;
	return (cadd(cpower(z, 2), c));
}

t_complex burning_ship(t_complex z, t_complex c, t_specs *specs)
{
	t_complex tmp;

	tmp.a = fabs(z.a)*fabs(z.a) - fabs(z.b)*fabs(z.b);
	tmp.b = 2 * fabs(z.a) * fabs(z.b);
	c = cmultr(c, specs->scale);
	tmp = cadd(tmp, c);
	return (tmp);
}

void	draw_fractal(t_specs *specs)
{
	specs->img.img = mlx_new_image(specs->mlx, specs->width, specs->height);
	specs->img.addr = mlx_get_data_addr(specs->img.img, &specs->img.bits_per_pixel, &specs->img.line_length, &specs->img.endian);

	float i = 0;
	float j = 0;
	size_t iteration = 0;
	t_complex c;
	t_complex z;

	while (j < specs->height)
	{
		i = 0;
		while (i < specs->width)
		{
			if (specs->type == MANDLEBROT)
			{
				c.a = (i - specs->x_offset) - specs->width / 2;
				c.b = (j - specs->y_offset) - specs->height / 2;
				z.a = 0;
				z.b = 0;
			}
			else if (specs->type == JULIA)
			{
				z.a = ((i - specs->x_offset) - specs->width / 2) * specs->scale;
				z.b = ((j - specs->y_offset) - specs->height / 2) * specs->scale;
			}
			else
			{
				c.a = (i - specs->x_offset) - specs->width / 2;
				c.b = (j - specs->y_offset) - specs->height / 2;
				z.a = 0;
				z.b = 0;
			}
			iteration = 0;
			while (iteration < specs->max_iteration)
			{
				if (cmagn(z) >= specs->threshold)
					break;
				if (specs->type == MANDLEBROT)
					z = mandelbrot(z, c, specs);
				else if (specs->type == JULIA)
					z = julia(z, specs->c, specs);
				else if (specs->type == BURNING_SHIP)
					z = burning_ship(z, c, specs);
				iteration++;
			}
			set_pixel(&specs->img, i, j, compute_color(specs->colors ,iteration, specs->max_iteration));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(specs->mlx, specs->mlx_win, specs->img.img, 0, 0);
}


int	handle_mouse_event(int button, int x, int y, t_specs *specs)
{
	(void)x;
	(void)y;
	if (specs == NULL)
		return (-1);
	if (button == 4)
		specs->scale -= .05f * specs->scale;
	if (button == 5)
		specs->scale += .05f * specs->scale;
	draw_fractal(specs);
	return 0;
}

int	handle_key_event(int code, t_specs *specs)
{
	if (specs == NULL)
		return (-1);
	if (code == 'q')
	{
		// free(specs.mlx);
		free(specs->mlx);
		free(specs->mlx_win);
		// return (0);
		exit(0);
	}
	else if (code == 'a')
		specs->x_offset += 60;
	else if (code == 'd')
		specs->x_offset -= 60;
	else if (code == 'w')
		specs->y_offset += 60;
	else if (code == 's')
		specs->y_offset -= 60;
	else if (code == 'r')
	{
		specs->x_offset = 0;
		specs->y_offset = 0;
		specs->scale = 0.005f;
	}

	// colors
	else if (code == '1')
		set_color_palette(0, specs);
	else if (code == '2')
		set_color_palette(1, specs);
	else if (code == '3')
		set_color_palette(2, specs);

	// settings
	else if (code == '=')
		specs->max_iteration += 10;
	else if (code == '-')
	{
		if (specs->max_iteration - 10 > 10)
			specs->max_iteration -= 10;
	}
	else if (code == 'z')
		specs->threshold += 0.2f;
	else if (code == 'x')
	{
		if (specs->threshold > 0.2f)
			specs->threshold -= 0.2f;
	}
	else
		return (0);
	draw_fractal(specs);
	return (0);
}


int	set_fractal(int argc, char **argv, t_specs *specs)
{
	if (argc == 1)
	{
		ft_printf("Available options:\n(1) mandlebrot\n(2) julia\n(3) burning ship\n");
		return (1);
	}
	if (argv[1][0] == '1')
	{
		specs->title = "mandelbrot";
		specs->type = MANDLEBROT;
	}
	else if(argv[1][0] == '2')
	{
		specs->title = "julia";
		specs->type = JULIA;
	}
	else if (argv[1][0] == '3')
	{
		specs->title = "burning ship";
		specs->type = BURNING_SHIP;
	}
	else
	{
		ft_printf("\nWrong input, please try again\n");
		ft_printf("Available options:\n(1) mandlebrot\n(2) julia\n(3) burning ship\n");
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_specs	specs;

	specs.width = 720;
	specs.height = 480;
	specs.title = "Default";
	specs.type = JULIA;

	specs.scale = .005f;
	specs.x_offset = 0;
	specs.y_offset = 0;
	specs.threshold = 2;
	specs.max_iteration = 50;
	set_color_palette(0, &specs);

	if (set_fractal(argc, argv, &specs) == 1)
		exit(0);

	specs.c.a = 0.285;
	specs.c.b = 0.01;
	if (argc == 4)
	{
		specs.c.a = (double)atoi(argv[2]) / 100;
		specs.c.b = (double)atoi(argv[3]) / 100;
	}

	specs.mlx = mlx_init();
	specs.mlx_win = mlx_new_window(specs.mlx, specs.width, specs.height, specs.title);

	mlx_key_hook(specs.mlx_win, handle_key_event, &specs);
	mlx_mouse_hook(specs.mlx_win, handle_mouse_event, &specs);
	draw_fractal(&specs);

	mlx_loop(specs.mlx);
}
