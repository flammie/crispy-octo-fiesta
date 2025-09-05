
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

typedef struct queueitem queueitem_t;

struct queueitem {
    void* data;
    queueitem_t* next;
};

typedef struct queue {
    queueitem_t* first;
} queue_t;

queueitem_t* queueitem_new(void* data) {
    queueitem_t* rv = malloc(sizeof(queueitem_t));
    rv->data = data;
    rv->next = NULL;
    return rv;
}

void queueitem_delete(queueitem_t* qi) {
    free(qi);
}

queue_t* queue_new() {
    queue_t* rv = malloc(sizeof(queue_t));
    rv->first = NULL;
    return rv;
}

void queue_delete(queue_t* q) {
    queueitem_t* p = q->first;
    while (p != NULL) {
        queueitem_t* next = p->next;
        queueitem_delete(p);
        p = next;
    }
    free(q);
}

void queue_push(queue_t* q, void* data) {
    queueitem_t* newlast = queueitem_new(data);
    if (q->first == NULL) {
        q->first = newlast;
        return;
    }
    else {
        queueitem_t* prev = NULL;
        for (queueitem_t *p = q->first; p != NULL; p = p->next) {
            prev = p;
        }
        prev->next = newlast;
        return;
    }
    return;
}

void* queue_pop(queue_t* q) {
    queueitem_t* oldfirst = q->first;
    void* rv = oldfirst->data;
    q->first = q->first->next;
    queueitem_delete(oldfirst);
    return rv;
}

int main(int argc, char** argv) {
    queue_t* q = queue_new();
    printf("pushing: ");
    for (int i = 0; i < argc; i++) {
        printf("%d %s... ", i, argv[i]);
        queue_push(q, argv[i]);
    }
    printf("popping: ");
    for (int i = argc; i > 0; i--) {
        void* data = queue_pop(q);
        printf("%d %s... ", i, (char*)data);
    }
    printf("\n");
    queue_delete(q);
}
