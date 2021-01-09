#ifndef ANALYSIS
#define ANALYSIS

#include "movies.h"

void do_analysis(struct Movie *movies);

int main_menu();

void show_by_year(struct Movie *movies);
void show_highest_rated(struct Movie *movies);
void show_by_language(struct Movie *movies);

int has_lang(char **langs, int lang_count, char *target);

#endif
