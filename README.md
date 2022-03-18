#### Libmemory

*La libmemory est une surcouche à la stdlib sur ses fonction d'allocation de mémoire dans la Heap (malloc et realloc).*

**Elle y ajoute** :
- la gestion de groupe d'allocation de mémoire
- une forme de garbage collector, il suffit d'executer `xfree_all()` en fin de programme ou `xfree_group(...)` en fin d'execution d'une partie de code.

```Shell
# Pour installer utiliser la lib, execuez les commandes suivantes
git clone https://github.com/misteriaud/libmemory.git
make -C libmemory
```

***

#### Prototypes:
```C
// Pour allouer de la memoire :
int		xmalloc(void *ptr, size_t size, int group);
int		xrealloc(void *ptr, size_t size, int group);
int		xmore(void *ptr, size_t size, int group);

// Pour liberer la memoire allouée
void	xfree(void *ptr, int group);
void	xfree_group(int group);
void	xfree_all(void);
```
##### Args:
1. `void *ptr` attend un pointeur sur le pointeur qu'on veut allouer
2. `size_t size` est la taille en byte à allouer (pour `xmalloc` et `xrealloc` elle exprimée en valeur absolue, pour `xmore` en valeur relative par rapport à la memoire déjà allouée)
3. `int group` permet de regrouper des allocations pour pouvoir les libérer par lot ensuite, c'est en identifiant attribué librement (*entre INT_MIN et INT_MAX*)

##### Valeur de retour:
Les fonctions d'allocations retournent **1** si la mémoire a pu être allouée, sinon **0**.

***

##### Example d'utilisation:
```C
#include <string.h>
#include <stdio.h>
#include "libmemory.h"

int main(int ac, char **av)
{
        int i = 0;
        int j;
        int k = -1;
        size_t total_size = 0;
        char *catav = NULL;

        i = 0;
        while (++i < ac)
        {
                total_size += strlen(av[i]);
                if (!xrealloc(&catav, total_size, 1))
                        return (0);
                j = -1;
                while (av[i][++j])
                        catav[++k] = av[i][j];
        }
        if (!xrealloc(&catav, ++k + 1, 1))
                return (0);
        catav[k] = 0;
        printf("Concatenation des arguments : %s\n", catav);
        return (0);
}
```

***

#### Fonctions utilisées:
```C
#include <stdlib.h>

void *malloc(size_t size);
void free(void *ptr);
```
