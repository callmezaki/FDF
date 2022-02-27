/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:44:46 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/27 05:52:18 by zait-sli         ###   ########.fr       */
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

t_mlx	ft_reset(t_mlx mlx)
{
	mlx.altitude = 1;
	mlx.zoom = get_mult(mlx.data, mlx);
	mlx.position_x = 0;
	mlx.position_y = 0;
	mlx.r_type = 'n';
	mlx.iso_validity = 1;
	mlx.alpha = 0.8;
	mlx.beta = 0.8;
	mlx.gama = 0.8;
	return (mlx);
}

int	key_hook(int key, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_addr);
	mlx->img = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	if (key == ESC)
	{
		write(1, "Bye!\n", 6);
		exit(0);
	}
	if (key == KEY_R)
		*mlx = ft_reset(*mlx);
	if (key == PLUS)
		mlx->altitude += 1;
	if (key == MINUSE)
		mlx->altitude -= 1;
	if (key == RIGHT)
		mlx->position_x += 10;
	if (key == LEFT)
		mlx->position_x -= 10;
	if (key == DOWN)
		mlx->position_y += 10;
	if (key == UP)
		mlx->position_y -= 10;
	if (key == KEY_X || key == KEY_S)
	{
		mlx->r_type = 'x';
		if (key == KEY_X)
			mlx->alpha += 0.1;
		else
			mlx->alpha -= 0.1;
	}
	if (key == KEY_C || key == KEY_D)
	{
		mlx->r_type = 'y';
		if (key == KEY_C)
			mlx->beta += 0.1;
		else
			mlx->beta -= 0.1;
	}
	if (key == KEY_Z || key == KEY_A)
	{
		mlx->r_type = 'z';
		if (key == KEY_Z)
			mlx->gama += 0.1;
		else
			mlx->gama -= 0.1;
	}
	if (key == KEY_P)
	{
		if (mlx->iso_validity == TRUE)
			mlx->iso_validity = FALSE;
		else
			mlx->iso_validity = TRUE;
	}
	projection(mlx->data, mlx);
	return (0);
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

t_vars	ft_rotation(t_vars vars, t_mlx mlx, char rotation_type)
{
	int	temp;
	int	temp1;

	if (rotation_type == 'x')
	{
		temp = vars.y0 * cos(mlx.alpha) + vars.z0 * sin(mlx.alpha);
		temp1 = vars.y1 * cos(mlx.alpha) + vars.z1 * sin(mlx.alpha);
		vars.z0 = -vars.y0 * cos(mlx.alpha) + vars.z0 * sin(mlx.alpha);
		vars.z1 = -vars.y1 * cos(mlx.alpha) + vars.z1 * sin(mlx.alpha);
		vars.y0 = temp;
		vars.y1 = temp1;
	}
	if (rotation_type == 'y')
	{
		temp = vars.x0 * cos(mlx.beta) + vars.z0 * sin(mlx.beta);
		temp1 = vars.x1 * cos(mlx.beta) + vars.z1 * sin(mlx.beta);
		vars.z0 = -vars.x0 * cos(mlx.beta) + vars.z0 * sin(mlx.beta);
		vars.z1 = -vars.x1 * cos(mlx.beta) + vars.z1 * sin(mlx.beta);
		vars.x0 = temp;
		vars.x1 = temp1;
	}
	if (rotation_type == 'z')
	{
		temp = vars.x0 * cos(mlx.gama) - vars.y0 * sin(mlx.gama);
		temp1 = vars.x1 * cos(mlx.gama) - vars.y1 * sin(mlx.gama);
		vars.y0 = vars.x0 * cos(mlx.gama) + vars.y0 * sin(mlx.gama);
		vars.y1 = vars.x1 * cos(mlx.gama) + vars.y1 * sin(mlx.gama);
		vars.x0 = temp;
		vars.x1 = temp1;
	}
	return (vars);
}

int	mouse_press(int key, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_addr);
	mlx->img = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	if (key == SCROLL_UP && mlx->zoom >= 0)
		mlx->zoom += 1;
	if (key == SCROLL_DOWN && mlx->zoom > 0)
		mlx->zoom -= 1;
	projection(mlx->data, mlx);
	return (0);
}

int	ft_destroy(t_mlx *mlx)
{
	(void)mlx;
	write(1, "Bye!\n", 6);
	exit(0);
	return (0);
}
