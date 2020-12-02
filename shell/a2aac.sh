#!/usr/bin/env sh

for file in "$@"; do
    ffmpeg -i "${file}" -c:v copy -c:s copy -c:a aac "~${file}"
    mv "~${file}" "${file}"
done
