
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct listitem listitem_t;

struct listitem {
    void* data;
    listitem_t* next;
};

typedef struct list {
    listitem_t* head;
} list_t;

listitem_t* listitem_new(void* data) {
    listitem_t* rv = malloc(sizeof(listitem_t));
    rv->data = data;
    rv->next = NULL;
    return rv;
}

void listitem_delete(listitem_t* li) {
    free(li);
}

list_t* list_new() {
    list_t* rv = malloc(sizeof(list_t));
    rv->head = NULL;
    return rv;
}

void list_delete(list_t* l) {
    listitem_t* prev = NULL;
    for (listitem_t* p = l->head; p != NULL; p = p->next) {
        listitem_delete(prev);
        prev = p;
    }
    listitem_delete(prev);
    free(l);
}

void list_insert(list_t* l, void* data, size_t index) {
    if (index == 0) {
        listitem_t* oldhead = l->head;
        l->head = listitem_new(data);
        l->head->next = oldhead;
        return;
    }
    listitem_t* p = l->head;
    listitem_t* prev = NULL;
    for (size_t i = 0; i < index; i++) {
        prev = p;
        p = p->next;
    }
    prev->next = listitem_new(data);
    prev->next->next = p;
}

void list_remove(list_t* l, size_t index) {
    if (index == 0) {
        listitem_t* oldhead = l->head;
        l->head = l->head->next;
        listitem_delete(oldhead);
        return;
    }
    listitem_t* p = l->head;
    listitem_t* prev = NULL;
    for (size_t i = 0; i < index; i++) {
        prev = p;
        p = p->next;
    }
    prev->next = p->next;
    listitem_delete(p);
}

void list_printf(const char* fmt, list_t* l) {
    printf("[");
    bool first = true;
    for (listitem_t* p = l->head; p != NULL; p = p->next) {
        if (!first) {
            printf(", ");
        }
        printf(fmt, p->data);
        first = false;
    }
    printf("]\n");
}

int main(int argc, char** argv) {
    list_t* l = list_new();
    for (int i = 0; i < argc; i++) {
        list_insert(l, argv[i], i);
    }
    list_printf("%s", l);
    list_delete(l);
}
