
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

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

ssize_t list_find(list_t* l, void* data) {
    ssize_t rv = -1;
    for (listitem_t* p = l->head; p != NULL; p = p->next) {
        rv++;
        if (p->data == data) {
            return rv;
        }
    }
    return -1;
}

size_t list_size(list_t* l) {
    size_t rv = 0;
    for (listitem_t* p = l->head; p != NULL; p = p->next) {
        rv++;
    }
    return rv;
}

void* list_get(list_t* l, size_t index) {
    listitem_t* p = l->head;
    for (size_t i = 0; i < index; i++) {
        p = p->next;
    }
    return p->data;
}

void list_reverse(list_t* l) {
    listitem_t* p = l->head;
    listitem_t* prev = NULL;
    while (p != NULL) {
        listitem_t* next = p->next;
        p->next = prev;
        prev = p;
        p = next;
    }
    l->head = prev;
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
    printf("list:\n");
    list_printf("%s", l);
    list_reverse(l);
    printf("reversed:\n");
    list_printf("%s", l);
    printf("size: %zu\n", list_size(l));
    if (list_size(l) >= 2) {
        void* second = list_get(l, 1);
        printf("second: %s\n", (const char*)second);
        list_remove(l, 1);
        printf("removed:\n");
        list_printf("%s", l);
    }
    list_delete(l);
}
