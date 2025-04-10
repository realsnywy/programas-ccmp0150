#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char info;
    struct Node *next;
} Node;

Node *node_alloc()
{
    Node *n = malloc(sizeof(struct Node));
    if (n)
    {
        n->info = '\0';
        n->next = NULL;
    }
    return n;
}

void node_free(Node *n)
{
    free(n);
}

typedef struct List
{
    Node *list;
} List;

List *lst_alloc()
{
    List *l = malloc(sizeof(struct List));
    if (l)
    {
        l->list = NULL;
    }
    return l;
}

void lst_print(List *l)
{
    printf("list:");
    for (Node *p = l->list; p != NULL; p = p->next)
    {
        printf("[%p] %c|%p  ->  ", p, p->info, p->next);
    }
    printf("X \n");
}

void insert_front(List *l, char elm)
{
    Node *n = node_alloc();
    if (n)
    {
        n->info = elm;
        n->next = l->list;
        l->list = n;
    }
}

char remove_front(List *l)
{
    Node *n = l->list;
    char ret = '\0';
    if (n)
    {
        ret = n->info;
        l->list = n->next;
        node_free(n);
    }
    return ret;
}

int main()
{
    List *l = lst_alloc();

    insert_front(l, 'A');
    lst_print(l);
    insert_front(l, 'B');
    lst_print(l);
    insert_front(l, 'C');
    lst_print(l);
    remove_front(l);
    lst_print(l);
    remove_front(l);
    lst_print(l);

    return 0;
}