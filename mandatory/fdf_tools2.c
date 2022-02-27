/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:44:46 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/27 05:54:29 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	check_map(t_data data)
{
	int		i;
	int		len;
	char	**temp;

	len = 0;
	i = 0;
	while (i < data.height)
	{
		if (data.lines[i][0] == '\n')
		{
			printf("Invalid map.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (data.lines[i])
	{
		len = 0;
		temp = ft_split(data.lines[i], ' ');
		while (temp[len])
			len++;
		if (len != data.width)
		{
			printf("Invalid map.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	close_buton(int key, void *vars)
{
	(void)vars;
	if (key == ESC)
		exit(0);
	return (0);
}

int	get_mult(t_data data)
{
	int	n;

	if (data.height > 400 || data.width > 400)
		n = 2;
	else if (data.height > 200 || data.width > 200)
		n = 3;
	else if (data.height > 99 || data.width > 99)
		n = 4;
	else if (data.height > 50 || data.width > 50)
		n = 20;
	else
		n = 25;
	return (n);
}
