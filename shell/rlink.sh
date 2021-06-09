#!/usr/bin/env sh

if [ $# -lt 2 ]; then
    echo "Usage: $0 <source> <target>"
    exit 1
fi

SOURCE="$1"
TARGET="$2"

DIR="$(
    cd "$(dirname "${SOURCE}")" || exit
    pwd
)"

if [ -d "${DIR}" ]; then
    ln -svnf "${DIR}/$(basename "${SOURCE}")" "${TARGET}"
fi
