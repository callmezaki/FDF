/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:44:46 by zait-sli          #+#    #+#             */
/*   Updated: 2022/03/01 06:01:11 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

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

int	get_width(char *line)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_split(line, ' ');
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	return (i);
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

	i = 0;
	decimal = 0;
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
