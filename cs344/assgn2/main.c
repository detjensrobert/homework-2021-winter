#include <stdio.h>
#include <stdlib.h>

#include "movies.h"
#include "select.h"

int main_menu();

int main(int argc, char *argv[]) {

  int choice = main_menu();

  while (choice != 2) {
    char *filename = get_filename();

    printf("\nNow processing the chosen file named %s\n", filename);

    struct Movie *movies = movies_parse(filename);

    movies_delete(movies);
    free(filename);

    choice = main_menu();
  }

  return 0;
}

int main_menu() {
  int choice;

  do {
    printf("\n1. Select file to process\n"
           "2. Exit the program\n"
           "Enter a choice 1 or 2: ");

    scanf("%i", &choice);
  } while ((choice != 1 && choice != 2) && printf("Please choose 1 or 2.\n"));

  return choice;
}
