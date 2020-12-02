" Usage:
" :source date_list.vim
" :call DateList(08, 03)

function! DateList(year, month)
    let s:day = 1
    let s:year = 2000 + a:year
    let s:daymax = 31
    if a:month == 4 || a:month == 6 || a:month == 9 || a:month == 11
        let s:daymax = 30
    elseif a:month == 2
        if s:year % 4 == 0 && s:year % 400 != 0
            let s:daymax = 29
        else
            let s:daymax = 28
        endif
    endif
    while s:day <= s:daymax
        execute "normal o".printf("%04d.%02d.%02d", s:year, a:month, s:day)."\<Esc>"
        let s:day = s:day+1
    endwhile
endfunction
