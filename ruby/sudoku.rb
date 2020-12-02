#!/usr/bin/ruby

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

def row_include?(m, i, x)
    m[i].include?(x)
end

def col_include?(m, j, x)
    m.each { |row| return true if row[j] == x }
    false
end

def sqr_include?(m, i, j, x)
    m[i/3*3..i/3*3+2].each { |row| row[j/3*3..j/3*3+2].each { |col|
        return true if col == x
    } }
    false
end

def available(m, i, j)
    (1..9).to_a.delete_if { |x|
        row_include?(m, i, x) || col_include?(m, j, x) || sqr_include?(m, i, j, x)
    }
end

def next_pos(m, i, j)
    begin
        j += 1
        if (j == 9)
            i += 1
            j = 0
        end
        return nil if i == 9
    end until m[i][j] == 0
    [i, j]
end

def solve(m, i, j)
    n = next_pos(m, i, j)
    if (!n)
        p m
        return
    end
    a = available(m, n[0], n[1])
    a.each { |x|
        m[n[0]][n[1]] = x
        solve(m, n[0], n[1])
        m[n[0]][n[1]] = 0
    }
end

t1 = Time.new
solve m, 0, -1
t2 = Time.new
p t2-t1
