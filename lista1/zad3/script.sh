#!/usr/bin/zsh

echo "STRONGLY CONNECTED COMPONENTS"
for file in ./data/*
do
	cat $file | ./ssc.out
	echo "\n-------------------"
done

