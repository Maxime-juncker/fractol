#include <fractol.h>
#include <math.h>

/*
 * adding two complex
 * @param z first complex
 * @param c second complex
*/
t_complex	cadd(t_complex z, t_complex c)
{
	z.a = z.a + c.a;
	z.b = z.b + c.b;
	return (z);
}

/*
 * multiply two complex
 * @param z first complex
 * @param c second complex
*/
t_complex	cmult(t_complex z, t_complex c)
{
	t_complex	tmp;

	tmp.a = (z.a * c.a) - (z.b * c.b);
	tmp.b = (z.a * c.b) + (z.b * c.a);
	return (tmp);
}

/*
 * multiply a complex by a real
 * @param z first complex
 * @param r real number
*/
t_complex	cmultr(t_complex z, float r)
{
	z.a = z.a * r;
	z.b = z.b * r;
	return (z);
}

/*
 * power a complex number
 * @param z complex number
 * @param pow the power amount
*/
t_complex	cpower(t_complex z, int pow)
{
	int			i;
	t_complex	tmp;

	i = 1;
	tmp.a = z.a;
	tmp.b = z.b;
	while (i < pow)
	{
		z = cmult(z, tmp);
		i++;
	}
	return (z);
}
/*
 * abs of a complex number
 * @param z complex number
*/
double	cmagn(t_complex z)
{
	return (sqrt((z.a * z.a) + (z.b * z.b)));
}
