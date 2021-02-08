#include "signals.h"

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "debug.h"
#include "globals.h"

void ignore_sigint() {
  struct sigaction ignore_action = {0};
  ignore_action.sa_handler = SIG_IGN;

  sigaction(SIGINT, &ignore_action, NULL);
}

void default_sigint() {
  struct sigaction default_action = {0};
  default_action.sa_handler = SIG_DFL;

  sigaction(SIGINT, &default_action, NULL);
}

void ignore_sigtstp() {
  struct sigaction ignore_action = {0};
  ignore_action.sa_handler = SIG_IGN;

  sigaction(SIGTSTP, &ignore_action, NULL);
}

void handle_sigtstp() {
  // toggle BG commands allowed on SIGINT
  struct sigaction sigtstp_action = {0};
  sigtstp_action.sa_handler = sigtstp_handler;
  sigtstp_action.sa_flags = SA_RESTART;
  sigfillset(&sigtstp_action.sa_mask);

  sigaction(SIGTSTP, &sigtstp_action, NULL);
}

void sigtstp_handler(int signo) {
  bg_allowed = !bg_allowed;
  bg_print_message = 1 + bg_allowed;  // 1 for enabled msg, 2 for disabled msg
}
