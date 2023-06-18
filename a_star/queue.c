#include <stdlib.h>
#include <stdio.h>
#include "queue.h"



struct queue_t* init_queue() {
	struct queue_t* new_q = (struct queue_t*)malloc(sizeof(struct queue_t));

	new_q->head = NULL;
	new_q->size = 0;

	return new_q;
}


void queue_add(struct queue_t* q, void* value, int priority) {
	struct queue_node_t* new_node = (struct queue_node_t*)malloc(sizeof(struct queue_node_t));
    new_node->next = NULL;
    new_node->value = value;
    new_node->priority = priority;

    q->size++;

    if(q->head == NULL) {
        q->head = new_node;
    }

    else {
        struct queue_node_t* curr = q->head;

        if(priority < curr->priority) {
            new_node->next = curr;
            q->head = new_node;
            return;
        }

        for(; curr->next != NULL && priority > curr->next->priority; curr = curr->next);
        new_node->next = curr->next;
        curr->next = new_node;
    }
}


void* queue_remove(struct queue_t* q) {
    if(q->head == NULL) return NULL;

    void* last_head = (void*)malloc(sizeof(void));
    last_head = q->head->value;
    struct queue_node_t* temp = q->head->next;
    free(q->head);
    q->head = temp;
    q->size--;


    return last_head;
}

int change_node_priority (struct queue_t* q, void* node, int new_priority){
    int is_in_queue = 0;
    struct queue_node_t* curr = q->head;

    if(node != q->head->value) {
        for(int i = 0; i < q->size && curr->next != NULL; i++, curr = curr->next) {
            if(node == curr->next->value) {
                is_in_queue = 1;
                break;
            }
        }

        if(is_in_queue) {
            if(curr->next->next != NULL) {
                struct queue_node_t* temp = curr->next->next;
                free(curr->next);
                curr->next = temp;
            }
            else
                curr->next = NULL;

            q->size--;
        }
    }
    else queue_remove(q);

    queue_add(q, node, new_priority);

    return is_in_queue;
}

void print_queue(struct queue_t* q) {
    if(q->head == NULL) return;
    struct queue_node_t* curr = q->head;
    for(int i = 0; i < q->size; i++, curr = curr->next) {
        printf("^%d, ", curr->priority);
    }

    printf("\n\n\n");
}
