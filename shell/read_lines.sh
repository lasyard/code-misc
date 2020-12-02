read_lines() {
    _read_lines_lines_=""
    while read -r _read_lines_line_; do
        _read_lines_lines_="${_read_lines_lines_} ${_read_lines_line_}"
    done
    echo "${_read_lines_lines_}"
}
