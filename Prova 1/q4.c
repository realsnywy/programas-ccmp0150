#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Tarefa
{
    char *descricao;
    struct Tarefa *next;
} Tarefa;

typedef struct Fila
{
    Tarefa *front;
    Tarefa *rear;
} Fila;

Fila *criarFilaTarefa()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->front = f->rear = NULL;
    return f;
}

void enfileirarTarefa(Fila *f, char *descricao)
{
    Tarefa *newNode = (Tarefa *)malloc(sizeof(Tarefa));
    newNode->descricao = strdup(descricao);
    newNode->next = NULL;

    if (f->rear == NULL)
    {
        f->front = f->rear = newNode;
    }
    else
    {
        f->rear->next = newNode;
        f->rear = newNode;
    }
}

Tarefa *desenfileirarTarefa(Fila *f)
{
    if (f->front == NULL)
        return NULL;

    Tarefa *temp = f->front;
    f->front = f->front->next;

    if (f->front == NULL)
    {
        f->rear = NULL;
    }

    return temp;
}

bool filaTarefaVazia(Fila *f)
{
    return f->front == NULL;
}

typedef struct GerenciadorTarefas
{
    Fila *prioritaria;
    Fila *comum;
} GerenciadorTarefas;

GerenciadorTarefas *criarGerenciador()
{
    GerenciadorTarefas *g = (GerenciadorTarefas *)malloc(sizeof(GerenciadorTarefas));
    g->prioritaria = criarFilaTarefa();
    g->comum = criarFilaTarefa();
    return g;
}

void adicionarTarefaComum(GerenciadorTarefas *g, char *descricao)
{
    enfileirarTarefa(g->comum, descricao);
}

void adicionarTarefaPrioritaria(GerenciadorTarefas *g, char *descricao)
{
    enfileirarTarefa(g->prioritaria, descricao);
}

Tarefa *proximaTarefa(GerenciadorTarefas *g)
{
    if (!filaTarefaVazia(g->prioritaria))
    {
        return desenfileirarTarefa(g->prioritaria);
    }
    else if (!filaTarefaVazia(g->comum))
    {
        return desenfileirarTarefa(g->comum);
    }
    return NULL;
}

void liberarGerenciador(GerenciadorTarefas *g)
{
    // Liberar fila prioritária
    while (!filaTarefaVazia(g->prioritaria))
    {
        Tarefa *t = desenfileirarTarefa(g->prioritaria);
        free(t->descricao);
        free(t);
    }
    free(g->prioritaria);

    // Liberar fila comum
    while (!filaTarefaVazia(g->comum))
    {
        Tarefa *t = desenfileirarTarefa(g->comum);
        free(t->descricao);
        free(t);
    }
    free(g->comum);

    free(g);
}

int main()
{
    GerenciadorTarefas *gerenciador = criarGerenciador();

    adicionarTarefaComum(gerenciador, "Atualizar relatório");
    adicionarTarefaPrioritaria(gerenciador, "Corrigir bug crítico");
    adicionarTarefaComum(gerenciador, "Enviar e-mails");
    adicionarTarefaPrioritaria(gerenciador, "Deploy da nova versão");

    Tarefa *tarefa;
    while ((tarefa = proximaTarefa(gerenciador)) != NULL)
    {
        // Simula o processamento da tarefa
        free(tarefa->descricao);
        free(tarefa);
    }

    liberarGerenciador(gerenciador);

    return 0;
}
