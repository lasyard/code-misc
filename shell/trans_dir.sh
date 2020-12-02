#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <command>"
    exit 1
fi

command="$*"

trans_dir() {
    for d in */; do
        if [ "$d" != "*/" ] && cd "${d}"; then
            trans_dir
            cd ..
        fi
    done
    echo "In directory \"$(pwd)\":"
    ${command}
}

trans_dir
