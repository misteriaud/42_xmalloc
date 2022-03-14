/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmemory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:07:01 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/14 18:41:17 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef enum {
	FALSE = 0,
	TRUE = 1
}		t_bool;

typedef struct s_alloc {
	void			*ptr;
	size_t			size;
	struct s_alloc *next;
}				t_alloc;

typedef struct s_node {
	int				group;
	t_alloc			*first;
	struct s_node	*next;
}				t_node;

void	ft_bzero(void *s, size_t n);
void	ft_memcpy(void *dest, const void *src, size_t n);

t_node	**get_first_node();
t_node	*new_node(t_node **first, int group);
t_node	*get_node(int group);

t_alloc **get_first_alloc(int group);
t_alloc *new_alloc(t_alloc **first, size_t size);

void	*Xmalloc(size_t size, int group, t_bool set2zero);
void	*Xrealloc(int group, void *ptr, size_t size, t_bool set2zero);

void	Xfree(int group, void *ptr);
void	Xfree_group(int group);
void	Xfree_all();
