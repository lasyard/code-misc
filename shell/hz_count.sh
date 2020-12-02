#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <FileName...>"
    exit 1
fi

total=0
for file in "$@"; do
    ct=$(($(iconv -f utf-8 -t gb18030 "${file}" | wc -c) / 2))
    echo "${file}: ${ct}"
    total=$((total + ct))
done
echo "Total: ${total}"
