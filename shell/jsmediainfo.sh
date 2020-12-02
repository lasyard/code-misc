#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <FileName...>"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "${file}" ]; then
        echo "File ${file} does not exist."
        continue
    fi

    TRACKS=$(mediainfo --Output=JSON "${file}" | jq '.media.track')

    GENERAL=$(echo "${TRACKS}" | jq -r '.[]|select(."@type"=="General")')
    FILESIZE=$(echo "${GENERAL}" | jq -r '.FileSize')
    DURATION=$(echo "${GENERAL}" | jq -r '.Duration')

    VIDEO_TRACK=$(echo "${TRACKS}" | jq '.[]|select(."@type"=="Video")')
    # DURATION=$(echo "${VIDEO_TRACK}" | jq -r '.Duration')
    WIDTH=$(echo "${VIDEO_TRACK}" | jq -r '.Width')
    HEIGHT=$(echo "${VIDEO_TRACK}" | jq -r '.Height')

    echo "${file}: size=${FILESIZE}, duration=${DURATION}, width=${WIDTH}, height=${HEIGHT}"
done
