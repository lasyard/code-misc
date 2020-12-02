#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time

m = [
    [8, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 3, 6, 0, 0, 0, 0, 0],
    [0, 7, 0, 0, 9, 0, 2, 0, 0],
    [0, 5, 0, 0, 0, 7, 0, 0, 0],
    [0, 0, 0, 0, 4, 5, 7, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 3, 0],
    [0, 0, 1, 0, 0, 0, 0, 6, 8],
    [0, 0, 8, 5, 0, 0, 0, 1, 0],
    [0, 9, 0, 0, 0, 0, 4, 0, 0]
]


def row_include(m, i, x):
    return x in m[i]


def col_include(m, j, x):
    for row in m:
        if row[j] == x:
            return True
    return False


def sqr_include(m, i, j, x):
    for row in m[i // 3 * 3:i // 3 * 3 + 3]:
        for col in row[j // 3 * 3:j // 3 * 3 + 3]:
            if col == x:
                return True
    return False


def available(m, i, j):
    return [x for x in range(1, 10) if not (row_include(m, i, x) or col_include(m, j, x) or sqr_include(m, i, j, x))]


def next_pos(m, i, j):
    while True:
        j += 1
        if j == 9:
            i += 1
            j = 0
        if i == 9:
            return None, None
        if m[i][j] == 0:
            return i, j


def solve(m, i, j):
    ii, jj = next_pos(m, i, j)
    if ii is None:
        print(m)
        return
    for x in available(m, ii, jj):
        m[ii][jj] = x
        solve(m, ii, jj)
        m[ii][jj] = 0


if __name__ == '__main__':
    t1 = time.clock()
    solve(m, 0, -1)
    t2 = time.clock()
    print('%d' % (t2 - t1))
