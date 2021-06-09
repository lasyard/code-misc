#!/usr/bin/env bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <input-file...>"
    exit 1
fi

DATE_FMT="+%Y:%m:%d %H:%M:%S"

for file in "$@"; do
    DIGIT="$(basename "${file}" | grep -o -E '\d{10}')"
    if [ -n "${DIGIT}" ]; then
        DATE="$(date -j -f "%s" "${DATE_FMT}" "${DIGIT}")"
        echo "Change date of ${file} to ${DATE}, derived from timestamp."
    else
        DATE="$(date -r "${file}" "${DATE_FMT}")"
        echo "Change date of ${file} to ${DATE}, derived from modification time."
    fi
    # shellcheck disable=SC2016
    exiftool -ext jpg -if 'not ${DateTimeOriginal}' -AllDates="${DATE}" -overwrite_original "${file}"
done
