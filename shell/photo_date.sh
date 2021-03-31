#!/usr/bin/env bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <input-file...>"
    exit 1
fi

for file in "$@"; do
    DATE="$(date -j -f "%s" "+%Y:%m:%d %H:%M:%S" "$(basename "${file}" | grep -o -E '\d{10}')")"
    echo "Change date of ${file} to ${DATE}."
    # shellcheck disable=SC2016
    exiftool -ext jpg -if 'not ${DateTimeOriginal}' -AllDates="${DATE}" -overwrite_original "${file}"
done
