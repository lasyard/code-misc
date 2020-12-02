#!/usr/bin/env bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <regex> <target>"
    exit 1
fi

regex="$1"
target="$2"

set -o pipefail

if ! find . -maxdepth 1 -not -name '.*' | grep -E "${regex}" |
    sed -E "s/^/\"/; s/$/\"/" | sed -E "p; s/${regex}/${target}/g" | xargs -n2 echo; then
    echo "No files found to rename."
    exit 1
fi

read -rp "Do you want to rename? (y/N)" ans

if [ "${ans}" == 'y' ] || [ "${ans}" == 'Y' ]; then
    find . -maxdepth 1 -not -name '.*' | grep -E "${regex}" |
        sed -E "s/^/\"/; s/$/\"/" | sed -E "p; s/${regex}/${target}/g" | xargs -n2 mv
fi
