#! /bin/bash

if [[ $# == 0 ]]; then
    echo "Usage : $0 file [...]"
    exit 1
fi

for file in `ls $@`; do
    COUNT=`wc -L < $file`
    echo "$COUNT $file"
done
