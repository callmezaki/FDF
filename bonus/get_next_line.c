/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:16:39 by zait-sli          #+#    #+#             */
/*   Updated: 2022/02/09 19:08:44 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include<unistd.h>

char	*read_buff(int fd, char *rs)
{
	int		a;
	char	*buff;

	buff = malloc(sizeof(char) * 1000001);
	if (!buff)
		return (NULL);
	a = 1;
	while (a && !ft_strchr(rs, '\n'))
	{
		a = read(fd, buff, 1000000);
		if (a == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[a] = '\0';
		rs = ft_strjoin(rs, buff);
	}
	free(buff);
	return (rs);
}

char	*get_line(char *rs)
{
	int		i;
	char	*line;

	i = 0;
	if (!rs[i])
		return (NULL);
	while (rs[i] != '\n' && rs[i])
		i++;
	if (rs[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (rs[i] != '\n' && rs[i])
	{
		line[i] = rs[i];
		i++;
	}
	if (rs[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_new_rest(char *rs)
{
	int		lenrs;
	char	*newrs;
	int		i;

	i = 0;
	lenrs = 0;
	while (rs[i] != '\0' && rs[i] != '\n')
		i++;
	if (!rs[i])
	{
		free(rs);
		return (NULL);
	}
	i++;
	lenrs = ft_strlen(&rs[i]);
	newrs = malloc(lenrs + 1);
	if (!newrs)
		return (NULL);
	lenrs = 0;
	while (rs[i])
		newrs[lenrs++] = rs[i++];
	newrs[lenrs] = '\0';
	free(rs);
	return (newrs);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rs;

	if (fd < 0)
		return (NULL);
	rs = read_buff(fd, rs);
	if (!rs)
		return (NULL);
	line = get_line(rs);
	rs = get_new_rest(rs);
	return (line);
}
