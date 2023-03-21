#!/bin/sh



# if the number of the arguments are less than 2, exit with error
if [[ $# -ne 2 ]]; then
    echo "The number of arguments are less than 2."
    exit 1
fi

# if the first argument is not directory, exit with error message
if ! [[ -d $1 ]]; then
    echo "You entered invalid directory"
    exit 1
fi


matchingLines=$(grep $2 -r $1 | wc -l)
numOfFiles=$(ls -1 $1 | wc -l)

echo "The number of files are $numOfFiles and the number of matching lines are $matchingLines"
