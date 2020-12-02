#!/usr/bin/env bash

INPUT_VIDEO_FILE=
OUTPUT_VIDEO_FILE=

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 [-crf 23] [-crop] [-size 1280x720] [-nohqdn] <File Name>"
    exit 1
fi

declare -a OPTS=("-c:a" "aac" "-c:v" "libx264")
declare -a VFS

for ((i = 1; i <= $#; ++i)); do
    case "${!i}" in
    -crf)
        ((++i))
        CRF="${!i}"
        OPTS+=("-crf")
        OPTS+=("${CRF}")
        CRFSET=true
        echo "Set crf to ${CRF}. NOTE: 23 is default, value - 6, file size double."
        ;;
    -crop)
        echo "Crop input file from 16:9 to 4:3 and encode."
        VFS+=("crop=out_w=in_w*3/4")
        ;;
    -size)
        ((++i))
        SIZE="${!i}"
        OPTS+=("-s")
        OPTS+=("${SIZE}")
        echo "Set output size to ${SIZE}."
        ;;
    -nohqdn)
        NOHQDN=true
        echo "Disable dedot."
        ;;
    -*)
        echo "Unknow option \"${!i}\"! A mistake?"
        exit 1
        ;;
    *)
        if [[ -z "${INPUT_VIDEO_FILE}" ]]; then
            INPUT_VIDEO_FILE="${!i}"
        elif [[ -z "${OUTPUT_VIDEO_FILE}" ]]; then
            OUTPUT_VIDEO_FILE="${!i}"
        else
            echo "Extra parameter \"${!i}\" found. A mistake?"
            exit 1
        fi
        ;;
    esac
done

if [[ -z "${INPUT_VIDEO_FILE}" ]]; then
    echo "Please specify the input file."
    exit 1
fi

if [[ -z "${OUTPUT_VIDEO_FILE}" ]]; then
    OUTPUT_VIDEO_FILE="out.mp4"
fi

echo "Input file is ${INPUT_VIDEO_FILE}."
echo "Output file is ${OUTPUT_VIDEO_FILE}."

if [[ -z "${CRFSET}" ]]; then
    OPTS+=("-crf")
    OPTS+=("18")
fi
if [[ -z "${NOHQDN}" ]]; then
    VFS+=("hqdn3d")
fi
VIDEO_FILTERS=$(
    IFS=,
    echo "${VFS[*]}"
)

if [[ -n "${VIDEO_FILTERS}" ]]; then
    OPTS+=("-vf")
    OPTS+=("${VIDEO_FILTERS}")
fi

set -x

ffmpeg -i "${INPUT_VIDEO_FILE}" "${OPTS[@]}" "${OUTPUT_VIDEO_FILE}"
