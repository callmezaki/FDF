/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:44:08 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 05:29:19 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_iso(t_vars *vars)
{
	int	temp;
	int	temp1;
	int	temp2;
	int	temp3;

	temp = (vars->x0 - vars->y0) * cos(0.52);
	temp1 = (vars->x1 - vars->y1) * cos(0.52);
	temp2 = -vars->z0 + (vars->x0 + vars->y0) * sin(0.52);
	temp3 = -vars->z1 +(vars->x1 + vars->y1) * sin(0.52);
	vars->x0 = temp ;
	vars->x1 = temp1;
	vars->y0 = temp2;
	vars->y1 = temp3;
}

void	handle_zoom_center(t_vars *vars, t_mlx mlx, t_data data)
{
	vars->y0 *= mlx.zoom;
	vars->y1 *= mlx.zoom;
	vars->x0 *= mlx.zoom;
	vars->x1 *= mlx.zoom;
	vars->y0 -= (data.height * mlx.zoom) / 2;
	vars->y1 -= (data.height * mlx.zoom) / 2;
	vars->x0 -= (data.width * mlx.zoom) / 2;
	vars->x1 -= (data.width * mlx.zoom) / 2;
}

void	padding(t_vars *vars)
{
	vars->x1 += vars->pad_x;
	vars->y1 += vars->pad_y;
	vars->x0 += vars->pad_x;
	vars->y0 += vars->pad_y;
}

t_math	get_valus(t_vars *vars, t_math math)
{
	math.dx = abs(vars->x1 - vars->x0);
	if (vars->x0 < vars->x1)
		math.sx = 1;
	else
		math.sx = -1;
	math.dy = -abs(vars->y1 - vars->y0);
	if (vars->y0 < vars->y1)
		math.sy = 1;
	else
		math.sy = -1;
	math.err = math.dx + math.dy;
	return (math);
}

void	bresenham(t_vars *vars, t_mlx mlx, t_math math, int color)
{
	math = get_valus(vars, math);
	while (1)
	{
		if ((vars->x0 + mlx.p_x) > 0 && (vars->x0 + mlx.p_x) < 1920
			&& (vars->y0 + mlx.p_y) > 0 && (vars->y0 + mlx.p_y) < 1080)
			my_mlx_pixel_put(&mlx, vars->x0 + mlx.p_x, vars->y0
				+ mlx.p_y, color);
		if (vars->x0 == vars->x1 && vars->y0 == vars->y1)
			break ;
		math.e2 = 2 * math.err;
		if (math.e2 >= math.dy)
		{
			if (vars->x0 == vars->x1)
				break ;
			math.err += math.dy;
			vars->x0 += math.sx;
		}
		if (math.e2 <= math.dx)
		{
			if (vars->y0 == vars->y1)
				break ;
			math.err += math.dx;
			vars->y0 += math.sy;
		}
	}
}
