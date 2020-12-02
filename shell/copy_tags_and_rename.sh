#!/usr/bin/env sh

if [ $# -lt 2 ]; then
    echo "Usage: $0 <Source JPG File> <Target JPG File>"
    exit 1
fi

src="$1"
tgt="$2"

set -x

exiftool -tagsfromfile "${src}" -exif:all -overwrite_original "${tgt}"
# shellcheck disable=SC2016
exiftool -if '${DateTimeOriginal} and ${Keywords} and ${Model}' -d '%y%m%d_%H%M%S' \
    -FileName\<'${DateTimeOriginal}_${Keywords;s/,\s*/_/g;}_${Model;tr/, /_/;}%-3c.%e' \
    -overwrite_original "${tgt}"
