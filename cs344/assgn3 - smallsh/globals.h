#ifndef GLOBALS
#define GLOBALS

#ifdef MAIN_FILE
int bg_allowed;
int bg_print_message;
#else
extern int bg_allowed;
extern int bg_print_message;
#endif

#endif
