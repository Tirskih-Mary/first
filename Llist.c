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

void listnode_insert_next(ListNode* node, int value) {
    ListNode* current_next = node->next;
    ListNode* newnode = init_listnode(value, current_next);
    node->next = newnode;
}

void listnode_remove_next(ListNode* node) {
    if (node == NULL || node->next == NULL) return;
    ListNode* current_next = node->next;
    node->next = node->next->next;
    free(current_next);
}

void list_push_front(List* l, int value) {
    ListNode* new_head = init_listnode(value, l->head);
    l->head = new_head;
    if (!l->size) l->tail = new_head;
    ++l->size;
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

void listnode_print(ListNode* node){
	if (node == NULL) return;
	while(node != NULL){
		printf("%d%s", node->value, node->next == NULL ? "\n" : " -> ");
		node = node->next;}
}

void list_print(List* l) {
    if (l == NULL) return;
    listnode_print(l->head);
}

ListNode* list_find(List* list, int value){
	if (list == NULL) return NULL;
	ListNode* node = list->head;
	while(node != NULL){
		if (node->value == value) return node;
		node = node->next;}
	return NULL;
}

void list_swap(ListNode* nodebefor1, ListNode* nodebefor2){
	ListNode nodebefor11 = *nodebefor1;
	ListNode* nodeafter11 = nodebefor1->next->next;
	ListNode* nodeafter22 = nodebefor2->next->next;
	nodebefor1->next = nodebefor2->next;
	nodebefor1->next->next = nodeafter11;
	nodebefor2->next = nodebefor11.next;
	nodebefor2->next->next = nodeafter22;
}

int main() {
    List l = list_init();
    for (int i = 1; i < 5; ++i) {
        list_push_front(&l, i * i);
        list_push_back(&l, i * i);
    }
    list_print(&l);

    while (l.size) {
        list_pop_front(&l);
        list_print(&l);
    }
    list_print(&l);
    return 0;
}
