/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmemory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:35:25 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/14 20:37:59 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMEMORY_H

# include <stdlib.h>

typedef enum e_bool {
	false = 0,
	true = 1
}		t_bool;

typedef struct s_alloc {
	void			*ptr;
	size_t			size;
	struct s_alloc	*next;
}				t_alloc;

typedef struct s_node {
	int				group;
	t_alloc			*first;
	struct s_node	*next;
}				t_node;

// ft_bzero.c && ft_memcpy.c
void	ft_bzero(void *s, size_t n);
void	ft_memcpy(void *dest, const void *src, size_t n);

// t_node.c
t_node	**get_first_node(void);
t_node	*new_node(t_node **first, int group);
t_node	*get_node(int group);

// t_alloc.c
t_alloc	**get_first_alloc(int group);
t_alloc	*new_alloc(t_alloc **first, size_t size);
void	xfree_allocs(t_alloc *first);

// libmemory.c
void	*xmalloc(size_t size, int group, t_bool set2zero);
void	*xrealloc(int group, void *ptr, size_t size, t_bool set2zero);
void	xfree(int group, void *ptr);
void	xfree_group(int group);
void	xfree_all(void);

#endif
