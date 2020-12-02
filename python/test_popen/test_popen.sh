#!/bin/bash

got_err_signal() {
    echo got ERR.
    exit 1
}

trap got_err_signal ERR

while true; do
    read str
    echo got ${str}
done
