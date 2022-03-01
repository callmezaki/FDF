/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:59:37 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 07:59:20 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;

	i = ft_strlen(src);
	dup = (char *)malloc(i + 1);
	if (dup == NULL)
	{
		return (0);
	}
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
