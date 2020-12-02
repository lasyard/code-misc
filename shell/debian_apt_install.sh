#!/usr/bin/env sh

for package in \
    build-essential \
    "linux-headers-$(uname -r)" \
    curl \
    default-jdk \
    vim; do
    sudo apt install "${package}"
done
