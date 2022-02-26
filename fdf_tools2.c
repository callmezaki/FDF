/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:44:46 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/26 06:12:19 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"fdf.h"

void check_map(t_data data)
{
	int i = 0;
	int len = 0;
	char **temp;
	
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
	while(data.lines[i])
	{
		len = 0;
		temp = ft_split(data.lines[i], ' ');
		while(temp[len])
			len++;
		if (len != data.width)
		{
			printf("Invalid map.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

t_mlx ft_reset(t_mlx mlx)
{
	mlx.altitude = 1;
	mlx.zoom	= 0;
	mlx.position_x	= 0;
	mlx.position_y	= 0;
	return(mlx);
} 

int	key_hook(int key, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr,mlx->img_addr);
	mlx->img = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	if (key == esc)
		exit(0);
	if (key == key_r)
		*mlx = ft_reset(*mlx);
	if(key == plus)
		mlx->altitude += 1;
	if(key == minuse)
		mlx->altitude -= 1;
	if(key == key_i)
		mlx->zoom += 1;
	if(key == key_o)
		mlx->zoom -= 1;
	if (key == right)
		mlx->position_x += 10;
	if (key == left)
		mlx->position_x -= 10;
	if (key == down)
		mlx->position_y += 10;
	if (key == up)
		mlx->position_y -= 10;
	if (key == key_x)
		mlx->r_type = 'x';
	if (key == key_p)
	{
		if (mlx->iso_validity == true)
			mlx->iso_validity = false;
		else
			mlx->iso_validity = true;
	}
	projection(mlx->data,mlx);
	return (0);
}

t_vars get_mult(t_data data, t_vars vars, int zoom)
{
	int n;
	if (data.height > 400 || data.width > 400)
		n = 2;
	else if (data.height > 200 || data.width > 200)
		n = 3;
	else if (data.height > 99 || data.width > 99)
		n = 4;
	else if (data.height > 50 || data.width > 50)
		n = 20;
	else
		n = 25;
	if (data.z_size != 0 && data.case_size != 0)
		n = data.case_size;
	vars.y0 *= n + zoom;
	vars.y1 *= n + zoom;
	vars.x0 *= n + zoom;
	vars.x1 *= n + zoom;
	return(vars);
}




// t_vars ft_rotation(t_vars vars , char rotation_type)
// {
// 	int t_y0;
// 	int t_y1;
// 	if (rotation_type == 'x')
// 	{
// 		t_y0 = vars.y0 * cos(0.8) + vars.z0 * sin(0.8);
// 		t_y1 = vars.y1 * cos(0.8) + vars.z1 * sin(0.8);
		
// 		vars.z0 = -vars.y0 * cos(0.8) + vars.z0 * sin(0.8);
// 		vars.z1 = -vars.y1 * cos(0.8) + vars.z1 * sin(0.8);
// 		vars.y0 = t_y0;
// 		vars.y0 = t_y1;
// 	}
	
// 	return(vars);
// }