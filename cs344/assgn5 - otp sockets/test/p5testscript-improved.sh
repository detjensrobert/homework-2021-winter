#!/bin/bash

# If test stuff is under a different dir from the binaries (e.g. test/),
# set BIN_DIR to relative path from script to binaries (e.g. ..)
BIN_DIR=.
if [ ! -e $BIN_DIR/enc_server ]; then
  # try going up a dir if binaries not found
  BIN_DIR=..
fi

POINTS=0

#Make sure we have the right number of arguments
if test $# -gt 3 -o $# -lt 2; then
  echo "USAGE: $0 <enc-port> <dec-port> [--no-color]" 1>&2
  exit 1
fi

#Record the ports passed in
ENC_PORT=$1
DEC_PORT=$2

# ANSI color codes for colorful output
RESTORE=$(echo -en '\033[0m')

RED=$(echo -en '\033[00;31m')
GREEN=$(echo -en '\033[00;32m')
BLUE=$(echo -en '\033[00;34m')
CYAN=$(echo -en '\033[00;36m')
WHITE=$(echo -en '\033[00;37m')
GREY=$(echo -en '\033[01;30m')
BYELLOW=$(echo -en '\033[01;33m')
BBLUE=$(echo -en '\033[01;34m')
BWHITE=$(echo -en '\033[01;37m')

if [ $3 -a $3 = "--no-color" ]; then
  RESTORE=''

  RED=''
  GREEN=''
  BLUE=''
  CYAN=''
  WHITE=''
  GREY=''
  BYELLOW=''
  BBLUE=''
  BWHITE=''
fi

header() { echo "${BWHITE}$*"; }
good() { echo "${GREEN}  YES: $*"; }
bad() { echo "${RED}  NO: $*"; }
warn() { echo "${BYELLOW}$*"; }
info() { echo "${GREY}  $*"; }
restore() { echo -n $RESTORE; }

cleanup() {
  info "- killing any running servers (ignore not permitted errors)"
  killall -q -u $USER dec_client
  killall -q -u $USER dec_server
  killall -q -u $USER enc_client
  killall -q -u $USER enc_server

  info "- removing tempfiles"
  rm -f ciphertext*
  rm -f plaintext*_*
  rm -f key20
  rm -f key70000
}

if [ ! -e $BIN_DIR/enc_server ]; then
  echo "${RED}ERR: cannot find binaries!"
  restore
  exit 1
fi

header "== CS344 Program 5 Grading Script =="

cleanup

info "- starting servers"
$BIN_DIR/enc_server $ENC_PORT &
$BIN_DIR/dec_server $DEC_PORT &

info "- generating key20"
$BIN_DIR/keygen 20 >key20

header "5 POINTS: does key20 exist?"
[ -s key20 ] || rm -f key20 # remove if empty
if [ -f key20 ]; then
  good "key20 exists"
  POINTS=$((POINTS + 5))
else
  bad "key20 does not exist"
fi

header "5 POINTS: is length of key20 21?"
if [ $(stat -c '%s' key20) -eq 21 ]; then
  good "key20 has correct length"
  POINTS=$((POINTS + 5))
else
  bad "key20 has length $(stat -c '%s' key20)"
fi

info "- generating key70000"
$BIN_DIR/keygen 70000 >key70000
header "5 POINTS: is size of key70000 70001?"
if [ $(stat -c '%s' key70000) -eq 70001 ]; then
  good "key70000 has correct length"
  POINTS=$((POINTS + 5))
else
  bad "key70000 has length $(stat -c '%s' key70000)"
fi

header "10 POINTS: error given about short key?"
restore
$BIN_DIR/enc_client plaintext1 key20 $ENC_PORT
if [ $? -eq 1 ]; then
  good "error reported"
  POINTS=$((POINTS + 10))
else
  bad "no error thrown"
fi

header "20 POINTS: returns encrypted text? ${BYELLOW}Double check manually!"
echo -n $BLUE
$BIN_DIR/enc_client plaintext1 key70000 $ENC_PORT
if [ $? -eq 0 ]; then
  good "no errors thrown"
  POINTS=$((POINTS + 20))
else
  bad "error reported"
fi

info "- creating ciphertext1 file"
$BIN_DIR/enc_client plaintext1 key70000 $ENC_PORT >ciphertext1
header "10 POINTS: does ciphertext1 exist?"
[ -s ciphertext1 ] || rm -f ciphertext1 # remove if empty
if [ -f key20 ]; then
  good "ciphertext1 exists"
  POINTS=$((POINTS + 10))
else
  bad "ciphertext1 does not exist"
fi

header "10 POINTS: is size of ciphertext1 same as plaintext1?"
if [ $(stat -c '%s' ciphertext1) -eq $(stat -c '%s' plaintext1) ]; then
  good "ciphertext1 has correct length"
  POINTS=$((POINTS + 10))
else
  bad "ciphertext1 has length $(stat -c '%s' ciphertext1), should be $(stat -c '%s' plaintext1)"
fi

header "5 POINTS: does ciphertext1 look encrypted? ${BYELLOW}Double check manually!"
echo -n $BLUE
cat ciphertext1
if [ $? -eq 0 ]; then
  good "no errors thrown"
  POINTS=$((POINTS + 5))
else
  bad "error reported"
fi

header "5 POINTS: dec -> enc invalid connection reported?"
restore
$BIN_DIR/dec_client ciphertext1 key70000 $ENC_PORT
if [ $? -eq 2 ]; then
  good "error reported"
  POINTS=$((POINTS + 5))
else
  bad "no error thrown"
fi

header "20 POINTS: does decrypted message match source?"
echo -n "${CYAN}Original : "
cat plaintext1
echo -n "${BLUE}Decrypted: "
$BIN_DIR/dec_client ciphertext1 key70000 $DEC_PORT
cmp -s plaintext1 <($BIN_DIR/dec_client ciphertext1 key70000 $DEC_PORT)
if [ $? -eq 0 ]; then
  good "output matches"
  POINTS=$((POINTS + 20))
else
  bad "output does not match"
fi

info "- decrypting ciphertext1 to plaintext1_a"
$BIN_DIR/dec_client ciphertext1 key70000 $DEC_PORT >plaintext1_a
header "10 POINTS: does plaintext1_a exist?"
[ -s plaintext1_a ] || rm -f plaintext1_a # remove if empty
if [ -f plaintext1_a ]; then
  good "plaintext1_a exists"
  POINTS=$((POINTS + 10))
else
  bad "plaintext1_a does not exist"
fi

header "5 POINTS: does decrypted message file match source?"
cmp -s plaintext1 plaintext1_a
if [ $? -eq 0 ]; then
  good "output matches"
  POINTS=$((POINTS + 5))
else
  bad "output does not match"
fi

info "- testing concurrent encyption"
header "5 POINTS: is error reported for bad input plaintext5?"
rm -f ciphertext*
rm -f plaintext*_*

$BIN_DIR/enc_client plaintext1 key70000 $ENC_PORT >ciphertext1 &
$BIN_DIR/enc_client plaintext2 key70000 $ENC_PORT >ciphertext2 &
$BIN_DIR/enc_client plaintext3 key70000 $ENC_PORT >ciphertext3 &
$BIN_DIR/enc_client plaintext4 key70000 $ENC_PORT >ciphertext4 &
# \/ this one should throw error
$BIN_DIR/enc_client plaintext5 key70000 $ENC_PORT >ciphertext5
if [ $? -ne 0 ]; then
  good "error reported for plaintext5"
  POINTS=$((POINTS + 5))
else
  bad "no error thrown"
fi

info "- waiting for programs to complete"
wait $( jobs -l | grep enc_client | cut -d' ' -f 2 )

header "20 POINTS: are correct ciphertexts generated with concurrent encryption?"
ALLMATCH=1
for f in text{1,2,3,4}; do
  if [ $(stat -c '%s' "cipher$f") -ne $(stat -c '%s' "plain$f") ]; then
    bad "size of cipher$f does not match plain$f"
    restore
    stat -c '%n %s' "plain$f" "cipher$f" | column -t
    ALLMATCH=0
  fi
done
if [ $ALLMATCH -eq 1 ]; then
  good "size of ciphertexts match plaintexts"
  POINTS=$((POINTS + 20))
fi

info "- testing concurrent decryption"
$BIN_DIR/dec_client ciphertext1 key70000 $DEC_PORT >plaintext1_a &
$BIN_DIR/dec_client ciphertext2 key70000 $DEC_PORT >plaintext2_a &
$BIN_DIR/dec_client ciphertext3 key70000 $DEC_PORT >plaintext3_a &
$BIN_DIR/dec_client ciphertext4 key70000 $DEC_PORT >plaintext4_a &

info "- waiting for programs to complete"
wait $( jobs -l | grep dec_client | cut -d' ' -f 2 )

header "15 POINTS: are correct output files generated with concurrent decryption?"
ALLMATCH=1
for f in plaintext{1,2,3,4}; do
  cmp -s "$f" "${f}_a"
  if [ $? -ne 0 ]; then
    bad "${f}_a does not match ${f}"
    restore
    stat -c '%n %s' "$f" "${f}_a" | column -t
    ALLMATCH=0
  fi
done
if [ $ALLMATCH -eq 1 ]; then
  good "decrypted text matches original"
  POINTS=$((POINTS + 15))
fi

cleanup
header "TOTAL SCORE: ${BBLUE}$POINTS $WHITE/ 150"
restore
