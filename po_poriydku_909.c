#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    long long int* data;
    size_t size;
    size_t capacity;
} Stack;

Stack init_stack(){
	Stack* st = malloc(sizeof(Stack));
	st->data = malloc(4 * sizeof(long long int));
	st->size = 0;
	st->capacity = 4;
	return *st;
}

int pop_stack(Stack *st){	//Удаляет элемент со стека и возвращает его
	long long int n = st->data[st->size - 1];
	st->size--;
	if (st->capacity > 4 && 4 * st->size < st->capacity){
		st->capacity = st->capacity / 2;
		st->data = realloc(st->data, st->capacity * sizeof(long long int));}
	return n;
}

void put_stack(Stack *st, long long int value){	//Добавляет элемент на стек
	st->data[st->size] = value;
	st->size++;
	if (st->size == st->capacity){
		st->capacity = st->capacity * 2;
		st->data = realloc(st->data, st->capacity * sizeof(long long int));}
}



struct Queue{
    Stack s1;
    Stack s2;
};

typedef struct Queue Queue;

Queue queue_init(){
	Stack s1 = init_stack();
	Stack s2 = init_stack();
	Queue q = {s1, s2};
	return q;
}

void enqueue(Queue* q, int value){	// Добавление значения в очередь
	put_stack(&q->s1, value);
}

int dequeue(Queue* q){	// Удаление значения из очереди
	if (!q->s2.size){
		size_t size = q->s1.size;
		for(size_t i = 0; i < size; i++){
			put_stack(&q->s2, pop_stack(&q->s1));}}
	return pop_stack(&q->s2);
}



void zapolnenie(Stack* s, Queue* q){
	enqueue(q, 9);
	long long int n;
	for (int i = 0; i < 511; i++){
		n = dequeue(q);
		put_stack(s, n);
		enqueue(q, n * 10);
		enqueue(q, n * 10 + 9);}
}

void print_stack(Stack* s){
	for(int i = 0; i < s->size; i++){
		printf ("%9lld\t", s->data[i]);
		if ((i + 1) % 5 == 0)putchar('\n');}
}



int main() {
    Queue q = queue_init();
    Stack s = init_stack();
    zapolnenie(&s, &q);
    print_stack(&s);
    return 0;
}
