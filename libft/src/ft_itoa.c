/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:04:13 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/07 11:25:11 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nb_len(int n)
{
	size_t		i;
	long int	nb;

	nb = (long)n;
	i = 1;
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb / 10 > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	nb;
	char		*res;
	size_t		i;
	size_t		len;

	len = get_nb_len(n);
	nb = (long)n;
	res = malloc(len + 1);
	i = 0;
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	if (nb < 0)
	{
		nb *= -1;
		res[0] = '-';
	}
	while (nb > 0)
	{
		res[len - i++ - 1] = (nb % 10) + '0';
		nb /= 10;
	}
	res[len] = '\0';
	return (res);
}

static size_t	uget_nb_len_base(unsigned int n, int base_len)
{
	size_t		i;
	long int	nb;

	nb = (long)n;
	i = 1;
	while (nb / base_len > 0)
	{
		i++;
		nb /= base_len;
	}
	return (i);
}

char	*u_ft_itoa(unsigned int n)
{
	char				*res;
	size_t				i;
	size_t				len;

	len = uget_nb_len_base(n, 10);
	res = malloc(len + 1);
	i = 0;
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	while (n > 0)
	{
		res[len - i++ - 1] = (n % 10) + '0';
		n /= 10;
	}
	res[len] = '\0';
	return (res);
}

char	*u_ft_itoa_base(unsigned int n, char *base)
{
	char	*res;
	size_t	i;
	size_t	len;
	size_t	base_len;

	base_len = ft_strlen(base);
	len = uget_nb_len_base(n, base_len);
	res = malloc(len + 1);
	i = 0;
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	while (n > 0)
	{
		res[len - i++ - 1] = base[(n % base_len)];
		n /= base_len;
	}
	res[len] = '\0';
	return (res);
}
