#include <stdio.h>

#define NODE_MAX 5

typedef struct Node
{
    char info;
    int next;
} Node;

Node memory[NODE_MAX];
int avail;

void node_init()
{
    avail = 0;
    for (int i = 0; i < NODE_MAX; i++)
    {
        memory[i].info = '\0';
        memory[i].next = i + 1;
    }
    memory[NODE_MAX - 1].next = -1;
}

int node_alloc()
{
    int ret = -1;
    if (avail != -1)
    {
        ret = avail;
        avail = memory[avail].next;
    }
    return ret;
}

void node_free(int p)
{
    memory[p].next = avail;
    avail = p;
}

void node_print()
{
    printf("avail: %d\n", avail);
    for (int i = avail; i != -1; i = memory[i].next)
    {
        printf("[%d] %d|%d  ->  ", i, memory[i].info, memory[i].next);
    }
    printf("X\n");
}

typedef struct List
{
    int list;
} List;

void insert_front(List *l, char elm)
{
    int p = node_alloc();
    if (p != -1)
    {
        memory[p].info = elm;
        memory[p].next = l->list;
        l->list = p;
    }
}

char remove_front(List *l)
{
    int p = l->list;
    char ret = memory[p].info;
    l->list = memory[p].next;
    node_free(p);
    return ret;
}

void lst_print(List *l)
{
    printf("list:");
    for (int p = l->list; p != -1; p = memory[p].next)
    {
        printf("[%d] %c|%d  ->  ", p, memory[p].info, memory[p].next);
    }
    printf("\n");
}

int main()
{
    List l;
    l.list = -1;

    node_init();

    insert_front(&l, 'A');
    lst_print(&l);
    insert_front(&l, 'B');
    lst_print(&l);
    insert_front(&l, 'C');
    lst_print(&l);
    remove_front(&l);
    lst_print(&l);
    remove_front(&l);
    lst_print(&l);

    return 0;
}