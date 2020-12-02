do shell script "/usr/bin/caffeinate /usr/local/bin/aria2c --enable-rpc --rpc-listen-all &> /dev/null &"
do shell script "cd ${HOME}/bin/webui-aria2; /usr/local/bin/node node-server.js &> /dev/null &"

delay 1

tell application "Google Chrome"
    open location "http://localhost:8888"
end tell
