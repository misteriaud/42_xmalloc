#include <stdio.h>
#include <stdlib.h>
#include "libmemory.h"
#include <string.h>

#define UNIT_TESTS 100
#define MAX_MALLOC_SIZE 1024

typedef struct {
	char *ptr;
	size_t size;
	int	group;
}			t_test;

void fill_xmalloc(t_test elem, size_t offset, char c)
{
	size_t i = offset;

	while (i < elem.size - 1)
	{
		elem.ptr[i] = c;
		i++;
	}
}

int main()
{
	int i;
	printf("// UNIT TESTING FOR libmemory //\n");
	char *str_tmp;
	size_t temp;
	char 	c = 'a';
	int strcmp_result;

	// xmalloc tests
	printf("\nTEST1 : Allocation of %d (maxsize: %d) in the same group\n", UNIT_TESTS, MAX_MALLOC_SIZE);
	t_test	test1[UNIT_TESTS];
	ft_bzero(test1, sizeof(*test1) * UNIT_TESTS);
	i = -1;
	while (++i < UNIT_TESTS)
	{
		test1[i].size = (rand() % MAX_MALLOC_SIZE - 1) + 1;
		if(!xmalloc(&test1[i].ptr, test1[i].size, 1))
		{
			fprintf(stderr, "XMALLOC ERROR\n");
			return (1);
		}
		fill_xmalloc(test1[i], 0, c);
		printf("xmalloc %d of size %ld ok\n", i, test1[i].size);
	}
	printf("OK\n");

	printf("\nTEST2 : Allocation of %d (maxsize: %d) in different group\n", UNIT_TESTS, MAX_MALLOC_SIZE);
	t_test test2[UNIT_TESTS];
	ft_bzero(test2, sizeof(*test2) * UNIT_TESTS);
	i = -1;
	while (++i < UNIT_TESTS)
	{
		test2[i].size = (rand() % MAX_MALLOC_SIZE - 1) + 1;
		test2[i].group = test2[i].size;
		if(!xmalloc(&test2[i].ptr, test2[i].size, test2[i].size))
		{
			fprintf(stderr, "XMALLOC ERROR\n");
			return (1);
		}
		fill_xmalloc(test2[i], 0, c);
		printf("xmalloc %d of size %ld ok\n", i, test2[i].size);
	}
	printf("OK\n");

	// xrealloc tests
	printf("\nTEST3 : Reallocation of test1\n");
	for (size_t j = 0; j < 10; j++)
	{
		c++;
		printf("XREALLOC n%ld\n", j + 1);
		i = -1;
		while (++i < UNIT_TESTS)
		{
			str_tmp = strdup(test1[i].ptr);
			temp = test1[i].size;
			test1[i].size += rand() % MAX_MALLOC_SIZE;
			printf("xrealloc of %d from %ld to %ld\n", i, temp, test1[i].size);
			if(!xrealloc(&test1[i].ptr, test1[i].size, 1))
			{
				fprintf(stderr, "XREALLOC ERROR\n");
				return (1);
			}
			printf("old: %s\nnew: %s\n", str_tmp, test1[i].ptr);
			if ((strcmp_result = strncmp(str_tmp, test1[i].ptr, temp)) != 0)
			{
				fprintf(stderr, "xrealloc %d didn't copy well on the first %ld bytes (%d)\n", i, temp, strcmp_result);
				return (1);
			}
			fill_xmalloc(test1[i], temp - 1, c);
			free(str_tmp);
		}
	}
	printf("OK\n");

	c='b';
	printf("\nTEST4 : Reallocation of test2\n");
	for (size_t j = 0; j < 10; j++)
	{
		c++;
		printf("XREALLOC n%ld\n", j + 1);
		i = -1;
		while (++i < UNIT_TESTS)
		{
			str_tmp = strdup(test2[i].ptr);
			temp = test2[i].size;
			test2[i].size += rand() % MAX_MALLOC_SIZE;
			printf("xrealloc of %d from %ld to %ld\n", i, temp, test2[i].size);
			if(!xrealloc(&test2[i].ptr, test2[i].size, test2[i].group))
			{
				fprintf(stderr, "XREALLOC ERROR\n");
				return (1);
			}
			printf("old: %s\nnew: %s\n", str_tmp, test2[i].ptr);
			if ((strcmp_result = strncmp(str_tmp, test2[i].ptr, temp)) != 0)
			{
				fprintf(stderr, "xrealloc %d didn't copy well on the first %ld bytes (%d)\n", i, temp, strcmp_result);
				return (1);
			}
			fill_xmalloc(test2[i], temp - 1, c);
			free(str_tmp);
		}
	}
	printf("OK\n");

	printf("FREE_ALL\n");
	xfree_all();

	return 0;
}
