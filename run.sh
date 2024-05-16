#!/bin/bash

interface_type="terminal"

while [[ $# -ne 0 ]]
do
  case "$1" in
  --interface|-i) interface_type="$2" ;;
  esac
  shift
  shift
done

./bin/server.out &
./bin/exe.out $interface_type
