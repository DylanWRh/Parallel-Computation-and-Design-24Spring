#!/bin/bash

recycbin=~/recycbin

if [ -d $recycbin ]; then
    rm -r "$recycbin"/*
    echo "Recycbin cleared"
else
    echo "Recycbin not found"
fi

exit 0
