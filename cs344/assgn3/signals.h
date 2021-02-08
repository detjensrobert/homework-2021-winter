#ifndef SIGNALS
#define SIGNALS

void ignore_sigint();
void default_sigint();

void ignore_sigtstp();
void handle_sigtstp();
void sigtstp_handler(int signo);

#endif
