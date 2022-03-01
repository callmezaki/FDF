/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:10:50 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 05:31:09 by zait-sli         ###   ########.fr       */
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
	mlx->data = data;
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
	ft_strings(mlx, vars);
	free(vars);
}

void	draw_line(t_vars *vars, t_mlx mlx, int color, t_data data)
{
	t_math	*math;
	int		r;

	math = (t_math *)malloc(sizeof(t_math *));
	vars->z0 = data.numbers[vars->y0][vars->x0];
	vars->z1 = data.numbers[vars->y1][vars->x1];
	if (data.z_size != 0 && data.case_size != 0)
	{
		vars->z0 *= data.z_size;
		vars->z1 *= data.z_size;
	}
	if (vars->z0 != 0)
		vars->z0 *= mlx.altitude;
	if (vars->z1 != 0)
		vars->z1 *= mlx.altitude;
	handle_zoom_center(vars, mlx, data);
	ft_rotation(vars, mlx, mlx.r_type);
	if (mlx.iso_validity == TRUE)
		ft_iso(vars);
	r = rand();
	if (mlx.random_colors == TRUE && r > 100)
		color = r;
	padding(vars);
	bresenham(vars, mlx, *math, color);
	free(math);
}
