/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:49:19 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 07:59:33 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	if (n == 0)
		return (0);
	a = 0;
	while (s1[a] && s2[a] && s1[a] == s2[a] && a < n - 1)
		a++;
	return (((unsigned char *)s1)[a] - ((unsigned char *)s2)[a]);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	a;

	a = 0;
	while (s1[a] && s2[a] && s1[a] == s2[a])
		a++;
	return (((unsigned char *)s1)[a] - ((unsigned char *)s2)[a]);
}
