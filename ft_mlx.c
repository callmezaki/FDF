/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 06:50:14 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 00:22:43 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_keymap(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 740, 11520457,
		"KEY MAP");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 790, 11520457,
		"parallel view : 'P'                               |");
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

void	ft_strings(t_mlx *mlx, t_vars *vars)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 920, 10, 11520457,
		"Map name : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 1040, 10, 11520457,
		mlx->data.map_name);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 10, 11520457, "INFO");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 40, 11520457, "ZOOM :");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 100, 40, 11520457,
		ft_itoa(mlx->zoom));
	if (mlx->zoom == 0)
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 120, 40, 16711680,
			"You can't zoom out any more!");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 70, 11520457,
		"X posintion : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 70, 11520457,
		ft_itoa(vars->pad_x + mlx->p_x));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 100, 11520457,
		"Y posintion : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 100, 11520457,
		ft_itoa(vars->pad_y + mlx->p_y));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 30, 130, 11520457,
		"Altitude : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 130, 11520457,
		ft_itoa(mlx->altitude));
	print_keymap(mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->img_addr + (y * mlx->line_length + x
			* (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
