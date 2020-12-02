#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

dir="$1"
img="$(basename "$dir").udf"

hdiutil makehybrid -o "$img" -udf "$dir"
