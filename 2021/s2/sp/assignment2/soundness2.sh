#!/bin/bash

ulimit -c 0

BASE=`pwd`
SAMPLES=$BASE/samples
DATA=$BASE/data

TIMEOUT=90s

shopt -q nullglob

setdisp() {
  for f; do
    case "$f" in
      "reset")                  param=0;;
      "bold")                   param="$param;1";;
      "nobold")                 param="$param;21";;
      "underscore")             param="$param;4";;
      "blink")                  param="$param;5";;
      "fg-black"|"black")       param="$param;30";;
      "fg-red"|"red")           param="$param;31";;
      "fg-green"|"green")       param="$param;32";;
      "fg-yellow"|"yellow")     param="$param;33";;
      "fg-blue"|"blue")         param="$param;34";;
      "fg-magenta"|"magenta")   param="$param;35";;
      "fg-cyan"|"cyan")         param="$param;36";;
      "fg-gray"|"gray")         param="$param;37";;
      "fg-dark"|"dark")         param="$param;90";;
      "fg-lred"|"lred")         param="$param;91";;
      "fg-lgreen"|"lgreen")     param="$param;92";;
      "fg-lyellow"|"lyellow")   param="$param;93";;
      "fg-lblue"|"lblue")       param="$param;94";;
      "fg-lmagenta"|"lmagenta") param="$param;95";;
      "fg-lcyan"|"lcyan")       param="$param;96";;
      "fg-white"|"white")       param="$param;97";;
      "fg-default")             param="$param;39";;
      "bg-black")               param="$param;40";;
      "bg-red")                 param="$param;41";;
      "bg-green")               param="$param;42";;
      "bg-yellow")              param="$param;43";;
      "bg-blue")                param="$param;44";;
      "bg-magenta")             param="$param;45";;
      "bg-cyan")                param="$param;46";;
      "bg-gray")                param="$param;47";;
      "bg-default")             param="$param;49";;
      *) return;;
    esac
  done
  echo -ne "\e[${param:1}m"
}

message() {
  color="$1"
  message="$2"
  setdisp $color
  echo "$message"
  setdisp reset
}

hasFile() {
  match=`echo $1`
  test -e "$match"
}


log() {
  echo "$*"
}


error() {
  message lred "Error: $*"
  exit 1
}

warning() {
  message yellow "Warning: $*"
  #printf "\e[32m$*\e[0m\n"
}


folder=`realpath "$1"`
name=`basename "$folder"`
if [ -d logs ]; then
  log=`pwd`/logs/"$name".log
else
  log=`pwd`/"$name".log
fi

echo ""
echo ""
echo ""
message green "------------------------------------------"
message green "+++ starting $name"
message green "------------------------------------------"

case "$name" in
  *.tar) tarflags="-xf";;
  *.tgz) tarflags="-zxf";;
  *) error "$name: bad extension";;
esac

RUNDIR=`mktemp -d  SND-SPA2.XXXXX` || runerror "Cannot create test run directory"
echo "Created test directory `setdisp blue`$RUNDIR`setdisp reset`"
RUNDIR=`realpath "$RUNDIR"` || runerror "Cannot get real path of test run directory"

tar -C "$RUNDIR" $tarflags "$folder" || error "$name: Cannot extract"
FILE="$name"

cd "$RUNDIR"

USER=`echo *`
case "$USER" in
  a[0-9][0-9][0-9][0-9][0-9][0-9][0-9]);;
  *) error "$FILE: Contents does not seem to be a student number"
esac

test -h "$USER" && error "$USER: is a symlink"
test -d "$USER" || error "$USER: is not a directory"
chmod -R u+rw "$USER" || error "$USER: could not chmod???"

echo "Found Student ID `setdisp blue`$USER`setdisp reset`"

cd $USER
hasFile "info.txt" || error "$FILE: No info.txt"

echo "" | cat info.txt - | sed '/^$/d;s/\r//g' | {
  read Student || exit 1
  echo "Found Student `setdisp blue`$Student`setdisp reset`"
  read ID || exit 1
  test "$ID" = "$USER"|| warning "$FILE: Student ID mismatch"
  read XX && exit 1
  exit 0
} || error "info.txt: Bad format"


hasFile "assignment2.pdf" || error "$FILE: No assignment2.pdf"
hasFile "*.o" && error "$FILE: Includes .o file"
for f in *; do 
  case "$f" in 
    assignment2.pdf);;
    info.txt);;
    src);;
    *) error "$FILE: unknown file $f";;
  esac
done

test -d "src" || error "$FILE: No src directory"

cd src  || error "$FILE: Cannot cd to src"


rm -f oracle.c
cat > oracle.c <<EOF
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "rsa.h"
#include "oracle.h"

static struct {
  num_t n;
  num_t e;
  num_t d;
} yek;

void oracle_init() {
  num_fromString(yek.n, "9e09a0f8b28b8f66b7e5ce7dd71adea72b825901e45eeb1d");
  num_fromString(yek.e, "10001");
  num_fromString(yek.d, "87ef3a5190a9f05fe720391ab48b9ceeca2327633200e475");
}

int oracle(const num_t c) {
  num_t r;
  num_modexp(r, c, yek.d, yek.n);
  if ((r[WORDSIZE-1] & 0xffff0000 ) != 0x00020000)
    return 0;
  return 1;
}

void oracle_getn(num_t n) {
  memcpy(n, yek.n, sizeof(num_t));
}

void oracle_gete(num_t e) {
  memcpy(e, yek.e, sizeof(num_t));
}
EOF

rm -f main.c
cat > main.c <<EOF
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "rsa.h"
#include "bb.h"
#include "oracle.h"


int main() {
  oracle_init();

  // Set up key, plaintext, and ciphertext
  num_t m, e, c, n;
  oracle_gete(e);
  oracle_getn(n);
  num_fromString(m, "deadbeef");
  num_modexp(c, m, e, n);

  // Blind key
  num_t c0={0}, s0={0};
  int a = bb_blind(c0, s0, c, e, n);
  uint32_t x = 0;
  for (int i = 0; i < WORDSIZE; i++)
    x |= c0[i] | s0[i];
  printf("Hello\n");
  return x==0;
}
EOF

make || error "$FILE: Cannot build";
./bb > bb.out 2>bb.err || error "$FILE: bb_blind does not change c0 and s0"
a=`cat bb.out`
test "$a" = "Hello" || error "bb does not run the test  main"

if [ -s bb.err ]; then
  error "$FILE: Output to stderr"
fi


setdisp lgreen; echo "Soundness test passed, but check for warnings"; setdisp reset
