#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void randarray(int numbers[], size_t size){
	for (size_t i = 0; i < size; ++i){numbers[i] = rand()%1000;}
}

void printarray(int numbers[], size_t size){
	for (int i = 0; i < size; ++i){
		printf("%4d\t", numbers[i]);
		if ((i + 1) % 10 == 0){putchar('\n');}}
}

void merge(int array[], int aux[], size_t lo, size_t mid, size_t hi){
	for (size_t i = lo; i <= hi; i++){aux[i] = array[i];}
	size_t lo1 = lo;
	size_t mid1 = mid + 1;
	for (size_t i = lo; i <= hi; i++){
		if (lo1 != mid + 1 && mid1 != hi + 1){
			if (aux[lo1] > aux[mid1]){array[i] = aux[mid1]; mid1++;}
			else {array[i] = aux[lo1]; lo1++;}}
		else if (lo1 == mid + 1){array[i] = aux[mid1]; mid1++;}
		else {array[i] = aux[lo1]; lo1++;}}
}

void mergesortaux(int array[], int aux[], size_t lo, size_t hi){
	if (lo == hi) {return;}
	size_t mid = (lo + hi) / 2;
	mergesortaux(array, aux, lo, mid);
	mergesortaux(array, aux, (mid + 1), hi);
	merge (array, aux, lo, mid, hi);
}

void mergesort(int array[], size_t size){
	int aux[size];
	mergesortaux(array, aux, 0, (size - 1));
}

int main(){
	printf ("Enter the number of numbers: ");
	int size;
	scanf("%d", &size);
	int array[size];
	randarray(array, size);
	printf ("Array:\n");
	printarray(array, size);
	putchar ('\n');
	mergesort(array, size);
	printf ("Sort array:\n");
	printarray(array, size);
	return 0;
}
