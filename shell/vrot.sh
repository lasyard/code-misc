#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <input-file> [<angle>]"
    exit 1
fi

if [ -z "$2" ]; then
    angle=0
else
    angle=$2
fi

INPUT_VIDEO_FILE="$1"
TMP_FILE="${HOME}/~$(basename -- "${INPUT_VIDEO_FILE}")"

echo "Using temp file ${TMP_FILE}."

ffmpeg -i "${INPUT_VIDEO_FILE}" -c copy -metadata:s:v:0 rotate="${angle}" "${TMP_FILE}"

mv "${TMP_FILE}" "${INPUT_VIDEO_FILE}"
