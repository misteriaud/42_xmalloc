/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:30:25 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/14 18:37:27 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libmemory.h"

t_node	**get_first_node()
{
	static t_node	*first;

	return (&first);
}

t_node	*new_node(t_node **first, int group)
{
	t_node *dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->next = *first;
	dest->group = group;
	dest->first = NULL;
	*first = dest;
	return (dest);
}

t_node	*get_node(int group)
{
	t_node	**first;
	t_node	*curr;

	first = get_first_node();
	curr = *first;
	while (curr)
	{
		if (curr->group == group)
			return (curr);
		curr = curr->next;
	}
	return(new_node(first, group));
}

void Xfree_group(int group)
{
	t_node	**first;
	t_node	*curr;
	t_node	*to_remove;

	first = get_first_node();
	if (*first && (*first)->group == group)
	{
		to_remove = *first;
		*first = to_remove->next;
		Xfree_allocs(to_remove->first);
		free(to_remove);
		return ;
	}
	curr = *first;
	while (curr && curr->next->group != group)
		curr = curr->next;
	if (!curr->next)
		return ;
	to_remove = curr->next;
	curr->next = to_remove->next;
	Xfree_allocs(to_remove->first);
	free(to_remove);
}
