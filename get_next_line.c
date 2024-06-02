/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecymer <ecymer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:19:02 by ecymer            #+#    #+#             */
/*   Updated: 2024/05/25 13:24:11 by ecymer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *buffer, char *line)
{
	int		bytes_count;
	char	*tmp;

	bytes_count = 1;
	while (bytes_count > 0)
	{
		bytes_count = read(fd, buffer, BUFFER_SIZE);
		if (bytes_count < 0)
			return (NULL);
		if (bytes_count == 0)
			break ;
		buffer[bytes_count] = '\0';
		if (line == NULL)
			line = ft_strdup("");
		tmp = line;
		line = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	return (line);
}

char	*rest_of_line(char *line)
{
	int		i;
	char	*rest_line;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	rest_line = ft_substr(line, i + 1, ft_strlen(line + i + 1));
	if (rest_line == NULL)
		return (NULL);
	line[i + 1] = '\0';
	return (rest_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest_line = NULL;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	line = read_line(fd, buffer, rest_line);
	free(buffer);
	if (line == NULL)
		return (NULL);
	rest_line = rest_of_line(line);
	return (line);
}

// int main(void)
// {
//     int fd;

//     fd = open("./text.txt", O_RDONLY);
//     get_next_line(15);
//     printf("DUPA: %s\n", get_next_line(15));
//     return (0);
// }
