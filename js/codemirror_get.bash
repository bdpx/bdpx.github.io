#!/bin/bash

version="6.65.7"
root="https://cdnjs.com/libraries/codemirror/${version}/"
prefix="https://cdnjs.cloudflare.com/ajax/libs/codemirror/${version}/"

len=${#prefix}
len=$((len+1))

FILES=($(curl ${root} | html2text -width 1000 | grep --only-matching "${prefix}.*" | cut -c${len}-))

for file in "${FILES[@]}"
do
    echo "url = ${prefix}$file"
    curl  --create-dirs --output "./codemirror/${file}" "${prefix}${file}"
done

