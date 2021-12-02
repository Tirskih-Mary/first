#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Stack;

Stack init_stack(){
	Stack* st = malloc(sizeof(Stack));
	st->data = malloc(4 * sizeof(int));
	st->size = 0;
	st->capacity = 4;
	return *st;
}

int pop_stack(Stack *st){	//Удаляет элемент со стека и возвращает его
	int n = st->data[st->size - 1];
	st->size--;
	if (st->capacity > 4 && 4 * st->size < st->capacity){
		st->capacity = st->capacity / 2;
		st->data = realloc(st->data, st->capacity * sizeof(int));}
	return n;
}

void put_stack(Stack *st, int value){	//Добавляет элемент на стек
	st->data[st->size] = value;
	st->size++;
	if (st->size == st->capacity){
		st->capacity = st->capacity * 2;
		st->data = realloc(st->data, st->capacity * sizeof(int));}
}

struct QueueStack{
    Stack s1;
    Stack s2;
};

typedef struct QueueStack QueueStack;

QueueStack queuestack_init(){
	Stack s1 = init_stack();
	Stack s2 = init_stack();
	QueueStack q = {s1, s2};
	return q;
}

void enqueuestack(QueueStack* q, int value){	// Добавление значения в очередь
	put_stack(&q->s1, value);
}

int dequeuestack(QueueStack* q){	// Удаление значения из очереди
	if (!q->s2.size){
		size_t size = q->s1.size;
		for(size_t i = 0; i < size; i++){
			put_stack(&q->s2, pop_stack(&q->s1));}}
	return pop_stack(&q->s2);
}



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

typedef struct List QueueList;

QueueList queuelist_init() {
    return list_init();
}

void enqueuelist(QueueList* q, int value){	// Добавление значения в очередь
	list_push_back(q, value);
}

int dequeuelist(QueueList* q){	// Удаление значения из очереди
	return list_pop_front(q);
}



int main() {
	
	for (int size = 10; size <= 100000; size = size * 10){
	
		QueueStack qstack = queuestack_init();
		clock_t start1 = clock();
		for (int i = 1; i < size; ++i) enqueuestack(&qstack, i * i);
		int s;
		for (int i = 1; i < size; ++i) s = dequeuestack(&qstack);
		clock_t end1 = clock();
		float secondsstack = (float)(end1 - start1)*1000000 / CLOCKS_PER_SEC;
		
		QueueList qlist = queuelist_init();
		clock_t start2 = clock();
		for (int i = 1; i < size; ++i) enqueuelist(&qlist, i * i);
		int l;
		for (int i = 1; i < size; ++i) l = dequeuelist(&qlist);
		clock_t end2 = clock();
		float secondslist = (float)(end2 - start2)*1000000 / CLOCKS_PER_SEC;
		
		printf("%6d ->\t", size);
		printf("QueueStack: %f\t", secondsstack/size);
		printf("QueueList: %f\n", secondslist/size);}
    return 0;
}
