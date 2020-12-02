#!/usr/bin/env sh

for formula in \
    ffmpeg \
    jq \
    media-info \
    p7zip \
    rsync \
    tree \
    unrar \
    wget; do
    brew install "${formula}"
done
