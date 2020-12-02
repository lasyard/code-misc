#!/bin/bash

for file in "$@"; do
    filename=${file%.wav}
    lame -b 320 "${file}" "${filename}.mp3"
done
