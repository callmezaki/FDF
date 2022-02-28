/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 07:12:05 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 07:15:08 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_buton(int key, void *vars)
{
	(void)vars;
	if (key == ESC)
		exit(0);
	return (0);
}

int	ft_destroy(t_mlx *mlx)
{
	(void)mlx;
	write(1, "Bye!\n", 6);
	exit(0);
	return (0);
}
