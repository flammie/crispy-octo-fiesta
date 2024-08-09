
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

typedef struct listitem listitem_t;

struct listitem {
    void* data;
    listitem_t* prev;
    listitem_t* next;
};

typedef struct list {
    listitem_t* tail;
    listitem_t* head;
} list_t;

listitem_t* listitem_new(void* data) {
    listitem_t* rv = malloc(sizeof(listitem_t));
    rv->data = data;
    rv->next = NULL;
    rv->prev = NULL;
    return rv;
}

void listitem_delete(listitem_t* li) {
    free(li);
}

list_t* list_new() {
    list_t* rv = malloc(sizeof(list_t));
    rv->head = NULL;
    rv->tail = NULL;
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

size_t list_size(list_t* l) {
    size_t rv = 0;
    for (listitem_t* p = l->head; p != NULL; p = p->next) {
        rv++;
    }
    return rv;
}

void list_push(list_t* l, void* data) {
    listitem_t* oldhead = l->head;
    l->head = listitem_new(data);
    l->head->next = oldhead;
    if (l->tail == NULL) {
        l->tail = l->head;
    }
    return;
}

void list_insert(list_t* l, void* data, size_t index) {
    if (index == 0) {
        return list_push(l, data);
    }
    listitem_t* p = l->head;
    listitem_t* prev = NULL;
    for (size_t i = 0; i < index; i++) {
        prev = p;
        p = p->next;
    }
    prev->next = listitem_new(data);
    prev->next->next = p;
    prev->next->prev = prev;
    if (p == NULL) {
        l->tail = prev->next;
    }
}

void list_pop(list_t* l) {
    listitem_t* oldhead = l->head;
    l->head = l->head->next;
    l->head->prev = NULL;
    listitem_delete(oldhead);
}

void list_remove(list_t* l, size_t index) {
    if (index == 0) {
        return list_pop(l);
    }
    listitem_t* p = l->head;
    listitem_t* prev = NULL;
    for (size_t i = 0; i < index; i++) {
        prev = p;
        p = p->next;
    }
    prev->next = p->next;
    if (prev->next != NULL) {
        prev->next->prev = prev;
    }
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

ssize_t list_rfind(list_t* l, void* data) {
    ssize_t rv = list_size(l);
    for (listitem_t* p = l->tail; p != NULL; p = p->prev) {
        rv--;
        if (p->data == data) {
            return rv;
        }
    }
    return -1;
}


void* list_get(list_t* l, size_t index) {
    listitem_t* p = l->head;
    for (size_t i = 0; i < index; i++) {
        p = p->next;
    }
    return p->data;
}

void list_reverse(list_t* l) {
    listitem_t* old_head = l->head;
    l->head = l->tail;
    l->tail = old_head;
    listitem_t* p = old_head;
    while (p != NULL) {
        listitem_t* old_prev = p->prev;
        p->prev = p->next;
        p->next = old_prev;
        p = p->prev;  //prev is old next
    }
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

void list_debug(list_t* l) {
    printf("Debugging list @%p:\n", l);
    printf("Head @%p, tail @%p\n", l->head, l->tail);
    printf("From head to tail:\n");
    for (listitem_t* p = l->head; p != NULL; p = p->next) {
        printf("* listitem @%p: data: @%p, prev: @%p, next: @%p\n", p,
               p->data, p->prev, p->next);
    }
    printf("From tail to head:\n");
    for (listitem_t* p = l->tail; p != NULL; p = p->prev) {
        printf("* listitem @%p, data: @%p, prev: @%p, next: @%p\n", p,
               p->data, p->prev, p->next);
    }
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
        char* needle = "b";
        ssize_t i = list_find(l, &needle);
        printf("found %s at: %zd\n", needle, i);
        i = list_rfind(l, &needle);
        printf("rfound %s at: %zd\n", needle, i);
    }
    list_delete(l);
}
