#include <stdio.h>
#include <stdlib.h>
#include "libmemory.h"

#define UNIT_TESTS 100
#define MAX_MALLOC_SIZE 1024

int error(char *s)
{
	printf("%s\n", s);
	return (1);
}

int main()
{
	printf("// UNIT TESTING FOR libmemory //\n");

	// xmalloc tests
	printf("Allocation of %d (")
	char *str[100];
	int i = -1;
	while (++i < UNIT_TESTS)
		if(xmalloc(&str[i], (rand() % MAX_MALLOC_SIZE - 1) + 1))
			return (error("MALLOC ERROR"));

	return 0;
}
