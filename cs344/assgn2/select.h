#ifndef SELECT
#define SELECT

#include <dirent.h>
#include <sys/types.h>

char *get_filename();

int file_select_menu();
char *file_get_lgsm(DIR *dp, int want_largest);
char *file_get_user(DIR *dp);

#endif
