#include <stdio.h>

#include "analysis.h"

void do_analysis(struct Movie *movies) {
  int choice = main_menu();

  while (choice != 4) {
    switch (choice) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
    }
  }

  printf("You chose: %i\n", choice);
}

int main_menu() {
  int choice;

  do {
    printf("\n");
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific "
           "language\n");
    printf("4. Exit from the program\n");
    printf("\n");
    printf("Enter a choice from 1 to 4: ");

    scanf("%i", &choice);

  } while ((choice < 1 || choice > 4) &&
           printf("Please choose a number between 1 and 4!\n"));

  return choice;
}
