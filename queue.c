#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - o elemento deve existir
// - o elemento nao deve estar em outra fila //Dúvida em como fazer essa função

void queue_append(queue_t** queue, queue_t* elem){
    // Verifica se a fila existe
    // printf("Entro nessa funcao");
    // if(queue == NULL){
    //     fprintf(stderr, "Erro: A fila deve existir.\n");
    // }
    // // Verifica se o elemento existe
    // else if( elem == NULL){
    //     fprintf(stderr, "Erro: O elemento deve existir.\n");
    // }
    // else{
    //     //Insere o elemento no final da fila 
    //     printf("Vai inserir um elemento");
    //     queue_t* last = (*queue)->prev;
    //     printf("Achou o ultimo elemento");
    //     last->next = elem;
    //     elem->prev = last;
    //     elem->next = *queue;
    //     (*queue)->prev = elem;
    // }   
    // queue_t* fila_matriz = *queue;
    // while (fila_matriz != NULL) {
    //     queue_t* aux = fila_matriz;
    //     while (aux != NULL) {
    //         if (aux == elem) {
    //             printf("O elemento estah na fila\n");
    //             break;
    //         }
    //         aux = aux->next;
    //     }
        
    //     fila_matriz = fila_matriz->next;
    // }
    
    // (*queue)->prev;
    // aux->next = elem;
    // elem->prev = last;
    // elem->next = *queue;
}

//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia //Dúvida: qual a diferença entre uma fila que não existe e uma fila nao vazia?
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: apontador para o elemento removido, ou NULL se erro

queue_t *queue_remove (queue_t **queue, queue_t *elem){
    // Verifica se a fila existe
    if(queue == NULL){
        fprintf(stderr, "Erro: A fila deve existir.\n");
        return;
    }
    // Verifica se o elemento existe
    else if( elem == NULL){
        fprintf(stderr, "Erro: O elemento deve existir.\n");
        return;
    }
    else{
        // Verifica se o elemento pertence à fila indicada
        int elem_belongs_to_queue = 0;
        queue_t* current = *queue;
        do {
            if (current == elem) {
                elem_belongs_to_queue = 1;
                queue_t* removed = elem;
                queue_t* removed_next = removed->next;
                queue_t* removed_prev = removed->prev;
                removed_next->prev = removed_prev;
                removed_prev->next = removed_next; 
                return removed;
            }
            current = current->next;
        } while (current != NULL);

        if (!elem_belongs_to_queue) {
            fprintf(stderr, "Erro: O elemento não pertence à fila indicada.\n");
            return;
        }      
    }
}

//------------------------------------------------------------------------------
// Conta o numero de elementos na fila
// Retorno: numero de elementos na fila

int queue_size (queue_t *queue) {
    int count = 0;
    queue_t * head = queue;
    if(queue == NULL){
        return count;
    }
    else{
        while(head != NULL){
            count++;
            head = head->next;
        }
        return count;
    }
}

//------------------------------------------------------------------------------
// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir

void queue_print (char *name, queue_t *queue, void print_elem (void*) ){
    printf("Conteúdo da fila %s:\n", name);

    if (queue == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    queue_t* current = queue;
    do {
        // Chama a função externa para imprimir o elemento atual
        print_elem(current);

        current = current->next;
    } while (current != NULL);

    printf("\n");
}