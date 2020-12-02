#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <command>"
    exit 1
fi

command="$*"

. read_lines.sh

hosts=$(read_lines)

echo "Hosts are: ${hosts}."

set -x
for host in ${hosts}; do
    # shellcheck disable=SC2029
    ssh "${host}" "${command}"
done
