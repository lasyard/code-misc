#!/usr/bin/env sh

if [ $# -lt 3 ]; then
    echo "Usage: $0 <app-name> <package.tar.gz> <install-dir>"
    exit 1
fi

app="$1"

package="$2"
dir="${3%%/}"
target="$(tar -tvf "${package}" | head -n 1 | tr -s "[:blank:]" "\n" | tail -n 1 | cut -d '/' -f 1)"
appdir="${dir}/${app}"

if [ ! -f "${package}" ]; then
    echo "File ${package} does not exists."
    exit 1
fi

if [ ! -d "${dir}" ]; then
    echo "${dir} is not a directory."
    exit 1
fi

# set -x

if [ -x "${dir}" ] && [ -w "${dir}" ]; then
    sudo=""
else
    sudo="sudo"
fi

${sudo} tar -poC "${dir}" -xzf "${package}"

${sudo} ln -snvf "${dir}/${target}" "${appdir}"

add_path() {
    path="$1"
    if [ -d "${path}" ]; then
        if [ -d "/etc/profile.d" ]; then
            echo "PATH=\"${path}:\${PATH}\"" | sudo tee -a "/etc/profile.d/${app}.sh"
            echo "'${path}' added to /etc/profile.d/${app}.sh."
        elif [ -d "/etc/paths.d" ]; then
            echo "${path}" | sudo tee -a "/etc/paths.d/${app}.sh"
            echo "'${path}' added to /etc/paths.d/${app}.sh."
        else
            echo "Cannot find '/etc/profile.d' or '/etc/paths.d' to put path '${path}'"
            return 1
        fi
        return 0
    fi
    echo "${path} is not a directory."
}

add_path "${appdir}/bin"
add_path "${appdir}/sbin"
