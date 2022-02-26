/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:07:17 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/13 00:08:58 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

int **get_numbers(char **lines, int h, int w)
{
	int **numbers;
	char **splited_line;
	char **temp;
	int i = 0;
	int j;


	numbers = malloc(8 * h);
	while(i < h)
	{
		j = 0;
		splited_line = ft_split(lines[i], ' ');
		numbers[i] = malloc(4 * w);
		while(splited_line[j])
		{
			if (ft_strchr(splited_line[j], ','))
			{
				temp = ft_split(splited_line[j], ',');
				numbers[i][j] = ft_atoi(temp[0]);
				free(temp);
			}
			else
				numbers[i][j] = ft_atoi(splited_line[j]);
			j++;
		}
		free(splited_line);
		i++;
	}
	return(numbers);
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

int convert_hex(char *hex)
{
	int temp;
	int decimal = 0;
	int len;
	int i;

	i = 0;
	len = ft_strlen(hex) - 1;
	while(hex[i])
	{
		if(hex[i]>='0' && hex[i]<='9')
		{
			temp = hex[i] - 48;
		}
		else if(hex[i]>='a' && hex[i]<='f')
		{
			temp = hex[i] - 97 + 10;
		}
		else if(hex[i]>='A' && hex[i]<='F')
		{
			temp = hex[i] - 65 + 10;
		}
		decimal += temp * pow(16, len);
		i++;
		len--;
	}
	return(decimal);
}

int **get_colors(char **lines, int h, int w)
{
	int **colors;
	char **temp;
	char **splited_line;
	int i = 0;
	int j;
	int var;

	colors = malloc(8 * h);
	while(i < h)
	{
		j = 0;
		splited_line = ft_split(lines[i], ' ');
		colors[i] = malloc (4 * w);
		while(splited_line[j])
		{
			if (ft_strchr(splited_line[j], ','))
			{
				temp = ft_split(splited_line[j], ',');
				var = convert_hex(&temp[1][2]);
				colors[i][j] = var;
			}
			else
			{
				var = 16777215;
				colors[i][j] = var;
			}
			j++;
		}
		free(splited_line);
		i++;
	}
	return(colors);
}
int get_width(char *line)
{
	char **temp;
	int i = 0;
	
	temp = ft_split(line, ' ');
	while(temp[i])
		i++;
	return(i);
}