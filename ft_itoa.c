/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:02:54 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 05:26:12 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include "fdf.h"

static	int	ft_len(int n)
{
	int	a;
	int	len;

	a = n;
	len = 0;
	if (a <= 0)
		len++;
	while (a != 0)
	{
		a = a / 10;
		len++;
	}
	return (len);
}

static char	*ft_pos(int n)
{
	char	*p;
	int		a;
	int		len;

	a = n;
	len = ft_len(n);
	p = (char *) malloc (len + 1);
	if (p == NULL)
		return (NULL);
	if (n == 0)
		p[0] = '0';
	while (n != 0)
	{
		len--;
		p[len] = (n % 10) + '0';
		n = n / 10;
	}
	p[ft_len(a)] = '\0';
	return (p);
}

static char	*ft_nega(int n)
{
	char	*p;
	int		a;
	int		len;

	a = n;
	len = ft_len(n);
	p = (char *) malloc (len + 1);
	if (p == NULL)
		return (NULL);
	p[0] = '-';
	if (n == 0)
		p[0] = '0';
	while (n != 0)
	{
		len--;
		p[len] = -(n % 10) + '0';
		n = n / 10;
	}
	p[ft_len(a)] = '\0';
	return (p);
}

char	*ft_itoa(int n)
{
	if (n < 0)
		return (ft_nega(n));
	else
		return (ft_pos(n));
}
