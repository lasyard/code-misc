" On Windows, put it to vim directory and rename to _vimrc
" On Linux, put it to home directory and rename to .vimrc

set nocompatible
set noswapfile
set ruler
set wrap
set showbreak=>
set display=lastline,uhex
set backspace=indent,eol,start
set whichwrap+=<,>,[,]
set number
set tabstop=4
set shiftwidth=4
set expandtab
set magic

if has("gui_running")
    set guioptions=aemgTRb
    set lines=33
    set columns=120
    if has("gui_win32")
        set dir=%TEMP%
        set guifont=:h16:cDEFAULT
        setglobal fileencodings=ucs-bom,utf-8,chinese
    endif
    if has("gui_macvim")
        set guifont=Monaco:h18
        set guifontwide=宋体-简:h18
        " Important to show full width quotation marks.
        set ambiwidth=double
        set linespace=2
        set noimdisable
    endif
endif

if has("autocmd")
    filetype indent on
    filetype plugin on
endif

if !exists("syntax_on")
    syntax on
endif

set hlsearch

highlight LineNr ctermbg=DarkBlue ctermfg=Grey
