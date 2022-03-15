/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmemory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:07:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/15 15:46:44 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmemory.h"

int	xmalloc(void **ptr, size_t size, int group)
{
	t_alloc	**first;
	t_alloc	*dest;

	first = get_first_alloc(group);
	dest = new_alloc(first, size);
	if (!dest)
		return (0);
	ft_bzero(dest->ptr, size);
	*ptr = dest->ptr;
	return (1);
}

int	xrealloc(void **ptr, size_t size, int group)
{
	t_alloc	**first;
	t_alloc	*curr;
	t_alloc	*dest;

	if (!*ptr)
		return (xmalloc(ptr, size, group));
	first = get_first_alloc(group);
	curr = *first;
	while (curr && curr->ptr != *ptr)
		curr = curr->next;
	if (!curr)
		return (xmalloc(ptr, size, group));
	dest = new_alloc(first, size + curr->size);
	if (!dest)
		return (0);
	ft_memcpy(dest->ptr, curr->ptr, curr->size);
	ft_bzero(dest->ptr + curr->size, size);
	*ptr = dest->ptr;
	xfree(group, curr->ptr);
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
