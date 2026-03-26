#!/bin/bash

if [[ -n $1 ]]; then
        executableName=$1
else
        executableName='grep++'
fi

g++ main.cpp config.cpp printing.cpp string_stuff.cpp util.cpp -o $executableName &&
        echo "grep++ is available by running ./$executableName"
