/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:07:25 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/12 16:25:26 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*sf;

	sf = (char *)s;
	i = 0;
	while ((size_t)i <= ft_strlen(sf))
	{
		if (s[i] == (char)c)
		{
			i++;
			return (&((char *)sf)[i]);
		}
		i++;
	}
	return (0);
}
