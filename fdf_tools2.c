/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:44:46 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 02:55:51 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx	ft_reset(t_mlx mlx)
{
	mlx.altitude = 1;
	mlx.zoom = get_mult(mlx.data, mlx);
	mlx.p_x = 0;
	mlx.p_y = 0;
	mlx.r_type = 'n';
	mlx.iso_validity = 1;
	mlx.alpha = 0;
	mlx.beta = 0;
	mlx.gama = 0;
	return (mlx);
}

int	get_mult(t_data data, t_mlx vars)
{
	if (data.height > 400 || data.width > 400)
		vars.zoom = 2;
	else if (data.height > 200 || data.width > 200)
		vars.zoom = 3;
	else if (data.height > 99 || data.width > 99)
		vars.zoom = 4;
	else if (data.height > 50 || data.width > 50)
		vars.zoom = 20;
	else
		vars.zoom = 25;
	if (data.z_size != 0 && data.case_size != 0)
		vars.zoom = data.case_size;
	return (vars.zoom);
}
