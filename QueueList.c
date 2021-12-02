#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

struct ListNode{
    int value;
    struct ListNode* next;
};

typedef struct ListNode ListNode;

struct List{
    size_t size;
    ListNode* head;
    ListNode* tail;
};

typedef struct List List;

List list_init() {
    List l = {0, NULL, NULL};
    return l;
}

ListNode* init_listnode(int value, ListNode* next) {
    ListNode* newnode = malloc(sizeof(ListNode));
    newnode->value = value;
    newnode->next = next;
    return newnode;
}

void list_push_back(List* list, int value){
	if (list == NULL) return;
	ListNode* newtail = init_listnode(value, NULL);
	if (!list->size){
		list->tail = newtail;
		list->head = newtail;
		++list->size;}
	else{
		list->tail->next = newtail;
		list->tail = newtail;
		++list->size;}
}

int list_pop_front(List* l) {
    if (l == NULL || !l->size) return 0;
    ListNode* current_head = l->head;
    int value = current_head == NULL ? 0 : current_head->value;
    l->head = l->head->next;
    free(current_head);
    if (!--l->size) l->tail = NULL;
    return value;
}

typedef struct List Queue;

Queue queue_init() {
    return list_init();
}

void enqueue(Queue* q, int value){
	list_push_back(q, value);
}

int dequeue(Queue* q){
	return list_pop_front(q);
}




int main() {
    Queue q = queue_init();
    for (int i = 1; i < 10; ++i) enqueue(&q, i * i);
    for (int i = 1; i < 10; ++i) printf("%d ", dequeue(&q));
    putchar('\n');
    return 0;
}
