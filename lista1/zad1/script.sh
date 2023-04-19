#!/usr/bin/zsh

echo "BFS"
for file in ./data/*
do
	cat $file | ./bfs.out $1
	echo "-------------------"
done

echo "DFS"
for file in ./data/*
do
	cat $file | ./dfs.out $1
	echo "------------------"
done
