/* Code Chef Practice - TSORT

Given the list of numbers, you are to sort them in non decreasing order.
Input

t – the number of numbers in list, then t lines follow [t <= 10^6]. 

Each line contains one integer: N [0 <= N <= 10^6]
Output

Output given numbers in non decreasing order.
Example

Input:
5
5
3
6
7
1
Output:
1
3
5
6
7

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int level = 0;
int values;

#define DEBUG 0

void p(int *array) {
	int i;
	for (i = 0; i < values; i++) {
		printf("%i\t", array[i]);
	}
	printf("\n");
}

int partition(int *array, int left, int right) {
	int i = left - 1; // -1 because the first op is ++i
	int j = right; // dead on right, because we'll move past the pivot in the first op, --j
	/* find the pivot - atm just using the middle element */
	/* best case, you should use median of start, end and middle elements */
	int index = left + (right - left) / 2;
	int pivot = array[index];
	int temp;

	if (DEBUG) printf("pivot is: %i\n", pivot);
	if (DEBUG) p(array);

	/* swap the pivot with the right-most element */
	if (DEBUG) printf("swapping %i and %i\n", array[index], array[right]);
	temp = array[index];
	array[index] = array[right];
	array[right] = temp;

	/* loop over this */
	while (1) {
		if (DEBUG) p(array);

		/* move i position forward until element at i is greater than pivot */
		while (array[++i] < pivot) ;
		/* then move j position backward until element at j is less than pivot */
		while (pivot < array[--j]) ;
		if (DEBUG) printf("i stopped at %i, j stopped at %i\n", array[i], array[j]);

		/* now that both i and j are in position, if i is still to the left of j */
		if (i < j) {
			/* swap those two positions */
			if (DEBUG) printf("swapping %i and %i\n", array[i], array[j]);
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			if (DEBUG) p(array);
		} else {
			/* otherwise, we're done with this pass and break out of the main loop */
			if (DEBUG) printf("leaving loop\n");
			break;
		}

		/* since we're here, loop again, continuing to move i and j toward each other */
	}

	/* we've broken out of the main loop, so swap the pivot with the place where i stopped */
	if (DEBUG) printf("putting pivot in place, ");
	if (DEBUG) printf("swapping %i and %i\n", array[right], array[i]);
	temp = array[i];
	array[i] = array[right];
	array[right] = temp;

	/* return that position so that we can sort the sub-arrays to the left and right of it */
	return i;
}

void sort(int *array, int start, int end) {
	if (DEBUG) printf("sorting array from %i to %i\n", start, end);
	if (start < end) {
		int index = partition(array, start, end);
		sort(array, start, index - 1);
		sort(array, index + 1, end);
	}
	level--;
}

int getnumb(int limit) {
	return rand() % (limit - 1) + 1;
}

int main(void) {
	int i;
	int *list;

/* for codechef, read from stdin */
	scanf("%d\n", &values);
	if (DEBUG) printf("sorting %i values\n", values);

	list = malloc(sizeof(int) * values);
	for (i = 0; i < values; i++) {
		scanf("%d\n", &list[i]);
	}

/* for now, generate randomly! 
	struct timeval t1;
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);

	values = getnumb(100);
	printf("sorting %i values\n", values);

	list = malloc(sizeof(int) * values);
	for (i = 0; i < values; i++) {
		list[i] = getnumb(1000000);
	}
*/

	if (DEBUG) {
		printf("List  : ");
		for (i = 0; i < values; i++) {
			printf("%i ", list[i]);
		}
		printf("\n");
	}

	/* start the sort */
	sort(list, 0, values - 1);

	if (DEBUG) {
		printf("Sorted: ");
		for (i = 0; i < values; i++) {
			printf("%i ", list[i]);
		}

		printf("\n");
	} else {
		for (i = 0; i < values; i++) {
			printf("%i\n", list[i]);
		}
	}

	free(list);

	return 0;
}
