#!/usr/bin/env bash

test -f .cp.marker || { >&2 printf -- 'Please call run.sh from the repo root directory.' ; exit 1 ; }

# TODO build for unconfigured judges

case "$1" in
  j/ka/*|./j/ka/*)
    file="${1##*j/ka/}"
    mkdir -p build/j/ka
    case "$1" in
      *.cpp)
        base="${file%.cpp}"
        mkdir -p "$(dirname -- build/j/ka/"$base")"
        g++-14 -g -O2 -o build/j/ka/"$base" -std=gnu++23 -static -lrt -Wl,--whole-archive -lpthread -Wl,--no-whole-archive "$1" || exit
        build/j/ka/"$base"
        ;;
    esac
    ;;
  j/co/*|./j/co/*)
    file="${1##*j/co/}"
    mkdir -p build/j/co
    case "$1" in
      *.cpp)
        base="${file%.cpp}"
        mkdir -p "$(dirname -- build/j/co/"$base")"
        g++-14 -Wall -Wextra -Wconversion -static -DONLINE_JUDGE -O2 -std=c++23 "$1" -lstdc++exp -o build/j/co/"$base" || exit
        build/j/co/"$base"
        ;;
    esac
    ;;
  *)
esac
