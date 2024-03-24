#!/bin/bash

recycbin=~/recycbin

if [ ! -d $recycbin ]; then
    mkdir -p $recycbin
fi

echo "Running $0 ..."
echo "Moving $# files to recycbin"
mv $* -t $recycbin
exit 0
