#!/usr/bin/env bash

declare -a INPUT_VIDEO_FILES

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 [-crf 23] [-crop] [-size 1280x720] [-nohqdn] <File...>"
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
        INPUT_VIDEO_FILES+=("${!i}")
        ;;
    esac
done

if [[ -z "${INPUT_VIDEO_FILES[*]}" ]]; then
    echo "Please specify the input file."
    exit 1
fi

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

for f in "${INPUT_VIDEO_FILES[@]}"; do
    IN_FILE="$f"
    OUT_FILE="${f%.*}-out.mp4"
    echo "Encoding file \"${IN_FILE}\" to \"${OUT_FILE}\"..."
    set -x
    ffmpeg -i "${IN_FILE}" "${OPTS[@]}" "${OUT_FILE}"
    set +x
done
