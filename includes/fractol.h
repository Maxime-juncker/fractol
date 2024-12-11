#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>

// complex: z = ax + bi
typedef struct s_complex
{
	double	a;
	double	b;
} t_complex;

t_complex		cadd(t_complex z, t_complex c);
t_complex		cmultr(t_complex z, float r);
t_complex		cmult(t_complex z, t_complex c);
t_complex		cpower(t_complex z, int pow);
double			cmagn(t_complex z);

#endif