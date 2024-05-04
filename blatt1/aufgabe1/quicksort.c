#include <stdio.h>
#include <stdlib.h>

void list_print(long list[], int len);
char* list_is_sorted(long list[], int len);
int partition(long list[], int start, int end);
void quicksort(long list[], int start, int end);

// aufgabe1/quicksort <long>[]
int main(int argc, const char *argv[]) {
	// create the list from the command line
	const int len = argc - 1;
	long list[len];
	
	for (int i = 0; i < len; ++i) {
		list[i] = strtol(argv[i + 1], NULL, 10);
	}
	
	// print unsorted list
	printf("---- Unsortiert: %s ----\n", list_is_sorted(list, len));
	list_print(list, len);
		
	// sort it
	quicksort(list, 0, len);
		
	
		// print the sorted list
	printf("---- Sortiert: %s ----\n", list_is_sorted(list, len));
	list_print(list, len);
	
	return 0;
}

char* list_is_sorted(long list[], int len){
	for (int i = 0; i < len - 1; i++) {
		if (list[i] > list[i+1]){
			return "false";
		}
    }

	return "true";
}

void list_print(long list[], int len){
	char* sep = "";

	printf("[");
	for (int i = 0; i < len; i++, sep=", ") {
        printf("%s%i", sep, list[i]);
    }
	printf("]\n");
}

void quicksort(long list[], int start, int end){
	if (end - start <= 1){
		return;
	}
	
	int mid = partition(list, start, end);
	quicksort(list, start, mid);
	quicksort(list, mid + 1, end);
}

int partition(long list[], int start, int end){
	int pivot = end - 1;
	int l = start, r = end - 2;
	int t;
	
	while (1) {
		while (l < r && list[l] <  list[pivot]){
			++l;
		}	
		while (l < r && list[r] >= list[pivot]){
			--r;
		}	
		
		if (l >= r) break;
		
		t = list[l];
		list[l] = list[r];
		list[r] = t;
	}
	
	if (list[l] >= list[pivot]) {
		t = list[l];
		list[l] = list[pivot];
		list[pivot] = t;
		return l;
	}
	
	return pivot;
}