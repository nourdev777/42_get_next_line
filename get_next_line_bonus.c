/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:45:51 by numussan          #+#    #+#             */
/*   Updated: 2022/05/24 18:43:35 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_put_reminder_to_buff(char *remainder, char *buff)
{
	char	*temp;

	if (remainder)
	{
		temp = ft_strdup(++remainder);
		free(buff);
		buff = ft_strdup(temp);
		free(temp);
	}
	else
	{
		free(buff);
		buff = NULL;
	}
	return (buff);
}

char	*ft_result_line(char *buff)
{
	int		i;
	char	*result;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	result = (char *)malloc((sizeof(char) * i) + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		result[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		result[i++] = '\n';
	result[i] = '\0';
	return (result);
}

char	*ft_read_file_and_find_remainder(int fd, char *buff, char **remainder)
{
	char		*new_buff;
	ssize_t		bytes_read;
	char		*temp_buff;

	new_buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new_buff)
		return (NULL);
	bytes_read = 1;
	while (remainder[0] == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, new_buff, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		new_buff[bytes_read] = '\0';
		temp_buff = buff;
		buff = ft_strjoin(buff, new_buff);
		free(temp_buff);
		remainder[0] = ft_strchr(buff);
	}
	free(new_buff);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char		*buff[1024];
	char			*result;
	char			*remainder;

	remainder = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (0);
	buff[fd] = ft_read_file_and_find_remainder(fd, buff[fd], &remainder);
	if (!buff[fd])
		return (NULL);
	if (*buff[fd] == '\0')
	{
		free (buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	result = ft_result_line(buff[fd]);
	buff[fd] = ft_put_reminder_to_buff(remainder, buff[fd]);
	return (result);
}
