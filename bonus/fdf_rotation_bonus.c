/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 06:16:46 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 07:58:49 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	x_rotaion(t_vars *vars, t_mlx mlx)
{
	int	temp;
	int	temp1;

	temp = vars->y0 * cos(mlx.alpha) + vars->z0 * sin(mlx.alpha);
	temp1 = vars->y1 * cos(mlx.alpha) + vars->z1 * sin(mlx.alpha);
	vars->z0 = -vars->y0 * sin(mlx.alpha) + vars->z0 * cos(mlx.alpha);
	vars->z1 = -vars->y1 * sin(mlx.alpha) + vars->z1 * cos(mlx.alpha);
	vars->y0 = temp;
	vars->y1 = temp1;
}

void	y_rotaion(t_vars *vars, t_mlx mlx)
{
	int	temp;
	int	temp1;

	temp = vars->x0 * cos(mlx.beta) + vars->z0 * sin(mlx.beta);
	temp1 = vars->x1 * cos(mlx.beta) + vars->z1 * sin(mlx.beta);
	vars->z0 = -vars->x0 * sin(mlx.beta) + vars->z0 * cos(mlx.beta);
	vars->z1 = -vars->x1 * sin(mlx.beta) + vars->z1 * cos(mlx.beta);
	vars->x0 = temp;
	vars->x1 = temp1;
}

void	z_rotaion(t_vars *vars, t_mlx mlx)
{
	int	temp;
	int	temp1;

	temp = vars->x0 * cos(mlx.gama) - vars->y0 * sin(mlx.gama);
	temp1 = vars->x1 * cos(mlx.gama) - vars->y1 * sin(mlx.gama);
	vars->y0 = vars->x0 * sin(mlx.gama) + vars->y0 * cos(mlx.gama);
	vars->y1 = vars->x1 * sin(mlx.gama) + vars->y1 * cos(mlx.gama);
	vars->x0 = temp;
	vars->x1 = temp1;
}

void	ft_rotation(t_vars *vars, t_mlx mlx, char rotation_type)
{
	if (rotation_type == 'x')
		x_rotaion(vars, mlx);
	if (rotation_type == 'y')
		y_rotaion(vars, mlx);
	if (rotation_type == 'z')
		z_rotaion(vars, mlx);
}
