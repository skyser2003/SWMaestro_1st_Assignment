#!/bin/sh

script_dir="$(dirname $(readlink -f $0))"

if [ ! -d $script_dir/log ]; then
	mkdir $script_dir/log
fi

tmux new -s swma -d -c $script_dir
tmux send -t swma "tmux new-window './Server > log/server.txt' 2>&1" Enter

