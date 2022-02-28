/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:07:17 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/28 08:48:25 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*treat_altitiude(int *numbers, char **splited_line)
{
	int		j;

	j = 0;
	while (splited_line[j])
	{
		numbers[j] = ft_atoi(splited_line[j]);
		free(splited_line[j]);
		j++;
	}
	return (numbers);
}

int	**get_numbers(char **lines, int h, int w)
{
	int		**numbers;
	char	**splited_line;
	int		i;

	i = 0;
	numbers = malloc(8 * h);
	while (i < h)
	{
		splited_line = ft_split(lines[i], ' ');
		numbers[i] = malloc(4 * w);
		numbers[i] = treat_altitiude(numbers[i], splited_line);
		free(splited_line);
		i++;
	}
	return (numbers);
}

int	*treat_color(int *colors, char **splited_line)
{
	int		j;
	int		var;
	int		i;

	j = 0;
	while (splited_line[j])
	{
		if (ft_strchr(splited_line[j], ','))
		{
			i = 0;
			while (splited_line[j][i] != ',')
				i++;
			if (splited_line[j][i + 1] == '0' && (splited_line[j][i + 2] == 'x'
					|| splited_line[j][i + 2] == 'X'))
				var = convert_hex(&splited_line[j][i + 3]);
			else if (ft_isdigit(splited_line[j][i + 1]))
				var = ft_atoi(&splited_line[j][i + 1]);
			else
				var = 0;
		}
		else
			colors[j] = 16777215;
		j++;
	}
	return (colors);
}

int	**get_colors(char **lines, int h, int w)
{
	int		**colors;
	char	**splited_line;
	int		i;

	i = 0;
	colors = malloc(8 * h);
	while (i < h)
	{
		splited_line = ft_split(lines[i], ' ');
		colors[i] = malloc (4 * w);
		colors[i] = treat_color(colors[i], splited_line);
		free(splited_line);
		i++;
	}
	return (colors);
}
