/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:17:04 by kprasol           #+#    #+#             */
/*   Updated: 2017/12/13 12:51:46 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_type				*ft_newlist(t_type *newlist, int fd)
{
	char	*tmp;

	tmp = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	tmp[BUFF_SIZE] = '\0';
	if (!newlist)
	{
		newlist = (t_type*)ft_lstnew(tmp, (BUFF_SIZE + 1));
		newlist->size = fd;
	}
	free(tmp);
	return (newlist);
}

t_type				*ft_head(t_type *head, int fd)
{
	char	*tmp;

	tmp = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	tmp[BUFF_SIZE] = '\0';
	while (head->size != fd && head->next)
		head = head->next;
	if (head->size != fd)
	{
		head->next = (t_type*)ft_lstnew(tmp, (BUFF_SIZE + 1));
		head = head->next;
		head->size = fd;
	}
	free(tmp);
	return (head);
}

char				*ft_read(char *result, t_type *head, char *tmp)
{
	int				ret;

	while (!(ft_strchr(result, '\n'))
		&& (ret = read(head->size, head->content, BUFF_SIZE)) > 0)
	{
		head->content[ret] = '\0';
		tmp = result;
		result = ft_strjoin(result, head->content);
		free(tmp);
	}
	if (ret == -1)
		return (NULL);
	return (result);
}

int					ft_test(char *result, char *tmp, char **line)
{
	if (!ft_strchr(result, '\n'))
	{
		if (ft_strlen(result) > 0)
		{
			tmp = result;
			*line = ft_strdup(result);
			free(tmp);
			return (1);
		}
		else
			return (0);
	}
	*line = ft_strsub(result, 0, (ft_strchr(result, '\n') - result));
	free(result);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_type	*newlist;
	t_type			*head;
	char			*result;
	char			*b;
	char			*tmp;

	if (!line || BUFF_SIZE < 0 || fd < 0)
		return (-1);
	newlist = ft_newlist(newlist, fd);
	head = newlist;
	if ((head = ft_head(head, fd)) && head == NULL)
		return (-1);
	if (!(b = ft_strchr(head->content, '\n')))
		result = ft_strdup("");
	else
	{
		*b = ' ';
		result = ft_strdup(b + 1);
	}
	tmp = NULL;
	if (!(result = ft_read(result, head, tmp)))
		return (-1);
	if (ft_test(result, tmp, line) == 0)
		return (0);
	return (1);
}
