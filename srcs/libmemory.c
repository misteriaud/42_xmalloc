/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmemory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:07:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/16 17:07:36 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmemory.h"

int	xmalloc(void *ptr, size_t size, int group)
{
	t_alloc	**first;
	t_alloc	*dest;
	void	**data;

	data = (void **)ptr;
	first = get_first_alloc(group);
	dest = new_alloc(first, size);
	if (!dest)
		return (0);
	ft_bzero(dest->ptr, size);
	*data = dest->ptr;
	return (1);
}

int	xrealloc(void *ptr, size_t size, int group)
{
	t_alloc	**first;
	t_alloc	*curr;
	void	*dest;
	void	**data;

	data = (void **)ptr;
	if (!*data)
		return (xmalloc(ptr, size, group));
	first = get_first_alloc(group);
	curr = *first;
	while (curr && curr->ptr != *data)
		curr = curr->next;
	if (!curr)
		return (xmalloc(ptr, size, group));
	dest = malloc(size + curr->size);
	if (!dest)
		return (0);
	ft_memcpy(curr->ptr, dest, curr->size);
	ft_bzero(dest + curr->size, size);
	free(curr->ptr);
	curr->ptr = dest;
	*data = curr->ptr;
	return (1);
}

void	xfree_all(void)
{
	t_node	**first;
	t_node	*to_remove;

	first = get_first_node();
	if (!*first)
		return ;
	while (*first)
	{
		to_remove = *first;
		*first = to_remove->next;
		xfree_allocs(to_remove->first);
		free(to_remove);
	}
}
