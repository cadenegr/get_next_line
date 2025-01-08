/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:01:46 by cadenegr          #+#    #+#             */
/*   Updated: 2023/08/30 13:33:08 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_next(char *stat)
{
	int		i;
	int		j;
	char	*str_next;

	i = 0;
	j = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == 0)
		return (NULL);
	i++;
	while (stat[i + j])
		j++;
	str_next = malloc (j + 1);
	if (!str_next)
		return (NULL);
	j = 0;
	while (stat[i + j])
	{
		str_next[j] = stat[i + j];
		j++;
	}
	str_next[j] = '\0';
	return (str_next);
}

char	*ft_line(char *stat)
{
	char	*str_line;
	int		i;

	i = 0;
	if (stat[i] == 0)
		return (NULL);
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	str_line = malloc (i + 1);
	if (!str_line)
		return (NULL);
	i = 0;
	while (stat[i] != 0 && stat[i] != '\n')
	{
		str_line[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
		str_line[i++] = '\n';
	str_line[i] = 0;
	return (str_line);
}

char	*ft_read(int fd, char *stat)
{
	char	*buffer;
	int		byte_read;

	byte_read = 1;
	while (!ft_strchr(stat, '\n') && byte_read != 0)
	{
		buffer = malloc (BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		byte_read = read (fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free (stat);
			free (buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[byte_read] = '\0';
		stat = ft_strjoin(stat, buffer);
		free (buffer);
		buffer = NULL;
	}
	return (stat);
}

char	*get_next_line(int fd)
{
	static char	*stat[FD_MAX];
	char		*line;
	char		*next;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return (NULL);
	stat[fd] = ft_read(fd, stat[fd]);
	if (stat[fd] == NULL)
		return (NULL);
	line = ft_line(stat[fd]);
	next = stat[fd];
	stat[fd] = ft_next(stat[fd]);
	free(next);
	next = NULL;
	return (line);
}
/*
int main(void)
{
	int 	fd1;
	int		fd2;
	char	*theline;

	fd1 = open ("first", O_RDONLY, 0777);
	fd2 = open ("second", O_RDONLY, 0777);
	if (fd1 == -1)
		printf("couldn't open");
	theline = get_next_line(fd1);
	printf("output = %s\n", theline);
	theline = get_next_line(fd1);
	printf("output = %s\n", theline);
	theline = get_next_line(fd2);
	printf("output = %s\n", theline);
	theline = get_next_line(fd1);
	printf("output = %s\n", theline);
	theline = get_next_line(fd1);
	printf("output = %s\n", theline);
	theline = get_next_line(fd2);
	printf("output = %s\n", theline);
	theline = get_next_line(fd2);
	printf("output = %s\n", theline);
	theline = get_next_line(fd2);
	printf("output = %s\n", theline);
	theline = get_next_line(fd1);
	printf("output = %s\n", theline);
	theline = get_next_line(fd2);
	printf("output = %s\n", theline);
	free (theline);
	return (0);
}*/

// int main(void)
// {
//     int fd1, fd2, fd3, fd4;
//     char *theline1 = NULL;
// 	char *theline2 = NULL;
// 	char *theline3 = NULL;
// 	char *theline4 = NULL;

//     int line_number1 = 1;
// 	int line_number2 = 1;
// 	int line_number3 = 1;
// 	int line_number4 = 1;

//     fd1 = open("Psalm23.txt", O_RDONLY);
// 		if (fd1 == -1)
// 	{
// 		printf("couldn't open first file\n");

// 	}
// 	fd2 = open("Psalm91.txt", O_RDONLY);
// 		if (fd2 == -1)
// 	{
// 		printf("couldn't open second file\n");

// 	}
// 	fd3 = open("Psalms121.txt", O_RDONLY);
// 		if (fd3 == -1)
// 	{
// 		printf("couldn't open third file\n");

// 	}
// 	fd4 = open("Whatever.txt", O_RDONLY);
// 		if (fd4 == -1)
// 	{
// 		printf("couldn't open fourth file\n");

// 	}

//     while (1)
// 	{
// 		theline1 = get_next_line(fd1);
// 		if (theline1 == NULL)
// 		{
// 			printf("FILE1 ended!\n");
// 		}
// 		printf("File1 Line %d: %s\n", line_number1++, theline1);
// 		free(theline1);
// 		theline2 = get_next_line(fd2);
// 		if (theline2 == NULL)
// 		{
// 			printf("FILE2 ended\n");
// 		}
// 		printf("File2 Line %d: %s\n", line_number2++, theline2);
// 		free(theline2);
// 		theline3 = get_next_line(fd3);
// 		if (theline3 == NULL)
// 		{
// 			printf("FILE3 ended\n");
// 		}
// 		printf("File3 Line %d: %s\n", line_number3++, theline3);
// 		free(theline3);
// 		theline4 = get_next_line(fd4);
// 		if (theline4 == NULL)
// 		{
// 			printf("FILE4 ended\n");
// 		}
// 		printf("File4 Line %d: %s\n", line_number4++, theline4);
// 		free(theline4);
// 	    if (!theline1 && !theline2 && !theline3 && !theline4)
// 		{
//         // All files have reached their end, exit the loop
//         break;
//     	}
// 	}
//     close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);

//     return (0);
// }
/*
int main(void)
{
    char *input_line;
	if ((input_line = get_next_line(STDIN_FILENO)) != NULL)
        // Process the input_line
        {
        	printf("You entered: %s\n", input_line);
	        free(input_line);
	}
    return 0;
}*/
