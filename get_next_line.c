/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:42:37 by apaterno          #+#    #+#             */
/*   Updated: 2024/03/07 12:42:43 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

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

int	dealloclst(t_list **lista)
{
	char	*rest;
	t_list	*node;

	node = checkline(*lista);
	if (node == NULL)
	{
		lstclean(lista);
		return (1);
	}
	rest = lstnextnode(node);
	lstclean(lista);
	if (rest[0] == '\0')
	{
		free(rest);
		return (1);
	}
	if (!lstappend(lista, rest))
		return (0);
	return (1);
}

char	*next_line(t_list **lista)
{
	char	*nextline;
	int		i;
	int		k;
	t_list	*tmp;

	nextline = ft_calloc(nextline_len(*lista) + 1, sizeof(char));
	if (!nextline)
		return (NULL);
	k = 0;
	tmp = *lista;
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

	while (!checkline(*list))
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (0);
		chread = read(fd, buffer, BUFFER_SIZE);
		if (chread < 0)
			return (free(buffer), 0);
		if (chread == 0)
			return (free(buffer), 1);
		if (!lstappend(list, buffer))
			return (free(buffer), 0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*lista;
	char			*nextline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &nextline, 0) < 0)
		return (lstclean(&lista), NULL);
	if (!addtolist(&lista, fd))
		return (lstclean(&lista), NULL);
	if (!lista)
		return (NULL);
	nextline = next_line(&lista);
	if (!dealloclst(&lista))
		return (lstclean(&lista), NULL);
	return (nextline);
}
