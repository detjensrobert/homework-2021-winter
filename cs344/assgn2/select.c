#include <dirent.h>
#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "select.h"

char *get_filename() {

  char *filename = NULL;

  DIR *dp = opendir(".");

  if (dp == NULL) {
    fprintf(stderr, "Error reading directory!");
    exit(1);
  }

  do {
    int choice = file_select_menu();

    switch (choice) {
    case 1: // largest
      filename = file_get_lgsm(dp, 1);
      break;
    case 2: // smallest
      filename = file_get_lgsm(dp, 0);
      break;
    case 3: // user choice
      filename = file_get_user(dp);
      break;
    }
  } while (filename == NULL);

  closedir(dp);

  return filename;
}

int file_select_menu() {
  int choice;

  do {
    printf("\nWhich file you want to process?\n"
           "Enter 1 to pick the largest file\n"
           "Enter 2 to pick the smallest file\n"
           "Enter 3 to specify the name of a file\n"
           "Enter a choice from 1 to 3: ");

    scanf("%i", &choice);
  } while ((choice < 1 || choice > 3) && printf("Please choose 1, 2, or 3.\n"));

  return choice;
}

/*
 *  Finds either the largest or smallest movies_*.csv file.
 *  Largest if want_largest != 0, smallest if == 0.
 */
char *file_get_lgsm(DIR *dp, int want_largest) {
  char *filename = malloc(sizeof(char) * 256);

  off_t filesize = 0;
  if (!want_largest) {
    filesize = LONG_MAX;
  }

  struct dirent *entry;
  struct stat info;

  regex_t name_regex;
  if (regcomp(&name_regex, "^movies_.+\\.csv$", REG_EXTENDED)) {
    fprintf(stderr, "Could not compile regex!\n");
    exit(1);
  }

  // iterate through all entries in dir
  while ((entry = readdir(dp)) != NULL) {
    // only look at regular files
    if (entry->d_type == DT_REG) {

      // make sure it matches movies_*.csv
      if (regexec(&name_regex, entry->d_name, 0, NULL, 0) == REG_NOMATCH) {
        continue;
      }

      // get info on file
      if ((stat(entry->d_name, &info)) == -1) {
        continue;
      }

      // update current largest/smallest
      if ((want_largest && info.st_size > filesize) ||
          (!want_largest && info.st_size < filesize)) {
        strcpy(filename, entry->d_name);
        filesize = info.st_size;
      }
    }
  }

  regfree(&name_regex);
  return filename;
}

/*
 *  Accepts a filename from user input.
 *  If the file does not exist, prompt again.
 */
char *file_get_user(DIR *dp) {

  char *filename = calloc(sizeof(char), 256);
  struct stat info;

  printf("Enter the complete file name: ");
  scanf("%s", filename);

  // if file does not exist, return NULL to reprompt
  if ((stat(filename, &info)) == -1) {
    printf("The file %s was not found. Try again\n", filename);
    free(filename);
    filename = NULL;
  }

  return filename;
}
