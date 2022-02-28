/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:44:46 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 06:23:12 by zait-sli         ###   ########.fr       */
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

int	get_mult(t_data data, t_mlx mlx)
{
	if (data.height > 400 || data.width > 400)
		mlx.zoom = 2;
	else if (data.height > 200 || data.width > 200)
		mlx.zoom = 3;
	else if (data.height > 99 || data.width > 99)
		mlx.zoom = 4;
	else if (data.height > 50 || data.width > 50)
		mlx.zoom = 20;
	else
		mlx.zoom = 25;
	if (data.z_size != 0 && data.case_size != 0)
		mlx.zoom = data.case_size;
	return (mlx.zoom);
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

int	count_nbr(long long nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
		count++;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

int	convert_hex(char *hex)
{
	int	temp;
	int	decimal;
	int	len;
	int	i;

	decimal = 0;
	i = 0;
	len = ft_strlen(hex) - 1;
	while (hex[i])
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			temp = hex[i] - 48;
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			temp = hex[i] - 97 + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			temp = hex[i] - 65 + 10;
		decimal += temp * pow(16, len);
		i++;
		len--;
	}
	return (decimal);
}
