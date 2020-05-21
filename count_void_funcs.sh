#!/bin/bash

if [[ $# != 1 || ! -d "$1" ]]
  then
    echo "error!"
    exit 1
fi

((sum=0))
((counterfiles=0))
((counterdir=0))
for file in "$1"/*; do
	if [[ -f "$file" ]]; then
	num=`grep -w "void" "$file" | grep "(" | grep ")" | wc -l`
	(( sum = $sum + num + 0 ))
	elif [[ -d "$file" ]]; then
	sub=`$0 "$file"`
	(( sum = $sum + $sub + 0 ))
	else
		echo "$file" not such a file or directory >&2
	fi
done
echo "$sum"
exit 0
