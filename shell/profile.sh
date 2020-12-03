# Set PATH
if [ -d "${HOME}/bin" ]; then
    PATH="${PATH}:${HOME}/bin"
    if [ -d "${HOME}/bin/tools" ]; then
        PATH="${PATH}:${HOME}/bin/tools"
    fi
fi

# MySql
if [ -d "/usr/local/mysql/bin" ]; then
    PATH="${PATH}:/usr/local/mysql/bin"
fi

# Set aliases
alias md='mkdir -p'
alias rd='rmdir'
alias df='df -h'
if [ "$(uname)" = "Darwin" ]; then
    LSCOLORS='Gxfxcxdxbxegedabagacad'
    export LSCOLORS
    alias ls='ls -G'
    alias ll='ls -lAOh'
else
    LS_COLORS='di=1;36:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43'
    export LS_COLORS
    alias ls='ls --color=auto'
    alias ll='ls -lAh'
fi
alias l='ll'
alias la='ls -A'

# Set ssh agent
eval "$(ssh-agent)"
ssh-add "${HOME}/.ssh/id_rsa"

# MacOS
if [ "$(uname)" = "Darwin" ]; then
    if command -v 'mvim' >/dev/null; then
        # Set mvim
        alias vi='mvim --remote-tab-silent'
        alias vidiff='mvim -d'
        # Use original vim for fc
        export FCEDIT=vim
    fi
    if [ -d "/usr/local/opt/gettext/bin" ]; then
        PATH="/usr/local/opt/gettext/bin:${PATH}"
    fi
fi

# Set JAVA_HOME
if [ -x "/usr/libexec/java_home" ]; then # for MacOS
    JAVA_HOME="$(/usr/libexec/java_home)"
    export JAVA_HOME
else
    java_path=$(command -v java)
    if [ -n "${java_path}" ]; then
        JAVA_HOME="${java_path%/bin/java}"
        export JAVA_HOME
    fi
fi

# Set GPG_TTY
GPG_TTY=$(tty)
export GPG_TTY

# Set proxy
proxy() {
    if [ "$1" = 'off' ]; then
        export http_proxy=
        export https_proxy=
        return
    fi
    if nc -z localhost 1087; then
        export http_proxy=http://localhost:1087
        export https_proxy=http://localhost:1087
        echo "Set http_proxy & https_proxy to http://localhost:1087."
    else
        echo "No proxy found."
    fi
}
