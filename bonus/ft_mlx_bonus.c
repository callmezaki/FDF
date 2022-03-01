/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 06:50:14 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 07:59:10 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	print_keymap(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 710, 11520457,
		"KEY MAP");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 760, 11520457,
		"Activate random colors : space bar                |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 790, 11520457,
		"Parallel view : 'P'                               |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 820, 11520457,
		"Reset to defult : 'R'                             |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 850, 11520457,
		"Zoom in : scroll up , zoom out : scroll down      |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 880, 11520457,
		"Move up : arrow up , move down : arrow down       |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 910, 11520457,
		"Move right : arrow right , move left : arrow left |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 940, 11520457,
		"X rotation : + with 'X' , - with 'S'              |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 970, 11520457,
		"Y rotation : + with 'C' , - with 'D'              |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 1000, 11520457,
		"Z rotation : + with 'Z' , - with 'A'              |");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 1030, 11520457,
		"Altitude : + with '+' , - with '-'                |");
}

void	print_variables(t_mlx *mlx, t_vars *vars)
{
	char	*temp;

	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 100, 40, 11520457,
		temp = ft_itoa(mlx->zoom));
	free(temp);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 70, 11520457,
		temp = ft_itoa(vars->pad_x + mlx->p_x));
	free(temp);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 70, 11520457,
		temp = ft_itoa(vars->pad_x + mlx->p_x));
	free(temp);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 100, 11520457,
		temp = ft_itoa(vars->pad_y + mlx->p_y));
	free(temp);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 130, 11520457,
		temp = ft_itoa(mlx->altitude));
	free(temp);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 130, 11520457,
		temp = ft_itoa(mlx->altitude));
}

void	ft_strings(t_mlx *mlx, t_vars *vars)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 920, 10, 11520457,
		"Map name : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1040, 10, 11520457,
		mlx->data.map_name);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 10, 11520457, "INFO");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 40, 11520457, "ZOOM :");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 70, 11520457,
		"X posintion : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 100, 11520457,
		"Y posintion : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 130, 11520457,
		"Altitude : ");
	print_variables(mlx, vars);
	print_keymap(mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img_addr + (y * mlx->line_length + x
			* (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
