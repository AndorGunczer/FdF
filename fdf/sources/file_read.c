/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:02:07 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/24 16:15:00 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/fdf.h"

// void	get_params(char *file_name, int *x, int *y)
// {
// 	int		fd;
// 	char	**str;
// 	int		i;

// 	i = 0;
// 	fd = open(file_name, O_RDONLY);
// 	if (fd < 0)
// 		terminate(ERR_NO_MAP);
// 	str = ft_split(get_next_line(fd), ' ');
// 	if (!str)
// 		terminate(ERR_FILE_EMPTY);
// 	if (str)
// 		(*y)++;
// 	while (str[i])
// 	{
// 		(*x)++;
// 		i++;
// 	}
// 	ft_single_free(str);
// 	while (get_next_line(fd))
// 	{
// 		(*y)++;
// 	}
// 	close(fd);
// }

// void	set_line(struct s_fdf *data, char *file_name)
// {
// 	int		i;
// 	int		j;
// 	char	**arr;
// 	int		fd;

// 	i = 0;
// 	fd = open(file_name, O_RDONLY);
// 	while (i < data->height)
// 	{
// 		arr = ft_split(get_next_line(fd), ' ');
// 		if (!arr)
// 			terminate(ERR_NO_SPACE);
// 		data->matrix[i] = ft_calloc(sizeof(int), data->width);
// 		j = 0;
// 		while (j < data->width && arr && *(arr + j) != '\0')
// 		{
// 			data->matrix[i][j] = ft_atoi(arr[j]);
// 			j++;
// 		}
// 		ft_double_free(arr);
// 		i++;
// 	}
// 	close(fd);
// }

// void	set_matrix(struct s_fdf *data, char *file_name)
// {
// 	get_params(file_name, &data->width, &data->height);
// 	data->matrix = ft_calloc(sizeof(int *), data->height + 1);
// 	set_line(data, file_name);
// }

///////////////////////////////

#include "../includes/fdf.h"

static int	array_len(char **arr)
{
	int i;

	i = 0;
	while(*arr)
	{
		arr++;
		i++;
	}
	return(i);
}

t_list	*get_params(char *file_name, int *x, int *y)
{
    int     fd;
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
		lst = ft_lstnew(get_next_line(fd));
		ft_lstadd_back(&temp, lst);
    	(*y)++;
    }
	(*y)--;
	close(fd);
	return (lst_start);
}

void	set_line(struct s_fdf *data, t_list *lst)
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

void     set_matrix(struct s_fdf *data, char *file_name)
{
    int     line;
	t_list	*lst_start;

    line = 0;
    lst_start = get_params(file_name, &data->width, &data->height);
	data->matrix = ft_calloc(sizeof(int *), data->height + 1);
	set_line(data, lst_start);
}