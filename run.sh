#!/usr/bin/env bash

test -f cp.marker || { >&2 printf -- 'Please call run from the repo root directory.' ; exit 1 ; }

# TODO build for unconfigured judges

case "$1" in
  j/ka/*|./j/ka/*)
    file="${1##*j/ka/}"
    case "$1" in
      *.cpp)
        base="${2%.cpp}"
        g++-14 -g -O2 -o build/j/ka/"$base" -std=gnu++23 -static -lrt -Wl,--whole-archive -lpthread -Wl,--no-whole-archive "$1"
        build/j/ka/"$base"
        ;;
    esac
    ;;
  *)
esac
