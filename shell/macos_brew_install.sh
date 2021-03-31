#!/usr/bin/env sh

for formula in \
    ffmpeg \
    jq \
    media-info \
    p7zip \
    rsync \
    tree \
    gpg2 \
    wget \
    cmake; do
    brew install "${formula}"
done
