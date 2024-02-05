#! /bin/bash

# Based on https://stackoverflow.com/a/246128/5781491
SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE
done
cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1

> ./problems.txt

for i do
	URL="https://open.kattis.com/problems?page=$i"
	PATTERN='href="\/problems\/([a-zA-Z0-9_\-\.]+)"'
	echo "$URL:"
	curl "$URL" | grep --color=never -oE "$PATTERN" | sed --sandbox -E "s/$PATTERN/\1/" >> ./problems.txt
done
