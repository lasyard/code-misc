#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <file/dir>"
    exit 1
fi

file="$1"

if [ ! -e "${file}" ]; then
    echo "${file} not exists!"
    exit 1
fi

. read_lines.sh

hosts=$(read_lines)

echo "Hosts are: ${hosts}."

set -x
for host in ${hosts}; do
    scp -r "${file}" "${host}:${file}"
done
