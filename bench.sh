#!/bin/bash

i=0

function bench {
    while read line;
    do
        (( i++ ));
        ./pyrin "$line" > /dev/null;
        #echo $line | sha512sum > /dev/null;
        echo $i;
    done < /dev/urandom
}

export -f bench

timeout 1s bash -c bench

echo $i
