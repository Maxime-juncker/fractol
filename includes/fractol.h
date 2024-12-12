/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:18:15 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/12 11:16:08 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# include <libft.h>

typedef struct s_complex
{
	double	a;
	double	b;
}	t_complex;

typedef enum e_fractal
{
	NONE,
	MANDLEBROT,
	JULIA,
	BURNING_SHIP
}	t_fractal;

typedef struct s_colors
{
	int		r;
	int		g;
	int		b;
	float	power;
}	t_colors;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_specs
{
	size_t		width;
	size_t		height;
	char		*title;

	void		*mlx;
	void		*mlx_win;
	t_data		img;

	t_colors	colors;
	t_fractal	type;

	float		scale;
	int			x_offset;
	int			y_offset;
	int			nb_symetries;
	float		threshold;
	size_t		max_iteration;

	t_complex	c;
}	t_specs;

// complex.c
t_complex		cadd(t_complex z, t_complex c);
t_complex		cmultr(t_complex z, float r);
t_complex		cmult(t_complex z, t_complex c);
t_complex		cpower(t_complex z, int pow);
double			cmagn(t_complex z);

// colors.c
void			set_pixel(t_data *data, int x, int y, int color);
void			set_color_palette(int id, t_specs *specs);
int				create_trgb(int t, int r, int g, int b);
int				compute_color(t_colors colors, int iteration, \
								int max_iteration);

// formulas.c
t_complex		mandelbrot(t_complex z, t_complex c, t_specs *specs);
t_complex		julia(t_complex z, t_complex c, t_specs *specs);
t_complex		burning_ship(t_complex z, t_complex c, t_specs *specs);

// input.c
int				handle_key_event(int code, t_specs *specs);
int				handle_mouse_event(int button, int x, int y, t_specs *specs);

// main.c
void			draw_fractal(t_specs *specs);

// fractal.c
void			set_fractal(int argc, char **argv, t_specs *specs);
void			draw_fractal(t_specs *specs);

#endif