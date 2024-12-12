/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:25:43 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/12 11:06:14 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

//? Zn+1 = Zn^sim + c
t_complex	mandelbrot(t_complex z, t_complex c, t_specs *specs)
{
	return (cadd(cpower(z, specs->nb_symetries), cmultr(c, specs->scale)));
}

//? Zn+1 = Zn^sim + c (c constant)
t_complex	julia(t_complex z, t_complex c, t_specs *specs)
{
	return (cadd(cpower(z, specs->nb_symetries), c));
}

//? Zn+1 = (|Re(Zn)|^2 - |Im(Zn)|^2 + (2 * |Re(Zn)| * |Im(Zn)|)i ) + c
t_complex	burning_ship(t_complex z, t_complex c, t_specs *specs)
{
	t_complex	tmp;

	tmp.a = fabs(z.a) * fabs(z.a) - fabs(z.b) * fabs(z.b);
	tmp.b = 2 * fabs(z.a) * fabs(z.b);
	c = cmultr(c, specs->scale);
	tmp = cadd(tmp, c);
	return (tmp);
}
