#!/bin/sh

y=`find $1 -name "*.c"`
#grep -r --after-context=6 -n main $y 
#find . -name "*.c" | xargs grep -r --after-context=6 -n main

for i in $y;
do
	if grep $2 $i; then
		t=`grep -n -A 6 $2 $i`
		echo "============================================="
		echo "$i"
		echo "============================================="
		echo "$t"
	fi
done
