#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import os
import sys
from subprocess import Popen, PIPE

mydir = os.path.dirname(__file__)

p = Popen(['bash', mydir + '/test_popen.sh'], stdin=PIPE, stdout=PIPE)

i = 0

while i < 10:
    try:
        i += 1
        # bytes is only in py3; bytes in py2 is str.
        if bytes == str:
            p.stdin.write(b'Hello, I am test_popen.py '
                          + bytes(str(i)) + b"\n")
        else:
            p.stdin.write(b'Hello, I am test_popen.py '
                          + bytes(str(i), 'utf-8') + b"\n")
        p.stdin.flush()
        print('Send ' + str(i) + ' times')
        output = p.stdout.readline()
        print(output)
    except Exception as e:
        print(e)
        p.kill()
        sys.exit(1)

p.kill()
p.wait()
