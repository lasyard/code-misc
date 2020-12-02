#!/usr/bin/env sh

if [ $# -lt 2 ]; then
    echo "Usage: $0 <dir> <symbol>"
    exit 1
fi

dir="$1"
symbol="$2"

find_symbol() {
    for file in "${dir}"/$1; do
        if nm -s "${file}" 2>/dev/null | c++filt | grep "${symbol}"; then
            echo "Find \"${symbol}\" in \"${file}\"."
        fi
    done
}

find_symbol '*.o'
find_symbol '*.a'
find_symbol '*.so'
