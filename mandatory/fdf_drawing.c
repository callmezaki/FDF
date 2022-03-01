/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 06:41:15 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 05:57:35 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	two_lines_draw(int x, int y, t_vars *vars, t_mlx *mlx)
{
	if (x < mlx->data.width - 1)
	{
		vars->x0 = x;
		vars->y0 = y;
		vars->x1 = x + 1;
		vars->y1 = y;
		draw_line(vars,*mlx, mlx->data.colors[y][x], mlx->data);
	}
	if (y < mlx->data.height - 1)
	{
		vars->x0 = x;
		vars->y0 = y;
		vars->x1 = x;
		vars->y1 = y + 1;
		draw_line(vars,*mlx, mlx->data.colors[y][x], mlx->data);
	}
}

void	projection(t_data data, t_mlx *mlx)
{
	int		x;
	int		y;
	t_vars	*vars;

	y = 0;
	vars = (t_vars *)malloc(sizeof(t_vars));
	get_pad(vars, *mlx);
	while (y < data.height)
	{
		x = 0;
		while (x < data.width)
		{
			two_lines_draw(x, y, vars, mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	free(vars);
}

void	draw_line(t_vars *vars, t_mlx mlx, int color, t_data data)
{
	t_math	*math;

	math = (t_math *)malloc(sizeof(t_math *));
	vars->z0 = data.numbers[vars->y0][vars->x0];
	vars->z1 = data.numbers[vars->y1][vars->x1];
	if (data.z_size != 0 && data.case_size != 0)
	{
		vars->z0 *= data.z_size;
		vars->z1 *= data.z_size;
	}
	handle_zoom_center(vars, mlx, data);
	ft_iso(vars);
	padding(vars);
	bresenham(vars, mlx, *math, color);
	free(math);
}

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

void	get_pad(t_vars *vars, t_mlx mlx)
{
	int	x;
	int	y;

	x = cos(1.0472) * (mlx.data.height * mlx.zoom);
	y = sin(0.523599) * (mlx.data.width * mlx.zoom);
	vars->pad_x = 1920 - (x + y);
	vars->pad_x = vars->pad_x / 2;
	vars->pad_x += fmin(x, y) * 1.2;
	x = cos(0.523599) * (mlx.data.width * mlx.zoom);
	y = sin(0.523599) * (mlx.data.height * mlx.zoom);
	vars->pad_y = 1080 - (x + y);
	vars->pad_y = vars->pad_y / 2;
	vars->pad_y += fmax(x, y) * 0.8;
}
