#!/bin/bash

# if the number of the arguments are less than 2, exit with error
if [[ $# -ne 2 ]]; then
    echo "The number of arguments are less than 2."
    exit 1
fi


# Creates directory if not exist 
mkdir -p $(dirname $1)

echo $2 > $1
