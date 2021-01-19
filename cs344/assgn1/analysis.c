#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analysis.h"
#include "movies.h"

/*
 * Loops menu + analysis until user chooses to exit
 */
void do_analysis(struct Movie *movies) {
  int choice = main_menu();

  while (choice != 4) {
    switch (choice) {
    case 1:
      show_by_year(movies);
      break;
    case 2:
      show_highest_rated(movies);
      break;
    case 3:
      show_by_language(movies);
      break;
    }

    choice = main_menu();
  }
}

/*
 * Prints menu options and returns user choice
 */
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

/*
 * Prints all movies released in given year
 */
void show_by_year(struct Movie *movies) {
  int year;

  printf("Enter the year for which you want to see movies: ");
  scanf("%i", &year);

  int printed = 0;

  struct Movie *walker = movies;
  while (walker != NULL) {
    if (walker->year == year) {
      printf("%s\n", walker->title);
      printed++;
    }

    walker = walker->next;
  }
  if (printed == 0) {
    printf("No data about movies released in the year %i\n", year);
  }
}

/*
 * Prints the highest-rated movie for each year
 */
void show_highest_rated(struct Movie *movies) {

  // the smart way to do this would to be a hash table
  // and store a pointer to the max rated movie by year
  // BUT
  // could also bodge this with an array since the years are bounded
  // it *does* work

  int YEAR_MIN = 1900;
  int YEAR_MAX = 2021;

  struct Movie **max_arr = calloc(sizeof(struct Movie *), YEAR_MAX - YEAR_MIN + 1);

  struct Movie *walker = movies;
  while (walker != NULL) {

    // if first movie encountered OR is higher rated than currently stored
    if (max_arr[walker->year - YEAR_MIN] == NULL ||
        walker->rating > max_arr[walker->year - YEAR_MIN]->rating) {
      // set as new maximum for that year
      max_arr[walker->year - YEAR_MIN] = walker;
    }
    walker = walker->next;
  }

  for (int i = 0; i < YEAR_MAX - YEAR_MIN + 1; i++) {
    if (max_arr[i]) {
      printf("%i %.1f %s\n", max_arr[i]->year, max_arr[i]->rating,
             max_arr[i]->title);
    }
  }

  free(max_arr);
}

/*
 * Prints all movies released in a given language
 */
void show_by_language(struct Movie *movies) {
  char *lang = malloc(sizeof(char) * 21);

  printf("Enter the language for which you want to see movies: ");
  scanf("%s", lang);

  int printed = 0;

  struct Movie *walker = movies;
  while (walker != NULL) {
    if (has_lang(walker->langs, walker->lang_count, lang)) {
      printf("%i %s\n", walker->year, walker->title);
      printed++;
    }

    walker = walker->next;
  }
  if (printed == 0) {
    printf("No data about movies released in %s\n", lang);
  }

  free(lang);
}

/*
 * Returns whether `target` is contained within the string array `langs`
 */
int has_lang(char **langs, int lang_count, char *target) {
  for (int i = 0; i < lang_count; i++) {
    if (!(strncmp(langs[i], target, 20))) { // strcmp returns 0 (false) if equal
      return 1;
    }
  }
  return 0;
}
