/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:41:57 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/21 15:22:39 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

// static void	ft_putchar_fdr(char c, int fd)
// {
// 	write(fd, &c, 1);
// }

// static void	ft_putstr_fdr(char *s, int fd)
// {
// 	while (*s)
// 	{
// 		ft_putchar_fdr(*s, fd);
// 		s++;
// 	}
// }

static int	position_ofn(char *str, int i, int goal)
{
	if (goal == 1)
	{
		while (*(str + i) != '\0')
		{
			if (*(str + i) == '\n')
				return (i);
			i++;
		}
		return (i);
	}
	else if (goal == 2)
	{
		while (*str != '\0')
		{
			if (*str == '\n')
				return (1);
			str++;
		}
		return (0);
	}
	else
		return (0);
}

static char	*output_int(struct s_list *statics, char *result)
{
	if (statics->warehouse[statics->j] == '\n')
		return (result);
	else if (statics->warehouse[statics->j] == '\0')
	{
		free(statics->warehouse);
		statics->warehouse = 0;
		statics->i = 0;
		statics->j = 0;
		statics->custom = 0;
		return (result);
	}
	else
	{
		free(statics->warehouse);
		statics->warehouse = 0;
		statics->i = 0;
		statics->j = 0;
		statics->custom = 0;
		return (NULL);
	}
}

static char	*reader_helper(int fd, int *readcount, char *temp, char *str)
{
	int		newline;

	while (*readcount > 0)
	{
		temp = gnl_strjoin(temp, str);
		newline = position_ofn(str, 0, 2);
		if (newline == 1)
			break ;
		if (str)
			free(str);
		str = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
		*readcount = read(fd, str, BUFFER_SIZE);
	}
	free(str);
	return (temp);
}

static char	*reader(int fd, char *warehouse, int *readcount)
{
	char	*str;
	char	*temp;

	str = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	*readcount = read(fd, str, BUFFER_SIZE);
	// if (*readcount > 0)
	// {
	if (*readcount == -1 || (*readcount == 0 && !warehouse))
	{
		free(str);
		return (NULL);
	}
	temp = gnl_strdup("");
	if (!warehouse && readcount > 0)
		warehouse = gnl_strdup("");
	temp = reader_helper(fd, readcount, temp, str);
	warehouse = gnl_strjoin(warehouse, temp);
	if (temp != NULL)
		free(temp);
	if (!warehouse)
		return (NULL);
	// }
	// else
	// 	free(str);
	return (warehouse);
}

char	*get_next_line(int fd)
{
	static struct s_list	statics;
	char					*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (statics.readcount > 0 || statics.custom == 0)
	{	
		statics.warehouse = reader(fd, statics.warehouse, &statics.readcount);
		statics.custom = 1;
	}
	if (statics.readcount == 0 && !statics.warehouse)
		return (NULL);
	if (!statics.warehouse)
		return (NULL);
	statics.j = position_ofn(statics.warehouse, statics.i, 1);
	result = gnl_substr(statics.warehouse, statics.i, statics.j - statics.i + 1);
	statics.i = statics.j + 1;
	return (output_int(&statics, result));
}
