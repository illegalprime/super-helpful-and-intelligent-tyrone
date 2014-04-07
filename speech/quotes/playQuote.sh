#!/bin/bash

OWN_FILE="../../service/ownership/speaking"

if [ $(cat "$OWN_FILE") -eq 0 ]; then 
	echo 1 > "$OWN_FILE"
	
	play "$1"

	echo 0 > "$OWN_FILE"
fi
