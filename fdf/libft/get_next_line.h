/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:44:00 by agunczer          #+#    #+#             */
/*   Updated: 2021/08/04 10:53:40 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct s_list {
	char	*warehouse;
	int		i;
	int		j;
}	t_list;

char			*get_next_line(int fd);
unsigned int	ft_strlen(const char *s);
char			*gnl_strdup(const char *s1);
char			*gnl_strjoin(char const *s1, char const *s2);
char			*gnl_substr(char const *s, unsigned int start, unsigned int len);
void			*gnl_calloc(unsigned int count, unsigned int size);

#endif