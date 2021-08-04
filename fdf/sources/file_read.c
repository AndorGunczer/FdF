/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:02:07 by agunczer          #+#    #+#             */
/*   Updated: 2021/08/04 20:09:20 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This program reads the fdf file's contents into a 2D matrix

** The 2D matrix defines the dimensions of the projection (height - Y-axis && width - X-axis) **
** Every number of the Matrix equals to the height of the graph **

*/

/* 	// NEWLINE[HEIGHT] = get_next_line(fd)
	// WHILE (NEWLINE)
	// 	HEIGHT++
	// 	NEWLINE[HEIGHT] = get_next_line(fd) */

#include "../includes/fdf.h"

static int	array_len(char **arr)
{
	int i;

	i = 0;
	while(*arr != NULL)
	{
		arr++;
		i++;
	}
	return(i);
}

t_list	*get_params(char *file_name, struct t_fdf *data, int *x, int *y) //works
{
    int     fd;
	char	*str;
	t_list	*lst_start;
	t_list	*lst;
	t_list	*temp;

    fd = open(file_name, O_RDONLY);
	lst_start = ft_lstnew(get_next_line(fd));
	temp = lst_start;
	lst = ft_lstnew("smtg");
	if (lst_start->content)
	{
		*x = array_len(ft_split(lst_start->content, ' '));
		(*y)++;
	}
    while (lst->content != NULL)
    {
		printf("%s", lst->content);
		// printf("START POINTER: %p | START CONTENT %s\n", lst_start->next, lst_start->content);
		// printf("START POINTER: %p | START CONTENT %s\n", lst->next, lst->content);
		lst = ft_lstnew(get_next_line(fd));
		ft_lstadd_back(&temp, lst);
    	(*y)++;
    }
	(*y)--;
	printf("\nWIDTH: %d | HEIGHT: %d", data->width, data->height);
	close(fd);
	return (lst_start);
}

void	set_line(struct t_fdf *data, t_list *lst, char *file_name)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	data->matrix = ft_calloc(sizeof(int *), data->height);
	while (i < data->height)
	{
		arr = ft_split(lst->content, ' ');
		if (lst->next != NULL)
			lst = lst->next;
		// printf("TIMEs");
		data->matrix[i] = ft_calloc(sizeof(int), data->width);
		j = 0;
		while (j < data->width && arr && *arr)
		{
			data->matrix[i][j] = ft_atoi(*arr);
			arr++;
			j++;
		}
		i++;
	}
}

void     set_matrix(struct t_fdf *data, char *file_name)
{
    int     cnt;
    int     line;
	t_list	*lst_start;

    line = 0;
    lst_start = get_params(file_name, data, &data->width, &data->height);
	// while (lst_start->next != NULL)
	// {
	// 	printf("%s", lst_start->next->content);
	// 	lst_start = lst_start->next;
	// }
	data->matrix = ft_calloc(sizeof(int *), data->height + 1);
	set_line(data, lst_start, file_name);
	for (int i = 0; i < data->height && printf("\n"); i++ )
		for(int c = 0; c < data->width; c++)
			printf("%i ", data->matrix[i][c]);
}