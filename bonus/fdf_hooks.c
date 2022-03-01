/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 06:00:16 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 05:44:26 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_hooks(int key, t_mlx *mlx)
{
	if (key == KEY_X || key == KEY_S)
	{
		mlx->r_type = 'x';
		if (key == KEY_X)
			mlx->alpha += 0.06;
		else
			mlx->alpha -= 0.06;
	}
	if (key == KEY_C || key == KEY_D)
	{
		mlx->r_type = 'y';
		if (key == KEY_C)
			mlx->beta += 0.06;
		else
			mlx->beta -= 0.06;
	}
	if (key == KEY_Z || key == KEY_A)
	{
		mlx->r_type = 'z';
		if (key == KEY_Z)
			mlx->gama += 0.06;
		else
			mlx->gama -= 0.06;
	}
}

void	translation_hooks(int key, t_mlx *mlx)
{
	if (key == MINUSE)
		mlx->altitude -= 1;
	if (key == RIGHT)
		mlx->p_x += 10;
	if (key == LEFT)
		mlx->p_x -= 10;
	if (key == DOWN)
		mlx->p_y += 10;
	if (key == PLUS)
		mlx->altitude += 1;
	if (key == UP)
		mlx->p_y -= 10;
}

int	key_hook(int key, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_addr);
	mlx->img = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	if (key == ESC)
		ft_last_free(mlx->data, *mlx);
	if (key == KEY_R)
		*mlx = ft_reset(*mlx);
	if (key == KEY_P)
	{
		if (mlx->iso_validity == TRUE)
			mlx->iso_validity = FALSE;
		else
			mlx->iso_validity = TRUE;
	}
	if (key == SPACE_BAR)
	{
		if (mlx->random_colors == TRUE)
			mlx->random_colors = FALSE;
		else
			mlx->random_colors = TRUE;
	}
	translation_hooks(key, mlx);
	rotation_hooks(key, mlx);
	projection(mlx->data, mlx);
	return (0);
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
	ft_last_free(mlx->data, *mlx);
	return (0);
}
