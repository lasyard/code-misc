#!/usr/bin/env bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <input-file...>"
    exit 1
fi

for file in "$@"; do
    DIGIT="$(basename "${file}" | grep -o -E '\d{10}')"
    if [ -n "${DIGIT}" ]; then
        DATE="$(date -j -f "%s" "+%Y%m%d_%H%M%S" "${DIGIT}")"
        NEW_FILE="${DATE}.${file##*.}"
        echo "Rename file \"${file}\" to ${NEW_FILE}."
        mv "${file}" "${NEW_FILE}"
    fi
done
