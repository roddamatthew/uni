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

RUNDIR=`mktemp -d  SND-SPA1.XXXXX` || runerror "Cannot create test run directory"
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


hasFile "assignment1.pdf" || error "$FILE: No assignment1.pdf"
hasFile "*.o" && error "$FILE: Includes .o file"
for f in *; do 
  case "$f" in 
    assignment1.pdf);;
    info.txt);;
    rotate.c);;
    rsa.c);;
    part2);;
    *) error "$FILE: unknown file $f";;
  esac
done

cat > testrotate.c <<EOF
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rotate.c"

int main(int ac, char **av) {
  printf("%u\n", rotate(1, 1));
  exit(0);
}
EOF

if hasFile rotate.c; then
  cc -o testrotate testrotate.c || errro "+++ Cannot build rotate."
  ./testrotate  > testrotate.out 2> testrotate.err || errro "+++ Cannot use rotate."
  a=`cat testrotate.out`
  test "$a" = 2 || error "Cannot compute rotate(1,1)"

  if [ -s testrotate.err ]; then
    error "$FILE: Output to stderr"
  fi
  setdisp green; echo "+++ rotate.c passes sooundness"; setdisp reset
else
  warning "No file rotate.c - Question 9 will not be marked."
fi

cat > testrsa.c <<EOF
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rsa.c"

int main(int ac, char **av) {
  num_t m, n, e, c;
  num_fromString(m, av[1]);
  num_fromString(e, av[2]);
  num_fromString(n, av[3]);
  num_modexp(c, m, e, n);
  printf("%s\n", num_toString(c));
  exit(0);
}
EOF

if hasFile rsa.c; then
  n=d473c3b4a419b60eb3064528b1616b0687afd70656cdf15a3026c5a4a0990647a45acde2cfd7fff6f9a175d629996da9dee7cb1fbb43a9ecc9872ca350b62c40853ae4be9f123fd9db0a3ed87891b954a2b51263a1f1865bf0a5541fd54c6227923c4835b8e584324bb8a3316a4cb1fb5ce500548d62c92a2ab2102371356853
  cc -o testrsa testrsa.c || errro "+++ Cannot build rsa."
  ./testrsa  2 2 $n > testrsa.out 2> testrsa.err || errro "+++ Cannot use rsa."
  a=`sed 's/^0*//' testrsa.out`
  test "$a" = 4 || error "Cannot compute 2^2"

  if [ -s testrotate.err ]; then
    error "$FILE: Output to stderr"
  fi
  setdisp green; echo "+++ rsa.c passes sooundness"; setdisp reset
else
  warning "No file rsa.c - Question 10 will not be marked."
fi

setdisp lgreen; echo "Soundness test passed, but check for warnings"; setdisp reset
