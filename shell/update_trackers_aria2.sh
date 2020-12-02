#!/usr/bin/env sh

TRACKER_LIST_URL="https://raw.githubusercontent.com/ngosang/trackerslist/master/trackers_best.txt"

ARIA2_CONF="${HOME}/.config/aria2/aria2.conf"

list=$(wget -qO- --no-check-certificate "${TRACKER_LIST_URL}" | awk NF | sed -e ':a' -e 'N' -e '$!ba' -e 's/\n/,/g')

set -x

if ! grep "bt-tracker" "${ARIA2_CONF}"; then
    echo "bt-tracker=${list}" >>"${ARIA2_CONF}"
else
    sed -e "s@bt-tracker=.*@bt-tracker=${list}@g" -i '' "${ARIA2_CONF}"
fi
