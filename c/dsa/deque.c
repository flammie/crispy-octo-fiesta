
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

typedef struct dequeitem dequeitem_t;

struct dequeitem {
    void* data;
    dequeitem_t* next;
    dequeitem_t* prev;
};

typedef struct deque {
    dequeitem_t* first;
    dequeitem_t* last;
} deque_t;

dequeitem_t* dequeitem_new(void* data) {
    dequeitem_t* rv = malloc(sizeof(dequeitem_t));
    rv->data = data;
    rv->next = NULL;
    rv->prev = NULL;
    return rv;
}

void dequeitem_delete(dequeitem_t* di) {
    free(di);
}

deque_t* deque_new() {
    deque_t* rv = malloc(sizeof(deque_t));
    rv->first = NULL;
    rv->last = NULL;
    return rv;
}

void deque_delete(deque_t* d) {
    dequeitem_t* p = d->first;
    while (p != NULL) {
        dequeitem_t* next = p->next;
        dequeitem_delete(p);
        p = next;
    }
    free(d);
}

void deque_push_back(deque_t* d, void* data) {
    dequeitem_t* newlast = dequeitem_new(data);
    dequeitem_t* oldlast = d->last;
    if (oldlast == NULL) {
        d->first = newlast;
        d->last = newlast;
    }
    else {
        oldlast->next = newlast;
        newlast->prev = oldlast;
        d->last = newlast;
    }
}

void* deque_pop_front(deque_t* d) {
    dequeitem_t* oldfirst = d->first;
    void* rv = oldfirst->data;
    d->first = d->first->next;
    if (d->first != NULL) {
        d->first->prev = NULL;
    }
    else {
        d->last = NULL;
    }
    dequeitem_delete(oldfirst);
    return rv;
}

void deque_push_front(deque_t* d, void* data) {
    dequeitem_t* newfront = dequeitem_new(data);
    dequeitem_t* oldfront = d->first;
    if (oldfront == NULL) {
        d->first = newfront;
        d->last = newfront;
    }
    else {
        oldfront->prev = newfront;
        newfront->next = oldfront;
        d->first = newfront;
    }
}

void* deque_pop_back(deque_t* d) {
    dequeitem_t* oldlast = d->last;
    void* rv = oldlast->data;
    d->last = d->last->prev;
    if (d->last != NULL) {
        d->last->next = NULL;
    }
    else {
        d->first = NULL;
    }
    dequeitem_delete(oldlast);
    return rv;
}

int main(int argc, char** argv) {
    deque_t* s = deque_new();
    printf("pushing back: ");
    for (int i = 0; i < argc; i++) {
        printf("%d %s... ", i, argv[i]);
        deque_push_back(s, argv[i]);
    }
    printf("popping back: ");
    for (int i = argc; i > 0; i--) {
        void* data = deque_pop_back(s);
        printf("%d %s... ", i, (char*)data);
    }
    printf("\n");
    printf("pushing front: ");
    for (int i = 0; i < argc; i++) {
        printf("%d %s... ", i, argv[i]);
        deque_push_front(s, argv[i]);
    }
    printf("popping front: ");
    for (int i = argc; i > 0; i--) {
        void* data = deque_pop_front(s);
        printf("%d %s... ", i, (char*)data);
    }
    printf("\n");
    deque_delete(s);
}
