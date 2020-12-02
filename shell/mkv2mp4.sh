#!/bin/bash

for file in "$@"; do
    filename=${file%.mkv}
    ffmpeg -i "${file}" -c:a copy -c:v copy -f mp4 "${filename}.mp4"
    # mp4 cannot contain ass subtitle
    ffmpeg -i "${file}" -map 0:s:1 -c:s copy -f ass "${filename}.ass"
done
