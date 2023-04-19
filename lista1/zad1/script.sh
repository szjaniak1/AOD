#!/usr/bin/zsh

for file in ./data/*
do
	cat $file | ./bfs.out
	echo "-------------------"
done

for file in ./data/*
do
	cat $file | ./dfs.out
	echo "------------------"
done
