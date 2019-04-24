/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:33:46 by srobin            #+#    #+#             */
/*   Updated: 2019/04/24 16:37:46 by srobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*find_end_line(const int fd, char *str)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
		{
			tmp = str;
			str = ft_strjoin(str, buf);
			free(tmp);
		}
		if (ft_strchr(str, '\n'))
			return (str);
	}
	return (str);
}

static char		*cut_to_next_line(char *str, int i)
{
	char	*tmp;

	tmp = str;
	str = ft_strdup(&str[i + !!str[i]]);
	free(tmp);
	return (str);
}

int				get_next_line(const int fd, char **line)
{
	static char *(str[OPEN_MAX]);
	int			i;

	if (fd < 0 || fd > OPEN_MAX || !line || read(fd, NULL, 0) < 0)
		return (-1);
	if (!(str[fd] = find_end_line(fd, str[fd])))
		return (0);
	i = 0;
	if (str[fd][i])
	{
		while (str[fd][i] != '\n' && str[fd][i])
			i++;
		if (i == 0)
		{
			*line = ft_strdup("");
			str[fd] = cut_to_next_line(str[fd], i);
		}
		if (i > 0)
		{
			*line = ft_strsub(str[fd], 0, i);
			str[fd] = cut_to_next_line(str[fd], i);
		}
		return (1);
	}
	return (0);
}

int     main(int argc, char **argv)
{
	char *line;
	int fd;
	int retour;
	int i;
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
