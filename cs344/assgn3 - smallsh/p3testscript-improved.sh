#!/bin/bash

BIN_DIR=.
if [ ! -e $BIN_DIR/smallsh ]; then
  # try going up a dir if binaries not found
  BIN_DIR=..
fi

POINTS=0

if test $# -gt 1; then
  echo "USAGE: $0 [--no-color]" 1>&2
  exit 1
fi

BOLD=$(tput bold)
RESET=$(tput sgr0)

BLACK=$(tput setaf 0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
MAGENTA=$(tput setaf 5)
CYAN=$(tput setaf 6)
WHITE=$(tput setaf 7)
GREY="$(tput setaf 8)"

if [ $1 -a $1 = "--no-color" ]; then
  BOLD=''
  RESET=''

  BLACK=''
  RED=''
  GREEN=''
  YELLOW=''
  BLUE=''
  MAGENTA=''
  CYAN=''
  WHITE=''
  GREY=''
fi

restore() { echo -n $RESET; }
title() {
  echo
  echo "${BOLD}${WHITE}$*${RESET}"
  echo
}
header() { echo "${WHITE}${@:2} ${BLUE}($1 pts)"; }
pass() { echo "${GREEN}  PASS"; }
fail() { echo "${RED}  FAIL: $*"; }
warn() { echo "${YELLOW}$*"; }
info() {
  echo
  echo "${WHITE}$*"
}

cleanup() { rm -rf junk* smallsh-test-dir; }

# run arguments in smallsh and remove any prompts from output
smallsh() {
  echo -n "$GREY" > /dev/tty
  echo -e "$@\nexit" | $BIN_DIR/smallsh | sed 's/: //g'
}

title "CS344 Program 3 Grading Script"

cleanup

header 5 "comments"
smallsh "# i am a comment
#so am i" | grep -qP '.+' # /.+/ regex matches any output
if [ $? -eq 1 ]; then
  pass "comments are not printed"
  POINTS=$((POINTS + 5))
else
  fail "comment printed"
fi

header 10 "command execution"
cmp -s <(ls) <(smallsh ls)
if [ $? -eq 0 ]; then
  pass "executed successfully"
  POINTS=$((POINTS + 10))
else
  fail "listing does not match"
fi

header 15 "output redirection"
smallsh "ls > junk"
cmp -s <(ls) <(smallsh cat junk)
if [ $? -eq 0 ]; then
  pass "file exists and content is correct"
  POINTS=$((POINTS + 15))
else
  [ -f junk ] || fail "file does not exist" && (
    [ -s junk ] && fail "contents do not match" || fail "file is empty"
  )
fi

header 15 "input redirection"
cmp -s <(wc <junk) <(smallsh "wc < junk")
if [ $? -eq 0 ]; then
  pass "output is correct"
  POINTS=$((POINTS + 15))
else
  fail "output does not match"
fi

header 10 "input and output redirection"
smallsh "wc < junk > junk2"
cmp -s <(wc <junk) <(smallsh cat junk2)
if [ $? -eq 0 ]; then
  pass "file exists and content is correct"
  POINTS=$((POINTS + 10))
else
  [ -f junk ] || fail "file does not exist" && ([ -s junk ] && fail "contents do not match" || fail "file is empty")
fi

header 10 "status command"
OUTPUT=$(smallsh "test -f badfile
status &" | grep -oP '\d+')
if [ $OUTPUT -eq 1 ]; then
  pass "error status correctly reported"
  POINTS=$((POINTS + 10))
else
  fail "status not reported"
fi

header 10 "input redirection with nonexistent file"
OUTPUT=$(smallsh "wc < badfile
status &" | grep -oP '\d+')
if [ $OUTPUT -eq 1 ]; then
  pass "error status correctly reported"
  POINTS=$((POINTS + 10))
else
  fail "status not reported"
fi

header 10 "nonexistent command"
OUTPUT=$(smallsh "badcmd
status &" | grep -oP '\d+')
if [ $OUTPUT -eq 1 ]; then
  pass "error status correctly reported"
  POINTS=$((POINTS + 10))
else
  fail "status not reported"
fi

header 10 "background command PID on creation"
OUTPUT=$(smallsh "sleep 100 &
pidof sleep" | grep -oP '\d+') # extract pids from output string
OUTPUT=($OUTPUT)               # convert string to array
if [ ${OUTPUT[0]} -eq ${OUTPUT[1]} ]; then
  pass "background pid correctly reported"
  POINTS=$((POINTS + 10))
else
  fail "pid not reported"
fi

OUTPUT=$(smallsh "sleep 100 &
sleep 1
pkill sleep" | grep -oP '\d+') # extract pids from output string
OUTPUT=($OUTPUT)               # convert string to array

header 10 "background command PID on termination"
if [ ${OUTPUT[0]} -eq ${OUTPUT[1]} ]; then
  pass "background pid correctly reported"
  POINTS=$((POINTS + 10))
else
  fail "pid not reported"
fi

header 10 "background command termination signal"
if [ ${OUTPUT[2]} -eq 15 ]; then
  pass "termination signal correctly reported"
  POINTS=$((POINTS + 10))
else
  fail "signal not reported"
fi

OUTPUT=$(smallsh "sleep 1 &
sleep 2" | grep -oP '\d+') # extract pids from output string
OUTPUT=($OUTPUT)           # convert string to array

header 10 "background command PID on completion"
if ([ ${OUTPUT[0]} -eq ${OUTPUT[1]} ] && [ ${OUTPUT[2]} -eq 0 ]); then
  pass "background pid and exit status correctly reported"
  POINTS=$((POINTS + 10))
else
  fail "pid not reported"
fi

header 10 "background command exit code"
if ([ ${OUTPUT[2]} -eq 0 ]); then
  pass "exit status correctly reported"
  POINTS=$((POINTS + 10))
else
  fail "exit status not reported"
fi

header 5 "implicit cd to homedir"
OUTPUT=$(smallsh "cd
pwd")
if [ "$OUTPUT" = "$HOME" ]; then
  pass "changed to home directory"
  POINTS=$((POINTS + 5))
else
  fail "not in home directory"
fi

header 5 "cd to homedir"
OUTPUT=$(smallsh 'mkdir smallsh-test-dir
cd smallsh-test-dir
pwd')
if [ "$OUTPUT" = "$PWD/smallsh-test-dir" ]; then
  pass "changed to correct directory"
  POINTS=$((POINTS + 5))
else
  fail "not in correct directory"
fi

header 5 "pid variable replacement"
# run smallsh manually here to get true pid (instead of others in the function)
echo -e 'echo $$ > junk3\nexit' | $BIN_DIR/smallsh >/dev/null &
wait $!
if [ $! = $(cat junk3) ]; then
  pass "pid var correctly replaced"
  POINTS=$((POINTS + 5))
else
  [ $(cat junk3) = '$$' ] && fail "pid var was not replaced" || fail "replacement does not match correct pid"
fi

header 20 "foreground-only mode"
OUTPUT=$(smallsh 'kill -SIGTSTP $$
date +%s
sleep 2 &
date +%s
kill -SIGTSTP $$' | grep -oP '\d+') # extract times from output string
OUTPUT=($OUTPUT)                    # convert string to array
if [ ${OUTPUT[0]} = $(( ${OUTPUT[1]} - 2 )) ]; then
  pass "times are correctly 2 seconds apart"
  POINTS=$((POINTS + 20))
else
  fail "times are not 2 seconds apart"
fi


title "FINAL SCORE: ${BLUE}${POINTS}${WHITE} / 170"

cleanup
restore
