#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <input-file...>"
    exit 1
fi

LOG="vchk.log"

for file in "$@"; do
    echo "Check video file \"${file}\"." | tee -a "${LOG}"
    ffmpeg -v error -i "${file}" -f null - 2>&1 | tee -a "${LOG}" || break
done

# shellcheck disable=SC2039
read -rp "Do you want to remove log file \"${LOG}\"? (y/N)" ans
if [ "${ans}" = 'y' ] || [ "${ans}" = 'Y' ]; then
    rm -f ${LOG}
fi
