#!/bin/sh

if [ "$#" -ne 2 ]; then
    echo "USAGE: $0 host port"
    exit 0
fi

USERNAME="Anonymous"
PASS=""

HOST=$1
PORT=$2
MKFIFO=`which mkfifo`
PIPE=fifo
OUT=outfile
RESPONSE="WELCOME"
TAIL=`which tail`
NC="`which nc` -C"
TIMEOUT=1 #max time before reading server response

print_succeeded()
{
  echo "$1 test succeeded"
  echo "OK"  
  kill_client 2>&1 >/dev/null
}

getcode()
{
  sleep $TIMEOUT
  local code=$1
  echo "Waiting for $code reply-code"
  local data=`$TAIL -n 1 $OUT |cat -e |grep "^$code.*[$]$" |wc -l`
  return $data
}

launch_client()
{
  local host=$1
  local port=$2

  $MKFIFO $PIPE
  ($TAIL -f $PIPE 2>/dev/null | $NC $host $port &> $OUT &) >/dev/null 2>/dev/null

  echo "Connecting to $host : $port"
  sleep $TIMEOUT
  if [[ "`tail -n 1 $OUT`" == "WELCOME" ]]; then
    echo "Reply-code OK"
    return 1
  else
    echo "Connection to $host:$port failed"
    echo "Expected reply-code: WELCOME"
    echo "Received : ["`tail -n 1 $OUT |cat -e`"]"
    return 0
  fi  
  kill_client
}

kill_client()
{
  local nc=`which nc`

  if [ `pidof $TAIL | wc -l` -ne 0 ]
  then
    killall $TAIL &>/dev/null
  fi
  if [ `pidof $nc | wc -l` -ne 0 ]
  then
    killall $nc &>/dev/null
  fi  
  rm -f $PIPE $OUT &> /dev/null
}

test00()
{
  local test_name="Connection"

  local cmd1="USER $USERNAME"
  local cmd2="PASS $PASS"

  ../zappy_server -p $PORT & echo "dog"
  local pid=$!
  echo "$pid"
  launch_client $HOST $PORT
  if [[ ! $? -eq 1 ]]; then
    echo "KO"
    kill -9 $pid
    return
  fi

  print_succeeded "$test_name"
  kill -9 $pid
  return
}

test00