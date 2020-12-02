#!/usr/bin/env bash

declare -a source=(
    "${HOME}/Library/Mobile Documents/com~apple~CloudDocs"
    "${HOME}/Library/Application Support/Google/Chrome/Default/Extensions"
    "${HOME}/.m2/repository"
)
declare -a target=(
    "${HOME}/Documents/CloudDocs"
    "${HOME}/Downloads/ChromeExtensions"
    "${HOME}/Downloads/m2_repo"
)

if [[ "$1" == "--delete" ]]; then
    for ((i = 0; i < ${#target[*]}; i++)); do
        rm -vf "${target[$i]}"
    done
    exit 0
fi

for ((i = 0; i < ${#source[*]}; i++)); do
    ln -snvf "${source[$i]}" "${target[$i]}"
done
