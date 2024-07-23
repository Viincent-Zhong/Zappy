#!/bin/bash

HOST="127.0.0.1"
PORT="4242"
BIN_SERVER="../zappy_server"
BIN_AI_CLI="../zappy_ai"
SERVER="server"
CLIENT="client"
HELP="help"
RED='\033[0;31m'
Cyan='\033[0;36m'
NC='\033[0m'
FILE="test.txt"

SERVER_PORT="-p $PORT"
SERVER_WIDTH="-x 10"
SERVER_HEIGHT="-y 10"
SERVER_NAMES="-n pad"
SERVER_CLIENT_NB="-c 3"
SERVER_FREQ="-f 2"
AI_PORT="-p $PORT"
AI_IP="-h $HOST"
AI_NAME="-n pad"

trap end INT

function end() {
    rm -f $FILE
    echo -e "${RED}End with ctrl+C${NC}";
}

function wait_server() {
    echo "" > $FILE

    until nc $HOST $PORT < $FILE
    do
        echo "${RED}waiting for tcp server...${NC}"
        sleep 1
    done
}

function start_client() {
    ./$BIN_AI_CLI $AI_PORT $AI_IP $AI_NAME
}

function start_server() {
    ./$BIN_SERVER $SERVER_PORT $SERVER_WIDTH $SERVER_HEIGHT $SERVER_NAMES $SERVER_CLIENT_NB $SERVER_FREQ
}

function help() {
    echo "Run:"
    echo -e "\t$RED./script.sh${NC}: start server + client ai"
    echo -e "\t$RED./script.sh${NC} ${Cyan}server${NC}: start server"
    echo -e "\t$RED./script.sh${NC} ${Cyan}client${NC}: start client ai"
    echo -e "\t$RED./script.sh${NC} ${Cyan}help${NC}: print help"
}

function start_all() {
    start_server &
    wait_server
    start_client
}

function start() {
    if [ "$HELP" = "$1" ]; then
        help
    elif [ "$SERVER" = "$1" ]; then
        start_server
    elif [ "$CLIENT" = "$1" ]; then
        start_client
    else
        start_all
    fi
}

function welcome() {
    figlet -f pagga "Start Zappy"
}

welcome
start $1