#!/usr/bin/zsh

echo "TOPOLOGICAL SORT"
for file in ./data/*
do
	cat $file | ./top.out
	echo "\n-------------------"
done

