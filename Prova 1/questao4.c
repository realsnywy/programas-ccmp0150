#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Tarefa
{
    char *descricao;
} Tarefa;

typedef struct NodeFila
{
    Tarefa *tarefa;
    struct NodeFila *next;
} NodeFila;

typedef struct Fila
{
    NodeFila *front;
    NodeFila *rear;
} Fila;

typedef struct GerenciadorTarefas
{
    Fila *filaPrioritaria;
    Fila *filaComum;
} GerenciadorTarefas;

Fila *criarFilaTarefa()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->front = f->rear = NULL;
    return f;
}

void enfileirarTarefa(Fila *f, char *descricao)
{
    NodeFila *newNode = (NodeFila *)malloc(sizeof(NodeFila));
    newNode->tarefa = (Tarefa *)malloc(sizeof(Tarefa));
    newNode->tarefa->descricao = strdup(descricao);
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

    NodeFila *temp = f->front;
    Tarefa *tarefa = temp->tarefa;
    f->front = f->front->next;

    if (f->front == NULL)
    {
        f->rear = NULL;
    }

    free(temp);
    return tarefa;
}

bool filaTarefaVazia(Fila *f)
{
    return f->front == NULL;
}

GerenciadorTarefas *criarGerenciador()
{
    GerenciadorTarefas *g = (GerenciadorTarefas *)malloc(sizeof(GerenciadorTarefas));
    g->filaPrioritaria = criarFilaTarefa();
    g->filaComum = criarFilaTarefa();
    return g;
}

void adicionarTarefaComum(GerenciadorTarefas *g, char *descricao)
{
    enfileirarTarefa(g->filaComum, descricao);
}

void adicionarTarefaPrioritaria(GerenciadorTarefas *g, char *descricao)
{
    enfileirarTarefa(g->filaPrioritaria, descricao);
}

Tarefa *proximaTarefa(GerenciadorTarefas *g)
{
    if (!filaTarefaVazia(g->filaPrioritaria))
    {
        return desenfileirarTarefa(g->filaPrioritaria);
    }
    else if (!filaTarefaVazia(g->filaComum))
    {
        return desenfileirarTarefa(g->filaComum);
    }
    else
    {
        return NULL;
    }
}

void liberarGerenciador(GerenciadorTarefas *g)
{
    // Liberar fila prioritária
    while (!filaTarefaVazia(g->filaPrioritaria))
    {
        Tarefa *t = desenfileirarTarefa(g->filaPrioritaria);
        free(t->descricao);
        free(t);
    }
    free(g->filaPrioritaria);

    // Liberar fila comum
    while (!filaTarefaVazia(g->filaComum))
    {
        Tarefa *t = desenfileirarTarefa(g->filaComum);
        free(t->descricao);
        free(t);
    }
    free(g->filaComum);

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
        printf("Processando: %s\n", tarefa->descricao);
        free(tarefa->descricao);
        free(tarefa);
    }

    liberarGerenciador(gerenciador);
    return 0;
}
