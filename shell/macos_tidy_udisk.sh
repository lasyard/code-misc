#!/usr/bin/env sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <mount-point>"
    exit 1
fi

mp="$1"

# show status
sudo mdutil -s "${mp}"

# turn off indexing and searching
sudo mdutil -i off -d "${mp}"
sudo mdutil -X "${mp}"

touch "${mp}/.metadata_never_index"

# disable fsevent log
touch "${mp}/.fseventsd/no_log"
