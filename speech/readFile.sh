#!/bin/bash
OWN_FILE="../service/ownership/speaking"

if [ $(cat ${OWN_FILE}) -ne 0 ]; then
	echo "Something is already speaking.."
	exit 1
fi

echo 1 > $OWN_FILE

cat "$1" | espeak -vdefault+m3 -p 40 -s 160

echo 0 > $OWN_FILE