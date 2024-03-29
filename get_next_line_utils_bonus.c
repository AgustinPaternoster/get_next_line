/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaterno <apaterno@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:40:02 by apaterno          #+#    #+#             */
/*   Updated: 2024/03/11 10:40:09 by apaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

t_list	*checkline(t_list *lista)
{
	int		i;
	t_list	*tmp;

	tmp = lista;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->strbuff[i])
		{
			if (tmp->strbuff[i] == '\n')
				return (tmp);
			i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	lstappend(t_list **lista, char *buff, int fd)
{
	t_list	*node;
	t_list	*tmp;

	if (!buff)
		return (0);
	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->strbuff = buff;
	node->next = NULL;
	tmp = lista[fd];
	if (tmp == NULL)
		lista[fd] = node;
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = node;
	}
	return (1);
}

int	nextline_len(t_list *lista)
{
	int		i;
	int		len;
	t_list	*tmp;

	len = 0;
	tmp = lista;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->strbuff[i])
		{
			if (tmp->strbuff[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		tmp = tmp->next;
	}
	return (len);
}

void	lstclean(t_list **lista, int fd)
{
	t_list	*tmp;
	t_list	*toclean;

	toclean = lista[fd];
	while (toclean != NULL)
	{
		tmp = toclean->next;
		free(toclean->strbuff);
		free(toclean);
		toclean = tmp;
	}
	lista[fd] = NULL;
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	d;
	size_t	i;

	d = count * size;
	p = malloc(d);
	if (!p)
		return (NULL);
	i = 0;
	while (i < d)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
