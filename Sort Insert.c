#include <stdio.h>
#include <math.h>

void swap(int *a, int *b){
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void print(int numbers[], size_t size){
	for (int i = 0; i < size; ++i){
		printf("%4d\t", numbers[i]);
		if ((i + 1) % 10 == 0){putchar('\n');}}
}

void sort(int numbers[], size_t size){
	for (size_t i = 0; i < size; i++){
		for (size_t j = i; numbers[j - 1] > numbers[j] && j > 0; j --){
			swap(numbers + j, numbers + j - 1);}}
}

int main(){
	printf("Please, enter the number of numbers (dont more 100000): ");
	int size;
	scanf("%d", &size);
	int numbers[size];
	printf("Please, enter the numbers: ");
	for (int i = 0; i < size; ++i){scanf("%d",&numbers[i]);}
	sort (numbers, size);
	print (numbers, size);
	return 0;
}
