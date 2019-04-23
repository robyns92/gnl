/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 12:29:50 by srobin            #+#    #+#             */
/*   Updated: 2019/04/23 15:18:35 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUF_SIZE 4096

char			*readfile(const int fd, char *str)
{
	int			ret;
	char		buf[BUF_SIZE + 1];

	while ((ret = read(fd, buf, BUF_SIZE)))
	{
		buf[ret] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
			str = ft_strjoin(str, buf);
	}
	return (str);
}

int				get_next_line(const int fd, char **line)
{
	static char	*save;
	int			i;
	
//	if (fd == -1 || *line == NULL)
//		return (-1);	
//	save = malloc(sizeof(char) * (BUF_SIZE + 1));
	if (*save)
		*line = ft_strcpy(*line, save);
	save = readfile(fd, save);
	i = 0;
	if (save[i])
	{
		while(save[i] != '\n' && save[i])
			i++;
		if (i == 0)
			*line = ft_strdup("");
		if (i > 0)
		{
			*line = ft_strsub(save, 0, i);
			save = &save[i + 1];
//			ft_putstr(save);
		}
		return (1);
	}
	else
		*line = ft_strdup("");
	return (0);
}

int		main(int argc, char **argv)
{
	char *line;
	int fd;
	int	retour;
	int	i;
	i = 0;
	fd = open(argv[1], O_RDONLY);	
	while ((retour = get_next_line(fd, &line)) != 0)
	{
		i++;
		ft_putendl(line);
	}
	free(line);
	close(fd);
	return (0);
}
