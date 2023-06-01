#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


Stack* stack_init() {
    Stack* s = (Stack*) malloc(sizeof(Stack));

    s->head = NULL;
    s->tail = NULL;

    return s;
};


unsigned int stack_size(Stack* s) {
    Stack_node* node = s->head;
    unsigned int size = 0;

    for (; node != NULL; node = node->next, size++);

    return size;
};


void stack_push(Stack* s, void* value) {
    if (s->head == NULL) {

        s->tail = s->head = (Stack_node*) malloc(sizeof(Stack_node));
        s->head->data = value;
        s->head->next = s->head->prev = NULL;

        return;
    }

    s->head->prev = (Stack_node*) malloc(sizeof(Stack_node));
    
    s->head->prev->next = s->head;
    s->head = s->head->prev;

    s->head->data = value;
    s->head->prev = NULL;

};


void* stack_pop(Stack* s) {
    Stack_node* node = s->head;

    if (node == NULL) {
        printf("ERROR! Stack is empty!\n");
        return NULL;
    }

    Stack_node* removed_node = node;
    void* returned_value = node->data;

    s->head = node = node->next;
    node->prev = NULL;


    free(removed_node);
    return returned_value;
};


int stack_contains(Stack* s, void* value) {
    Stack_node* node = s->head;

    for (; node != NULL; node = node->next) {
        if (node->data == value)  return 1;
    };
    
    return 0;
};


void* stack_at(Stack* s, unsigned int index) {
    Stack_node* node = s->head;

    for (unsigned int i = 0; node != NULL && i <= index; node = node->next, i++) {
        if(i == index) return node->data;
    }

    printf("ERROR! Index out of Stack!\n");
    return NULL;
};


void stack_clear(Stack* s) {
    Stack_node* node = s->head;
    for (Stack_node* node_next; node != NULL; node = node_next) {
        node_next = node->next;
        free(node);
    }

    s->head = NULL;
};


void stack_destroy(Stack* s) {
    Stack_node* node = s->head;
    for (Stack_node* node_next; node != NULL; node = node_next) {
        node_next = node->next;
        free(node);
    }

    free(s);
};


void stack_print(Stack* s) {
    for(int i = 0; i < stack_size(s); i++)
    	printf("Stack[%d] = %d\n", i, *((int*)stack_at(s, i)));

};