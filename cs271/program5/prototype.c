#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void info();
void get_data(int *request);
void fill_array(int request, int *array);
void sort_list(int *array, int request);
void swap_elems(int *a, int *b);
void show_median(int *array, int request);
void show_list(int *array, int request, char *title);

int main(int argc, char **argv) {
  int count;
  int *numbers = malloc(200 * sizeof(int));
  char *unsortedstr = "Unsorted:";
  char *sortedstr =  "After sorting:";

  info();

  get_data(&count);

  fill_array(count, numbers);
  show_list(numbers, count, unsortedstr);

  sort_list(numbers, count);

  show_median(numbers, count);
  show_list(numbers, count, sortedstr);

  return 0;
}

void info() {
  printf("PROGRAM 5: Random Integer Sort - Robert Detjens\n");

  printf("This program generates random numbers in the range[100..999],\n");
  printf("display the original list, sorts the list, and calculates the\n");
  printf("median value. Finally, it displays the list sorted in\n");
  printf("descending order.\n");

  srand(time(0));
}

void get_data(int *request) {
  int tmp;
prompt:
  printf("How many numbers should be generated? [15..200]: ");
  scanf("%i", &tmp);

  if (tmp < 15 || tmp > 200) {
    printf("[ ERR ] Bad input\n");
    goto prompt;
  }

  *request = tmp;
}

void fill_array(int request, int *array) {
  int counter;

  counter = request;

fill_loop:
  counter--;
  array[counter] = rand() % 900 + 100;
  if (counter > 0) goto fill_loop;
}

void show_list(int *array, int request, char *title) {
  int counter = 0;
  int printed = 0;

  printf("%s\n", title);

display_loop:
  printf("%i     ", array[counter]);
  counter++;
  printed++;
  if (printed == 10) {
    printed = 0;
    printf("\n");
  }
  if (counter < request) {
    goto display_loop;
  }
  printf("\n\n");
}

void sort_list(int *array, int request) {
  // descending bubble sort

  int i, j;
  for (i = 0; i < request - 1; i++) {
    for (j = 0; j < request - 1; j++) {

      if (array[j] < array[j + 1]) {
        swap_elems(&array[j], &array[j + 1]);
      }

    }
  }
}

void swap_elems(int *a, int *b) {
  int x = *a;
  int y = *b;

  *a = y;
  *b = x;
}

void show_median(int *array, int request) {
  int median_idx = request / 2;
  int median = array[median_idx];

  if (request % 2 == 0) {
    median = median + array[median_idx - 1];
    median = median / 2;
  }

  printf("Median value is: %i\n", median);
}
