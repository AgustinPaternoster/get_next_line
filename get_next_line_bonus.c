/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:39:26 by apaterno          #+#    #+#             */
/*   Updated: 2024/03/11 10:39:36 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*lstnextnode(t_list *node)
{
	char	*rest;
	int		i;
	int		k;

	i = 0;
	k = 0;
	rest = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!rest)
		return (NULL);
	while (node->strbuff[i] != '\n')
		i++;
	i++;
	while (node->strbuff[i])
		rest[k++] = node->strbuff[i++];
	return (rest);
}

int	dealloclst(t_list **lista, int fd)
{
	char	*rest;
	t_list	*node;

	node = checkline(lista[fd]);
	if (node == NULL)
	{
		lstclean(lista, fd);
		return (1);
	}
	rest = lstnextnode(node);
	lstclean(lista, fd);
	if (rest[0] == '\0')
	{
		free(rest);
		return (1);
	}
	if (!lstappend(lista, rest, fd))
		return (0);
	return (1);
}

char	*next_line(t_list **lista, int fd)
{
	char	*nextline;
	int		i;
	int		k;
	t_list	*tmp;

	nextline = ft_calloc(nextline_len(lista[fd]) + 1, sizeof(char));
	if (!nextline)
		return (NULL);
	k = 0;
	tmp = lista[fd];
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->strbuff[i] && tmp->strbuff[i] != '\n')
			nextline[k++] = tmp->strbuff[i++];
		if (tmp->strbuff[i] == '\n')
			nextline[k++] = '\n';
		tmp = tmp->next;
	}
	return (nextline);
}

int	addtolist(t_list **list, int fd)
{
	int		chread;
	char	*buffer;

	while (!checkline(list[fd]))
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (0);
		chread = read(fd, buffer, BUFFER_SIZE);
		if (chread < 0)
			return (free(buffer), 0);
		if (chread == 0)
			return (free(buffer), 1);
		if (!lstappend(list, buffer, fd))
			return (free(buffer), 0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*lista[OPEN_MAX];
	char			*nline;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, &nline, 0) < 0)
		return (lstclean(lista, fd), NULL);
	if (!addtolist(lista, fd))
		return (lstclean(lista, fd), NULL);
	if (lista[fd] == NULL)
		return (NULL);
	nline = next_line(lista, fd);
	if (!dealloclst(lista, fd))
		return (lstclean(lista, fd), NULL);
	return (nline);
}
