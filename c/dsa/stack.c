
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

typedef struct stackitem stackitem_t;

struct stackitem {
    void* data;
    stackitem_t* next;
};

typedef struct stack {
    stackitem_t* top;
} stack_t;

stackitem_t* stackitem_new(void* data) {
    stackitem_t* rv = malloc(sizeof(stackitem_t));
    rv->data = data;
    rv->next = NULL;
    return rv;
}

void stackitem_delete(stackitem_t* si) {
    free(si);
}

stack_t* stack_new() {
    stack_t* rv = malloc(sizeof(stack_t));
    rv->top = NULL;
    return rv;
}

void stack_delete(stack_t* s) {
    stackitem_t* p = s->top;
    while (p != NULL) {
        stackitem_t* next = p->next;
        stackitem_delete(p);
        p = next;
    }
    free(s);
}

void stack_push(stack_t* s, void* data) {
    stackitem_t* newtop = stackitem_new(data);
    newtop->next = s->top;
    s->top = newtop;
    return;
}

void* stack_pop(stack_t* s) {
    stackitem_t* oldtop = s->top;
    void* rv = oldtop->data;
    s->top = s->top->next;
    stackitem_delete(oldtop);
    return rv;
}

int main(int argc, char** argv) {
    stack_t* s = stack_new();
    printf("pushing: ");
    for (int i = 0; i < argc; i++) {
        printf("%d %s... ", i, argv[i]);
        stack_push(s, argv[i]);
    }
    printf("popping: ");
    for (int i = argc; i > 0; i--) {
        void* data = stack_pop(s);
        printf("%d %s... ", i, (char*)data);
    }
    printf("\n");
    stack_delete(s);
}
